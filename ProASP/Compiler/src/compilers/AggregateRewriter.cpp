#include "AggregateRewriter.h"

std::string AggregateRewriter::AGG_SET_PREFIX = "Agg_set";
std::string AggregateRewriter::BODY_PREFIX = "Body";

AggregateRewriter::AggregateRewriter(const aspc::Program& program) : program(program), nextAggId(0){
    rewriteAggregates();
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
    std::vector<std::string> headTerms;
    //\rho
    for(std::string var : externalVars){
        if(conjVars.count(var) && headVars.insert(var).second){
            headTerms.push_back(var);
        }
    }
    //V
    for(std::string var : relWithAgg.getAggregate().getAggregateVariables()){
        if(headVars.insert(var).second)
            headTerms.push_back(var);
    }
    for(std::string var : headTerms){
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
    rewrittenProgram.addPredicate(joinBodyLiteral.getPredicateName(), joinBodyLiteral.getAriety());
    aspc::Rule joinRule({joinBodyLiteral.getAtom()}, rule.getBodyLiterals(), rule.getArithmeticRelations(), {}, false);
    std::cout <<"Created join rule with id: " << joinRule.getRuleId()<< "\n";
    rewrittenProgram.addRule(joinRule);
    aggSetBody.push_back(joinBodyLiteral);
    for(const aspc::Literal& lit : relWithAgg.getAggregate().getAggregateLiterals()){
        aggSetBody.push_back(lit);
    }
    rewrittenProgram.addPredicate(aggSetRuleHead.getPredicateName(), aggSetRuleHead.getAriety());
    aspc::Rule aggSetRule({aggSetRuleHead}, aggSetBody, rule.getArithmeticRelations(),{}, false);
    std::cout <<"Created aggSet rule with id: " << aggSetRule.getRuleId()<< "\n";
    rewrittenProgram.addRule(aggSetRule);
 
    //create normal rule with agg_set in body
    aspc::Literal aggSetLiteral(false, aggSetRuleHead);

    aspc::ArithmeticRelationWithAggregate rewrittenAggregate(false, relWithAgg.getGuard(), aspc::Aggregate({aggSetLiteral}, {},
        relWithAgg.getAggregate().getAggregateVariables(), relWithAgg.getAggregate().getAggregateFunction()), relWithAgg.getComparisonType(), relWithAgg.isNegated()
    );
    aspc::Rule ruleWithAggSet(rule.getHead(), {joinBodyLiteral}, rule.getArithmeticRelations(), {rewrittenAggregate}, false);
    std::cout <<"Created headR rule with id: " << ruleWithAggSet.getRuleId()<< "\n";
    rewrittenProgram.addRule(ruleWithAggSet);
    nextAggId++;
}