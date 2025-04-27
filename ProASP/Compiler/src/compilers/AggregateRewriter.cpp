#include "AggregateRewriter.h"

std::string AggregateRewriter::AGG_SET_PREFIX = "Agg_set";
std::string AggregateRewriter::BODY_PREFIX = "Body";

AggregateRewriter::AggregateRewriter(const aspc::Program& program) : program(program), nextAggId(0){
    rewriteAggregates();
    //copy directives
    for(const aspc::TypeDirective& d : program.getDirectives()){
        rewrittenProgram.addTypeDirective(d);
    }
}

void AggregateRewriter::rewriteAggregates(){
    for(aspc::Rule rule : program.getRules()){
        if(!rule.containsAggregate())
            rewrittenProgram.addRule(rule);
        else{
            rewriteRuleWithAggregate(rule);
        }
    }
}

const aspc::Program& AggregateRewriter::getRewrittenProgram(){
    return rewrittenProgram;
}

void AggregateRewriter::rewriteRuleWithAggregate(const aspc::Rule& rule){
    
    //create agg_set
    aspc::Atom aggSetRuleHead(AggregateRewriter::AGG_SET_PREFIX + std::to_string(nextAggId));
    
    const std::vector<aspc::Literal>& body = rule.getBodyLiterals();
    std::unordered_set<std::string> externalVars;
    for(const aspc::Literal& lit : body){
        if(lit.isPositiveLiteral())
           lit.addVariablesToSet(externalVars);
    }
    if(rule.getArithmeticRelationsWithAggregate().size() > 1){
        std::cout <<"Only one aggregate in allowed in body\n";
        exit(180);
    }

    const aspc::ArithmeticRelationWithAggregate& relWithAgg = rule.getArithmeticRelationsWithAggregate().at(0);
    std::vector<std::string> aggrVariables = relWithAgg.getAggregate().getAggregateVariables();
    std::unordered_set<std::string> conjVars;
    relWithAgg.getAggregate().addAggregateLiteralVariablesToSet(conjVars);
    std::unordered_set<std::string> headVars;
    std::vector<std::string> aggSetTerms;
    //\rho (terms in aggregate conjunction that are also in body)
    for(const aspc::Literal&  lit : relWithAgg.getAggregate().getAggregateLiterals()){
        for(std::string term : lit.getTerms()){
            if(externalVars.count(term) && isVariable(term) && headVars.insert(term).second)
                aggSetTerms.push_back(term);
        }
    }
    //V (terms in var set)
    for(std::string var : relWithAgg.getAggregate().getAggregateVariables()){
        if(headVars.insert(var).second)
            aggSetTerms.push_back(var);
    }
    for(std::string var : aggSetTerms){
        aggSetRuleHead.addTerm(var);
    }
    //construct aggSetRule body
    std::vector<aspc::Literal> aggSetBody;
    aspc::Literal joinBodyLiteral(false, aspc::Atom(AggregateRewriter::BODY_PREFIX + std::to_string(nextAggId)));
    std::unordered_set<std::string> joinBodyTerms;
    std::vector<std::string> joinBodyTermsVec;
    for(const aspc::Literal& lit : rule.getBodyLiterals()){
        for(std::string term : lit.getTerms()){
            if(joinBodyTerms.insert(term).second)
                joinBodyTermsVec.push_back(term);
        }
        // aggSetBody.push_back(lit);
    }
    joinBodyLiteral.setTerms(joinBodyTermsVec);
    //if rule with aggregate has only one body literal no rule for generating body is needed
    // no airthmnetic relation admitted in such case since a rule with aggregate is either
    //of the form h :- aggr. or h :- bodyJoin, aggr.  
    bool generateBodyRule = rule.getBodyLiterals().size() + rule.getArithmeticRelations().size() > 1;
    if(generateBodyRule){
        rewrittenProgram.addPredicate(joinBodyLiteral.getPredicateName(), joinBodyLiteral.getAriety());
        aspc::Rule joinRule({joinBodyLiteral.getAtom()}, rule.getBodyLiterals(), rule.getArithmeticRelations(), {}, false);
        std::cout <<"Created join rule with id: " << joinRule.getRuleId()<< "\n";
        rewrittenProgram.addRule(joinRule);
        aggSetBody.push_back(joinBodyLiteral);
    }
    for(const aspc::Literal& lit : relWithAgg.getAggregate().getAggregateLiterals()){
        aggSetBody.push_back(lit);
    }
    rewrittenProgram.addPredicate(aggSetRuleHead.getPredicateName(), aggSetRuleHead.getAriety());
    //if aggregate in rule has only one literal in the conjunction of the aggregate and there are no external vars
    //do not create rule for generating aggSet, but use directly that literal as AggSet
    bool aggLitCanBeAggSet = false;
    if(relWithAgg.getAggregate().getAggregateLiterals().size() == 1 && relWithAgg.getAggregate().getAggregateInequalities().size() == 0){
        //the above condition is satisfied if all terms of aggSetRuleHead are inside the single literal in conj
        std::unordered_set<std::string> conjTermsSet;
        for(std::string t : relWithAgg.getAggregate().getAggregateLiterals().at(0).getTerms())
            conjTermsSet.insert(t);
        aggLitCanBeAggSet = true;
        for(std::string term : aggSetRuleHead.getTerms()){
            if(!conjTermsSet.count(term)){
                aggLitCanBeAggSet = false;
            }
        }

    }
    if(!aggLitCanBeAggSet){
        std::vector<aspc::ArithmeticRelation> aggSetRuleArithRel;
        for(const aspc::ArithmeticRelation& rel : rule.getArithmeticRelations()) aggSetRuleArithRel.push_back(rel);
        for(const aspc::ArithmeticRelation& rel : rule.getArithmeticRelationsWithAggregate().at(0).getAggregate().getAggregateInequalities()) aggSetRuleArithRel.push_back(rel);
        //rule for generating aggSet
        aspc::Rule aggSetRule({aggSetRuleHead}, aggSetBody, aggSetRuleArithRel,{}, false);
        std::cout <<"Created aggSet rule with id: " << aggSetRule.getRuleId()<< "\n";
        rewrittenProgram.addRule(aggSetRule);
    }
    //create normal rule with agg_set in body
    aspc::Literal aggSetLiteral(false, aggSetRuleHead);
    
    std::vector<aspc::Literal> aggLiterals;
    if(aggLitCanBeAggSet)
        aggLiterals.push_back(relWithAgg.getAggregate().getAggregateLiterals().at(0));
    else
        aggLiterals.push_back(aggSetLiteral);
    aspc::ArithmeticRelationWithAggregate rewrittenAggregate(false, relWithAgg.getGuard(), aspc::Aggregate(aggLiterals, {},
        relWithAgg.getAggregate().getAggregateVariables(), relWithAgg.getAggregate().getAggregateFunction()), relWithAgg.getComparisonType(), relWithAgg.isNegated()
    );
    std::vector<aspc::Literal> bodyLits;
    //rule made of body + aggregate
    if(generateBodyRule){
        bodyLits.push_back(joinBodyLiteral);
    }
    else{// join rule for body was not generated
        //body is made of a signle literal and no join rule was created
        if(rule.getBodyLiterals().size() == 1)
            bodyLits.push_back(rule.getBodyLiterals().at(0));
    }
    aspc::Rule ruleWithAggSet(rule.getHead(), bodyLits, {}, {rewrittenAggregate}, false);
    std::cout <<"Created head rule with id: " << ruleWithAggSet.getRuleId()<< "\n";
    rewrittenProgram.addRule(ruleWithAggSet);
    
    nextAggId++;
}