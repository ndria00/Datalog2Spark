#include "SparkJobsCompiler.h"


//term that appears in aggregate should be float(they can be inferred)
//
std::unordered_map<std::string,std::string> SparkJobsCompiler::aggregateToFunction = {
    {"#count", "count"}, //count all -> int
    {"#sum", "sum"},     // float -> float
    {"#max", "max"},     // float -> float
    {"#min", "min"},     //float -> float
    {"#avg", "avg"},     //always float
    {"#median", ""},     //always float
    {"#stddev", ""},     //always float
    {"#var", ""}         //always float
};

//TODO check default values
std::unordered_map<std::string,std::string> SparkJobsCompiler::aggregateToDefaultValue = {
    {"#count", "0"},
    {"#sum", "0"},
    {"#max", std::to_string(std::numeric_limits<float>::min())},
    {"#min", std::to_string(std::numeric_limits<float>::max())},
    {"#avg", "0"},
    {"#median", "0"},
    {"#stddev", "0"},
    {"#var", "0"}
};

std::unordered_map<SparkJobsCompiler::JoinType, std::string> SparkJobsCompiler::JoinTypeToSparkJoin = {
    {SparkJobsCompiler::JoinType::INNER, "inner"},
    {SparkJobsCompiler::JoinType::ANTI, "left_anti"},
    {SparkJobsCompiler::JoinType::LEFT, "left"},
};

std::string SparkJobsCompiler::AGGREGATE_LIT_RESULT = "aggrRes";

SparkJobsCompiler::SparkJobsCompiler(const aspc::Program& program): program(program), ind(Indentation(0)){

}

void SparkJobsCompiler::compile(){
    dependencyManager.buildDependecyGraph(program);
    if(!program.isStratified()){
        std::cout << "Spark compilation only works for stratified programs\n";
        exit(180);
    }
    openMainFile();
    importAndOpenMainMethod();
    compileProgram();
    closeMainFile();
}


void SparkJobsCompiler::openMainFile(){
    std::string filePath = "../SparkApplication/src/main/java/application/Main.java";
    outfile =  std::ofstream(filePath);
    ind = Indentation(0);
    if(!outfile.is_open()){
        std::cout << "Error unable to create java Main " << std::endl;
        exit(180);
    }
}

void SparkJobsCompiler::compileCheckFileExists(){
    outfile << ind++ << "public static boolean instanceFileExists(String filePath, SparkSession session) {\n";
    outfile << ind++ << "try {\n";
    outfile << ind << "Path path = new Path(filePath);\n";
    outfile << ind << "FileSystem fs = path.getFileSystem(session.sparkContext().hadoopConfiguration());\n";
    outfile << ind << "return fs.exists(path);\n";
    outfile << --ind << "}\n";
    outfile << ind++ <<"catch (Exception e) {\n";
    outfile << ind << "return false;\n";
    outfile << --ind << "}\n";
    outfile << --ind << "}\n";
}

std::string SparkJobsCompiler::compileEmptyDatasetWithLitTerms(const aspc::Literal* lit){
    std::string output = "";
    output = "session.createDataFrame(Collections.emptyList(), new StructType()";
    const aspc::TypeDirective* directive = program.getTypeDirectiveByPredicateName(lit->getPredicateName());
    for(unsigned i = 0; i< lit->getTerms().size(); ++i){
        std::string termType = aspc::TypeDirective::INT_TYPE;
        if(directive != nullptr)
            termType = directive->getTermTypeFromPos(i);
        output = output + ".add(\"term" + std::to_string(i) + "\", \"" + termType + "\")";
    }
    output = output + ")";
    return output;
}


void SparkJobsCompiler::importAndOpenMainMethod(){
    outfile << ind << "package application;\n";
    outfile << ind << "import org.apache.spark.sql.Dataset;\n";
    outfile << ind << "import org.apache.spark.sql.Row;\n";
    outfile << ind << "import org.apache.spark.sql.SparkSession;\n";
    outfile << ind << "import org.apache.spark.sql.types.StructType;\n";
    outfile << ind << "import org.apache.spark.sql.types.DataTypes;\n";
    outfile << ind << "import static org.apache.spark.sql.functions.*;\n";
    outfile << ind << "import org.apache.hadoop.fs.Path;\n";
    outfile << ind << "import org.apache.hadoop.fs.FileSystem;\n";
    outfile << ind << "import java.util.HashMap;\n";
    outfile << ind << "import java.util.List;\n";
    outfile << ind << "import java.util.Map;\n";
    outfile << ind << "import java.util.Collections;\n";
    outfile << ind++ << "public class Main{\n";
    compileCheckFileExists();
    outfile << ind++ << "public static void main(String[] args){\n";
    // outfile << ind << "SparkSession session = new SparkSession.Builder().appName(\"test\").master(\"spark://eracle:7077\").getOrCreate();\n";
    outfile << ind << "SparkSession session = new SparkSession.Builder().appName(\"test\").master(\"local\").getOrCreate();\n";
    outfile << ind << "session.sparkContext().setLogLevel(\"error\");\n";
    outfile << ind++ << "if(args.length != 2){\n";
    outfile << ind << "System.out.println(\"Excute with two arguments: a path to instance folder and a path to output folder\");\n";
    outfile << ind << "System.exit(1);\n";
    outfile << --ind << "}\n";
    outfile << ind << "String instancePath = args[0];\n";
    outfile << ind << "String outputPath = args[1];\n";
    outfile << ind++ << "if(instancePath.charAt(instancePath.length()-1) != \'/\' && instancePath.charAt(instancePath.length()-1) != \'\\\\')\n";
    outfile << ind << "instancePath = instancePath + \'/\';\n";
    --ind;
    outfile << ind++ << "if(outputPath.charAt(outputPath.length()-1) != \'/\' && outputPath.charAt(outputPath.length()-1) != \'\\\\')\n";
    outfile << ind << "outputPath = outputPath + \'/\';\n";
    --ind;
    outfile << ind << "System.out.println(\"Opening instansce folder at: \" + instancePath);\n";
    outfile << ind << "System.out.println(\"Ouput folder at: \" + outputPath);\n";
}

void SparkJobsCompiler::compileProgram(){
    auto sccs = dependencyManager.getSCC();
    std::unordered_set<std::string> allProgramPredicates;
    for(const aspc::Rule& rule : program.getRules()){
        //assuming only one head
        allProgramPredicates.insert(rule.getHead().at(0).getPredicateName());
        headPredicates.insert(rule.getHead().at(0).getPredicateName());
        if(rule.getHead().at(0).getAriety() == 0)
                zeroArityPredicates.insert(rule.getHead().at(0).getPredicateName());
        for(const aspc::Literal& lit : rule.getBodyLiterals()){
            allProgramPredicates.insert(lit.getPredicateName());
            if(lit.getAriety() == 0)
                zeroArityPredicates.insert(lit.getPredicateName());
        }
    }
    if(zeroArityPredicates.size() > 0){
        outfile << ind << "StructType emptySchema = new StructType();\n";
        outfile << ind << "emptySchema = emptySchema.add(\"dummy\", DataTypes.StringType);\n";
        outfile << ind << "Dataset<Row> emptyDF = session.createDataFrame(Collections.emptyList(),emptySchema);\n";
    }
    for(int i = sccs.size() -1; i >=0; --i)
        computeToUnpersistDatasets(sccs, i, allProgramPredicates);
        
    for(int i = sccs.size() -1; i >= 0; --i){
        compileSCC(sccs[i], i);
    }
}

void SparkJobsCompiler::compileSCC(std::vector<int>& scc, int i){
    //debug print
    std::cout <<"Compiling component{";
    for(int i = 0; i< scc.size(); ++i){
        if(i != scc.size()-1)
            std::cout << dependencyManager.getPredicateName(scc[i]) << ", ";
        else
            std::cout << dependencyManager.getPredicateName(scc[i]);
    }
    std::cout << "}\n";
    
    for(auto pred : scc){
        std::string predName = dependencyManager.getPredicateName(pred);
        for(int id : program.getRulesForPredicate(predName)){
            if(!program.getRule(id).containsAggregate())
                defineRuleOrdering(id);
            else
                ruleOrdering[id] = {0,1}; //rule with aggregate are normalized and are of the form h :- bodyLit(...), aggr.
            std::cout <<"Rule Ordering for ";
            program.getRule(id).print();
            for(unsigned i = 0; i < ruleOrdering.at(id).size(); ++i){
                std::cout << ruleOrdering.at(id)[i] << " ";
            }
            std::cout << "\n";
            //give declare delta as true if there are multiple rules defining the same predicate
            compileRule(id, program.getRulesForPredicate(predName).size() > 1);
        }
        //merge deltas
        if(declaredDeltas.size() > 1){
            outfile << ind << predName << " = " << predName;
            for(unsigned  i = 0; i < declaredDeltas.size(); ++i){
                std::string deltaName = declaredDeltas[i];
                outfile << ".union(" << deltaName <<").dropDuplicates()";
            }
            outfile << ";\n";
            declaredDeltas.clear();
        }
    }
    for(std::string pred : unpersistDatasetsAfterComponent[i]){
        if(!unpersistedPredicates.count(pred)){
            unpersistedPredicates.insert(pred);
            //predicates that are edb do not need to be written
            if(headPredicates.count(pred)){
                if(zeroArityPredicates.count(pred)){
                    outfile << ind++ << "if(exists_" << pred << ")\n";
                    outfile << ind << "emptyDF.write().mode(\"overwrite\").option(\"header\", \"false\").option(\"delimiter\", \";\").csv(outputPath + \"/" << pred << "\");\n";
                    --ind;
                }else{
                    outfile << ind << pred << ".count();\n";
                    outfile << ind << pred << ".write().mode(\"overwrite\").option(\"header\", \"false\").option(\"delimiter\", \";\").csv(outputPath + \"/" << pred << "\");\n";
                    outfile << ind << pred << ".unpersist();\n";
                }
            }
        }
    }
}

void SparkJobsCompiler::computeToUnpersistDatasets(std::vector<std::vector<int>>& sccs, int scc, std::unordered_set<std::string>& allPredicates){
    std::unordered_set<std::string> canRemove(allPredicates.begin(), allPredicates.end());
    for(int i = scc-1; i >=0; --i){
        std::vector<int> scc = sccs[i];
        for(auto pred : scc){
            for(int id : program.getRulesForPredicate(dependencyManager.getPredicateName(pred))){
                const aspc::Rule& rule = program.getRule(id);
                canRemove.erase(rule.getHead().at(0).getPredicateName());
                for(const aspc::Literal& lit : rule.getBodyLiterals()){
                    canRemove.erase(lit.getPredicateName());
                }
                if(rule.containsAggregate()){
                    for(const aspc::Literal& lit : rule.getArithmeticRelationsWithAggregate().at(0).getAggregate().getAggregateLiterals()){
                        canRemove.erase(lit.getPredicateName());
                    }
                }
            }

        }
    }
    unpersistDatasetsAfterComponent.emplace(std::make_pair(scc, std::unordered_set<std::string>()));
    for(std::string toRemove : canRemove){
        unpersistDatasetsAfterComponent.at(scc).insert(toRemove);
    }
}

void SparkJobsCompiler::compileRule(unsigned id, bool declareDelta){
    //outfile <<"\n";
    outfile << ind << "//Compilation of rule " << id << "\n";
    std::cout <<"\tCompiling rule ";
    const aspc::Rule& rule = program.getRule(id);
    rule.print();
    auto body = rule.getFormulas();
    auto head = rule.getHead();
    //assuming only one head
    aspc::Literal headLit(false, head[0]);
    std::unordered_set<std::string> headVars(headLit.getVariables().begin(), headLit.getVariables().end());
    std::unordered_set<std::string> boundVars;
    Relation* leftRelation = nullptr;
    Relation* rightRelation = nullptr;

    bool foundZeroArityIf = false;
    bool printedZeroArityIf = false; 
    std::string zeroArityIfCondition = "";
    std::string deltaName;
    if(declareDelta)
        deltaName = "delta_" + headLit.getPredicateName() +"_"+ std::to_string(id);

    //do not compute joins if head is already true
    if(headLit.getAriety() == 0){
        foundZeroArityIf = true;
        zeroArityIfCondition =  "!exists_" + headLit.getPredicateName();
    }
    //do also load of head pred
    if(!loadedPredicates.count(headLit.getPredicateName())){
        printPredicateLoading(&headLit);
        loadedPredicates.insert(headLit.getPredicateName());
    }
    for(unsigned i = 0; i < rule.getBodyLiterals().size(); ++i){
        const aspc::Literal* lit = (const aspc::Literal*) body[i];
        if(!loadedPredicates.count(lit->getPredicateName())){
            printPredicateLoading(lit);
            loadedPredicates.insert(lit->getPredicateName());
        }
    }
    std::vector<unsigned> ruleOrder = ruleOrdering.at(id);
    for(unsigned i = 0; i < ruleOrder.size(); ++i){
        std::string newRelationName;
        const aspc::Formula* formula = body[ruleOrder[i]];
        if(!formula->isLiteral()){
            if(formula->containsAggregate()){
                assert(leftRelation != nullptr);
                std::unordered_map<std::string, std::string> variableRemapping;
                for(auto entry : leftRelation->variableToTerm){
                    variableRemapping.emplace(std::make_pair(entry.first, "term" + std::to_string(entry.second)));
                }
                const aspc::ArithmeticRelationWithAggregate* aggrRel = (const aspc::ArithmeticRelationWithAggregate*) formula;
                // get agg_set
                const aspc::Literal aggrLit = (const aspc::Literal) aggrRel->getAggregate().getAggregateLiterals().at(0);
                rightRelation = new Relation();
                rightRelation->name =  aggrLit.getPredicateName() + "_" + std::to_string(id);
                //get body vars
                std::unordered_set<std::string> externalVars =  computeExternalVariablesForAggregate(id, ruleOrder[i]);
                std::vector<std::string> aggSetTerms = aggrRel->getAggregate().getAggregateLiterals().at(0).getTerms();
                
                int termIdx = 0;
                std::vector<std::pair<std::string,std::string>> groupVariables;
                for(int varIdx = 0; varIdx < aggSetTerms.size(); ++varIdx){
                    if(isVariable(aggSetTerms[varIdx]))
                        boundVars.insert(aggSetTerms[varIdx]);
                    if(rightRelation->variableToTerm.emplace(aggSetTerms[varIdx], termIdx).second){
                        if(externalVars.count(aggSetTerms[varIdx])){
                            groupVariables.push_back(std::make_pair(aggSetTerms[varIdx], "term" + std::to_string(termIdx)));
                        }
                        termIdx++;
                        // if(variableRemapping.emplace(aggSetTerms[varIdx], "term" + std::to_string(termIdx)).second)
                        //     termIdx++;

                    }
                }
                outfile << ind << "Dataset<Row> " << rightRelation->name << " = " << aggrLit.getPredicateName() << ".groupBy(";

                for(unsigned groupVarIdx = 0; groupVarIdx < groupVariables.size(); ++groupVarIdx){
                    outfile << "\"" << groupVariables[groupVarIdx].second << "\"" << separatorIfNotLast(groupVarIdx, groupVariables.size()-1, ", ");
                }
                //close groupBy
                outfile << ").agg(";

                //first var of the symbolic set of the aggregate            
                std::string aggrSetAggVariable =  aggrRel->getAggregate().getAggregateVariables().at(0);
                int aggrSetAggTermCol;
                std::string aggrFunction = SparkJobsCompiler::aggregateToFunction[aggrRel->getAggregate().getAggregateFunction()];
                std::string aggrName = aggrRel->getAggregate().getAggregateFunction();
                if(isVariable(aggrSetAggVariable)){
                    aggrSetAggTermCol = rightRelation->variableToTerm.at(aggrSetAggVariable);
                    outfile << aggrFunction << "(\"term" << aggrSetAggTermCol << "\")";
                }else{//first var is constant
                    std::string aggSetTermsLit;
                    if(isInteger(aggrSetAggVariable))
                        aggSetTermsLit = "lit(" + aggrSetAggVariable + ")";
                    else
                        aggSetTermsLit = "lit(\"" + aggrSetAggVariable + "\")";
                    outfile << aggrFunction << "(" << aggSetTermsLit << ")";
                }
                //aggregation function
                //add aggregated column as new col of the grouped dataset
                int aggrResColNumber;
                aggrResColNumber = groupVariables.size();
                
                outfile <<".as(\"term" << aggrResColNumber << "\")";
                //close agg
                //aggregation column is always selected for checking the aggregate value with the guard or as value assignment
                outfile << ").select(";
                std::unordered_map <std::string, int> aggrRelationTerms;
                std::string aggrTermCol;
                int newTermIdx = 0;
                for(auto pair : groupVariables){
                    if(newTermIdx == groupVariables.size())
                        outfile << "col(\"term" << rightRelation->variableToTerm[pair.first] << "\").as(\"term" << newTermIdx << "\")";
                    else
                        outfile << "col(\"term" << rightRelation->variableToTerm[pair.first] << "\").as(\"term" << newTermIdx << "\"), ";
                    aggrRelationTerms.emplace(pair.first, newTermIdx);
                    newTermIdx++;
                }
                
                //join body with aggSet and then apply guard
                std::unordered_set<std::string> toKeepVars;
                std::vector<std::string> guardTerms = aggrRel->getGuard().getAllTerms();
                std::unordered_set<std::string> emptyBoundVars;

                //agregate res is always the last column
                outfile << "col(\"term" << aggrResColNumber << "\").alias(\"term" << newTermIdx << "\"));\n"; // close select
                aggrResColNumber = newTermIdx;
                    
                rightRelation->variableToTerm.clear();
                for(auto pair : aggrRelationTerms){
                    rightRelation->variableToTerm.emplace(pair.first, pair.second);
                    variableRemapping.emplace(pair.first, "term" + pair.second);
                }
                std::string originalAggregationColName = "term"+ std::to_string(aggrResColNumber);
                rightRelation->variableToTerm.emplace(originalAggregationColName, aggrResColNumber);
                variableRemapping.emplace(originalAggregationColName, originalAggregationColName);
                toKeepVars.emplace(originalAggregationColName);
                

                //keep all guard variables for assigning/checking default aggr value after left join
                for(unsigned guardTermIdx = 0; guardTermIdx < guardTerms.size(); ++guardTermIdx)
                    if(isVariable(guardTerms[guardTermIdx]))
                        toKeepVars.insert(guardTerms[guardTermIdx]);


                std::string boundedVar = "";
                //guard is bound
                if(aggrRel->isBoundedValueAssignment(boundVars)){
                    boundedVar = aggrRel->getAssignedVariable(emptyBoundVars);
                    //if bound and single term then we have #count{...} = T or #count{...} = constant
                    //std::string newColumnCreateCommand = "";
                    if(!aggrRel->getGuard().isSingleTerm() || !isVariable(aggrRel->getGuard().getStringRep())){
                        //add bound var as last column of the left relation
                        int lastColumn = rightRelation->variableToTerm.size();
                        rightRelation->variableToTerm.emplace(boundedVar, lastColumn); 
                        const aspc::ArithmeticExpression expr = (const aspc::ArithmeticExpression) aggrRel->getGuard();
                        outfile << ind << rightRelation->name << " = " << rightRelation->name << ".withColumn(\"term" << rightRelation->variableToTerm.at(boundedVar) << "\", expr(\"" << aggrRel->getAssignmentAsStringForRelation(variableRemapping, originalAggregationColName, false, "") << "\"));\n";  
                        variableRemapping.emplace(boundedVar, "term" + std::to_string(lastColumn));
                    }else{
                        //erase aggregation column from relation and subsistute it with the new mapping
                        //Example #count{...} produces term_n that maps to no variable
                        //#count{...} = C produces term_n that maps to no variable, but now it can map directly to C without adding a new col
                        rightRelation->variableToTerm.erase(originalAggregationColName);
                        variableRemapping.erase(originalAggregationColName);
                        variableRemapping.emplace(boundedVar, originalAggregationColName);
                        rightRelation->variableToTerm.emplace(boundedVar, aggrResColNumber);
                        toKeepVars.insert(boundedVar);
                    }
                }else{
                    
                    //keep aggrVar
                    toKeepVars.insert(originalAggregationColName);
                    //aggr is not an assignment -> do a filter
                    outfile << ind << rightRelation->name << " = " << rightRelation->name << ".where(\"term" << aggrResColNumber << " " << aspc::ArithmeticRelation::comparisonType2String[aggrRel->getComparisonType()] << " " << aggrRel->getGuard().getStringRepWithRemapping(variableRemapping) << "\");\n";
                }
                //no next body vars - rules are normalized and aggregate is evaluated as last
                std::unordered_set<std::string> nextBodyVars;
                //variables appearing in head have to be kept
                headLit.addVariablesToSet(toKeepVars);

                //TODO check for negation
                std::unordered_map<std::string, std::string> oldTermsToNewTerms = printJoinBetweenRelations(leftRelation, rightRelation, newRelationName, JoinType::LEFT, id, headVars, toKeepVars, nextBodyVars);
                std::string assignedValColumnName = "";
                std::unordered_map<std::string, std::string> oldRemapping(variableRemapping.begin(), variableRemapping.end());
                variableRemapping.clear();
                //update remapping so that the value of the aggregation column can be calculated for tuples in left join that are not in inner join
                // c->1 and term1->term2
                for(auto pair : oldRemapping){
                    variableRemapping[pair.first] = oldTermsToNewTerms[pair.second];
                }
                std::string newAggregationColName = oldTermsToNewTerms[originalAggregationColName];
                if(aggrRel->isBoundedValueAssignment(boundVars)){
                    outfile << ind << newRelationName << " = " << newRelationName << ".withColumn(\"" << variableRemapping[boundedVar] << "\", coalesce(col(\"" << newAggregationColName << "\"),";
                    variableRemapping.erase(boundedVar);
                    outfile <<" expr(\"" << aggrRel->getAssignmentAsStringForRelation(variableRemapping, newAggregationColName, true, SparkJobsCompiler::aggregateToDefaultValue[aggrName])<< "\")));\n";
                }else{
                    outfile << ind << newRelationName << " = " << newRelationName << ".where(\"" << SparkJobsCompiler::aggregateToDefaultValue[aggrName] << " " << aspc::ArithmeticRelation::comparisonType2String[aggrRel->getComparisonType()] << " " << aggrRel->getGuard().getStringRepWithRemapping(variableRemapping) << "\");\n";
                }
                //switch relations
                delete leftRelation;
                leftRelation = rightRelation;
                rightRelation = nullptr;
                leftRelation->name =  newRelationName;
                
            }else{
                assert(leftRelation != nullptr);
                std::unordered_map<std::string, std::string> variableRemapping;
                for(auto entry : leftRelation->variableToTerm){
                    variableRemapping.emplace(std::make_pair(entry.first, "term" + std::to_string(entry.second)));
                }
                const aspc::ArithmeticRelation* rel = (const aspc::ArithmeticRelation*) formula;
                std::unordered_set<std::string> relationVars;
                rel->addOccurringVariables(relationVars);
                //cast all columns involved in comparison to int
                if(formula->isBoundedRelation(boundVars)){
                    //filter according to arithmetic
                    outfile << ind << leftRelation->name << " = " << leftRelation->name << ".filter(\"" << rel->getStringRepWithRemapping(variableRemapping) << "\");\n";                    
                    
                }else{
                    std::string boundedVar = rel->getAssignedVariable(boundVars);
                    //add new column according to value assignment
                    bool toKeepVar = false;
                    if(headLit.getVariables().count(boundedVar))
                        toKeepVar = true;
                    std::unordered_set<std::string> toKeepVars; 
                    for(unsigned j = i+1; j < ruleOrder.size(); ++j){
                        body[ruleOrder[j]]->addVariablesToSet(toKeepVars);
                    }
                    if(toKeepVars.count(boundedVar)){
                        toKeepVar = true;
                    }
                    //compile add column
                    if(toKeepVar){
                        //add bound var as last column of the left relation
                        int lastColumn = leftRelation->variableToTerm.size();
                        leftRelation->variableToTerm.emplace(boundedVar, lastColumn); 
                        variableRemapping.emplace(boundedVar, "term" + std::to_string(lastColumn));
                        outfile << ind << leftRelation->name << " = " << leftRelation->name << ".withColumn(\"term" << leftRelation->variableToTerm.at(boundedVar) << "\", expr(\"" << rel->getStringRepWithRemapping(variableRemapping) << "\"));\n";  
                    }                    
                    boundVars.insert(boundedVar);
                }
            }
        }else{
            const aspc::Literal* lit = (const aspc::Literal*) formula;
            for(std::string var : lit->getVariables()){
                boundVars.insert(var);
            }
            // zero arity predicates are all bound and are considered before all other predicates
            // a zero arity predicate p in the body is true if its corresponding flag exists_p is set to true
            if(lit->getAriety() == 0){
                std::string negatedLit = lit->isNegated() ? "!" : "";
                //first conjunct
                if(zeroArityIfCondition == ""){
                    zeroArityIfCondition = zeroArityIfCondition + negatedLit + "exists_" + lit->getPredicateName();
                }
                else{
                    zeroArityIfCondition = zeroArityIfCondition + " && " + negatedLit + "exists_" + lit->getPredicateName();
                }
                foundZeroArityIf = true;
                //if rule only contains zero arity predicates in the body
                //head derivation must be printed, otherwise just construct the if and continue
                if(i != ruleOrder.size()-1)
                    continue;
            }else{
                //zero arity preds have been compiled, now the if can be printed
                if(foundZeroArityIf && !printedZeroArityIf){
                    printedZeroArityIf = true;
                    //no delta for zero arity predicates even if multiple rules of the same pred are present
                    if(headLit.getAriety() > 0){
                        if(declareDelta)
                            outfile << ind << "Dataset<Row> " << deltaName << " = " << compileEmptyDatasetWithLitTerms(&headLit) <<";\n";
                    }
                    //zero arity if for existence
                    outfile << ind++ << "if(" << zeroArityIfCondition << "){\n";
                }
            }
            
            if(leftRelation == nullptr){
                leftRelation = new Relation();
                leftRelation->name = lit->getPredicateName();
                compileFilterConstantsAndPojectSameVariables(leftRelation, lit);
            }else{
                assert(leftRelation != nullptr);
                rightRelation = new Relation();
                rightRelation->name = lit->getPredicateName();
                compileFilterConstantsAndPojectSameVariables(rightRelation, lit);
            }
            //compile join between left and right relation
            //then right relation becomes left relation
            if(rightRelation != nullptr){
                //compile
                std::unordered_set<std::string> toKeepVars;
                std::unordered_set<std::string> nextBodyVars;
                //variables appearing in head have to be kept
                headLit.addVariablesToSet(toKeepVars);
                //variables needed by next joins have to be kept too
                for(unsigned j = i+1; j < ruleOrder.size(); ++j){
                    body[ruleOrder[j]]->addVariablesToSet(toKeepVars);
                    body[ruleOrder[j]]->addVariablesToSet(nextBodyVars);
                }
                if(lit->isNegated())
                    printJoinBetweenRelations(leftRelation, rightRelation, newRelationName, JoinType::ANTI, id, headVars, toKeepVars, nextBodyVars);
                else
                    printJoinBetweenRelations(leftRelation, rightRelation, newRelationName, JoinType::INNER, id, headVars, toKeepVars, nextBodyVars);
                //switch relations
                delete leftRelation;
                leftRelation = rightRelation;
                rightRelation = nullptr;
                leftRelation->name =  newRelationName;
            }
        }
        //rule is firing
        if(i == body.size()-1){
            //rule is only made of zero arity literals and if has not been printed
            if(foundZeroArityIf && !printedZeroArityIf){
                // if(!zeroArityPredicates.count(headLit.getPredicateName()))
                //     outfile << ind << "Dataset<Row> " << deltaName << " = " << compileEmptyDatasetWithLitTerms(headLit) << ";\n";
                outfile << ind++ << "if(" << zeroArityIfCondition << "){\n";
            }
            if(!declareDelta){
                if(!zeroArityPredicates.count(headLit.getPredicateName())){
                    //select columns from last join and possibly add constants
                    outfile << ind << headLit.getPredicateName() << " = " << headLit.getPredicateName() << ".union(" << leftRelation->name << ".select(";
                    for(unsigned headTermIdx = 0; headTermIdx < headLit.getTerms().size(); ++headTermIdx){
                        if(headLit.isVariableTermAt(headTermIdx)){
                            outfile << "col(\"term" << leftRelation->variableToTerm.at(headLit.getTermAt(headTermIdx)) << "\").as(\"term" << headTermIdx << "\")" << separatorIfNotLast(headTermIdx, headLit.getTerms().size()-1, ", ");
                        }else{
                            if(isInteger(headLit.getTermAt(headTermIdx)))
                                outfile << "lit(" << headLit.getTermAt(headTermIdx) << ").as(\"term" << headTermIdx << "\")" << separatorIfNotLast(headTermIdx, headLit.getTerms().size()-1, ", ");
                            else
                                outfile << "lit(\"" << headLit.getTermAt(headTermIdx) << "\").as(\"term" << headTermIdx << "\")" << separatorIfNotLast(headTermIdx, headLit.getTerms().size()-1, ", ");
                        }
                    }
                    outfile << ")).dropDuplicates();\n";
                }else{
                    //full zero arity body  -> head is true if the printed zero-arity if is satisfied
                    if(!printedZeroArityIf){
                        outfile << ind << "exists_" << headLit.getPredicateName() << " = true;\n";
                    }
                    else{//head is true if at least one join exists for the last relation
                        outfile << ind << "exists_" << headLit.getPredicateName() << " = " << leftRelation->name << ".count() > 0;\n";
                        outfile << ind << leftRelation->name << ".unpersist();\n";
                    }
                }
            }else{
                if(!zeroArityPredicates.count(headLit.getPredicateName())){
                    //when if for zero arity predicate is printed deltas are already declared
                    if(!foundZeroArityIf)
                        outfile << ind <<"Dataset<Row> " << deltaName << " = " << compileEmptyDatasetWithLitTerms(&headLit) << ";\n";
                    newRelationName = deltaName;
                    //select head terms
                    outfile << ind << newRelationName << " = " << leftRelation->name << ".select(";
                    int termIdx = 0;
                    for(unsigned headTermIdx = 0; headTermIdx < headLit.getTerms().size(); ++headTermIdx){
                        if(headLit.isVariableTermAt(headTermIdx)){
                            outfile << "col(\"term" << leftRelation->variableToTerm.at(headLit.getTermAt(headTermIdx)) << "\").as(\"term" << headTermIdx << "\")" << separatorIfNotLast(headTermIdx, headLit.getTerms().size()-1, ", ");
                        }else{
                            if(isInteger(headLit.getTermAt(headTermIdx)))
                                outfile << "lit(" << headLit.getTermAt(headTermIdx) << ").as(\"term" << headTermIdx << "\")" << separatorIfNotLast(headTermIdx, headLit.getTerms().size()-1, ", ");
                            else
                                outfile << "lit(\"" << headLit.getTermAt(headTermIdx) << "\").as(\"term" << headTermIdx << "\")" << separatorIfNotLast(headTermIdx, headLit.getTerms().size()-1, ", ");
                        }
                    }
                    outfile << ");\n";
                    declaredDeltas.push_back(newRelationName);
                }else{
                    if(!printedZeroArityIf)
                        outfile << ind << "exists_" << headLit.getPredicateName() << " = true;\n";
                    else{
                        outfile << ind << "exists_" << headLit.getPredicateName() << " = " << leftRelation->name << ".count() > 0;\n";
                        outfile << ind << leftRelation->name << ".unpersist();\n";
                    }
                }
            }
        }
    }
    if(leftRelation != nullptr)
        delete leftRelation;
    
    if(foundZeroArityIf){
        outfile << --ind << "}\n";
    }
}

void SparkJobsCompiler::compileFilterConstantsAndPojectSameVariables(Relation* rel, const aspc::Literal* lit){
    std::string filteredRelName = rel->name + "f";
    //no duplicated variables
    if(lit->getVariables().size() == lit->getTerms().size()){
        for(unsigned varIdx = 0; varIdx < lit->getTerms().size(); ++varIdx){
            //<termIdx, Var> where termIdx is the index of column in dataset and Var is the variable of lit to which it corresponds
            rel->variableToTerm.emplace(std::make_pair(lit->getTermAt(varIdx), varIdx));
        }
    }else{
        //a(X, Y, X, 2)
        std::unordered_set litVars = lit->getVariables();
        std::vector<std::pair<std::string, int>> toSelectVariableAndTerm;
        std::vector<std::pair<std::string, std::string>> toFilterTermAndConstant;
        int termIdx = 0;
        bool doSelect =  false;
        for(unsigned varIdx = 0; varIdx < lit->getTerms().size(); ++varIdx){
            if(lit->isVariableTermAt(varIdx)){
                if(litVars.count(lit->getTermAt(varIdx))){
                    //<termIdx, Var> where termIdx is the index of column in dataset and Var is the variable of lit to which it corresponds
                    rel->variableToTerm.emplace(std::make_pair(lit->getTermAt(varIdx), termIdx));
                    toSelectVariableAndTerm.push_back(std::make_pair("term" + std::to_string(varIdx), termIdx));
                    termIdx++;
                    litVars.erase(lit->getTermAt(varIdx));
                }else{
                    doSelect = true;
                }
            }else{
                rel->variableToTerm.emplace(std::make_pair(lit->getTermAt(varIdx), termIdx));
                toFilterTermAndConstant.push_back(std::make_pair("term" + std::to_string(varIdx), lit->getTermAt(varIdx)));
                toSelectVariableAndTerm.push_back(std::make_pair("term" + std::to_string(varIdx), termIdx));
                termIdx++;
            }
        }

        //filtering constants
        if(toFilterTermAndConstant.size() > 0){
            outfile << ind << "Dataset<Row> " << filteredRelName << " = " << rel->name << ".filter(";
            rel->name = filteredRelName;
            for(unsigned constantIdx = 0; constantIdx < toFilterTermAndConstant.size(); ++constantIdx){
                if(isInteger(toFilterTermAndConstant[constantIdx].second))
                    outfile << "col(\"" << toFilterTermAndConstant[constantIdx].first<< "\").equalTo(" << toFilterTermAndConstant[constantIdx].second << ")" << separatorIfNotLast(constantIdx, toFilterTermAndConstant.size() -1, ".and(");
                else 
                    outfile << "col(\"" << toFilterTermAndConstant[constantIdx].first<< "\").equalTo(\"" << toFilterTermAndConstant[constantIdx].second << "\")" << separatorIfNotLast(constantIdx, toFilterTermAndConstant.size() -1, ".and(");                
                if(constantIdx > 0)
                    outfile <<")";
            }
            outfile << ");\n";
        }
        //selecting terms
        if(doSelect){
            outfile << ind << filteredRelName << " = " << rel->name << ".select(";
            rel->name = filteredRelName;
            for(unsigned variableTermIdx = 0; variableTermIdx < toSelectVariableAndTerm.size(); ++variableTermIdx){
                outfile << "col(\"" << toSelectVariableAndTerm[variableTermIdx].first<< "\").as(\"term" << toSelectVariableAndTerm[variableTermIdx].second << "\")" << separatorIfNotLast(variableTermIdx, toSelectVariableAndTerm.size() -1, ", ");
                
            }
            outfile << ");\n";
        }
    }
}

std::string SparkJobsCompiler::separatorIfNotLast(int current, int last, std::string sep){
    if(current == last)
        return "";
    return sep;
}

void SparkJobsCompiler::closeMainFile(){
    outfile << --ind << "}\n";
    outfile << --ind <<"}\n";
    outfile.close();
}

void SparkJobsCompiler::defineRuleOrdering(unsigned id){
    const aspc::Rule& rule = program.getRule(id);
    ruleOrdering.emplace(std::make_pair(id, std::vector<unsigned>()));
    assert(!rule.containsAggregate());
    auto body = rule.getFormulas();
    auto head = rule.getHead();
    std::vector<bool> visitedFormulas(body.size(), false);
    std::unordered_set<std::string> boundVars;
    //assuming only one head
    aspc::Literal headLit(false, head[0]);
    std::unordered_set<std::string> headVars(headLit.getVariables().begin(), headLit.getVariables().end());
    
    unsigned selectedFormula = 0;
    unsigned selectedBoundFormula;
    while(selectedFormula < body.size()){
        unsigned maxSharedHeadVars = 0;
        selectedFormula = body.size();
        selectedBoundFormula = body.size();
        bool notVisited = false;
        for(unsigned i = 0; i < body.size(); ++i){
            if(!visitedFormulas[i]){
                notVisited = false;
                if(body[i]->isBoundedLiteral(boundVars)){
                    selectedBoundFormula = i;
                    selectedFormula = i;
                    break;
                }else if(body[i]->isLiteral() && !body[i]->isBoundedLiteral(boundVars)){
                    const aspc::Literal* literal = (const aspc::Literal*) body[i];
                    if(!literal->isNegated()){
                        unsigned numSharedHeadVars = 0;
                        for(std::string var : literal->getVariables()){
                            if(headVars.count(var))
                                numSharedHeadVars++;
                        }
                        if(numSharedHeadVars > maxSharedHeadVars || maxSharedHeadVars == 0){
                            selectedFormula = i;
                            maxSharedHeadVars = numSharedHeadVars;
                        }
                    }
                }else{
                    if(body[i]->isBoundedRelation(boundVars)){
                        selectedBoundFormula = i;
                        selectedFormula = i;
                        break;
                    }else if(body[i]->isBoundedValueAssignment(boundVars)){
                        //prefer other formulas to bounded value assignment (these add columns to datasets)
                        if(selectedFormula == body.size()){
                            selectedFormula = i;
                            break;
                        }
                    }
                }

            }
        }
        if(selectedFormula != body.size()){
            const aspc::Formula* currentFormula;
            if(selectedBoundFormula != body.size()){
                currentFormula = body[selectedBoundFormula];
                visitedFormulas[selectedBoundFormula] = true;
                ruleOrdering.at(id).push_back(selectedBoundFormula);

            }else{
                currentFormula = body[selectedFormula];
                visitedFormulas[selectedFormula] = true;
                ruleOrdering.at(id).push_back(selectedFormula);
                if(body[selectedFormula]->isLiteral()){
                    const aspc::Literal* literal = (const aspc::Literal*) body[selectedFormula];
                    for(std::string var : literal->getVariables()){
                        boundVars.insert(var);
                    }
                }else if(body[selectedFormula]->isBoundedValueAssignment(boundVars)){
                        const aspc::ArithmeticRelation* relation = (const aspc::ArithmeticRelation*) body[selectedFormula];
                        boundVars.insert(relation->getAssignedVariable(boundVars));
                }
            }
        }else if(notVisited){
            std::cout << "Error ordering rule\n";
            exit(180);
        }
    }
    assert(visitedFormulas.size() == rule.getFormulas().size());
}

void SparkJobsCompiler::printPredicateLoading(const aspc::Literal* lit){
    std::string predName = lit->getPredicateName();
    unsigned predArity = lit->getAriety();
    if(predArity > 0){
        outfile << ind << "Dataset<Row> " << predName << ";\n";
        //do not load predicates that are result of rewriting (there is no fact for such predicates)
        if(predName.rfind(AggregateRewriter::AGG_SET_PREFIX, 0) == std::string::npos && predName.rfind(AggregateRewriter::BODY_PREFIX, 0) == std::string::npos){
            //print loading for input-output predicates or empty dataset for rewriting preds
            if(!nonInterfacePredicates.count(lit->getPredicateName())){
                outfile << ind++ << "if(Main.instanceFileExists(instancePath + \"" << predName << ".csv\", session))\n";
                outfile << ind << predName << " = session.read().format(\"csv\").option(\"header\", false).schema(\"";
                const aspc::TypeDirective* directive = program.getTypeDirectiveByPredicateName(predName);
                if(directive != nullptr){
                    std::cout << "\t type directive for predicate " << predName << " : ";
                    directive->print();
                }
                for(int i = 0; i < predArity; ++i){
                    //default type is string
                    std::string termType = aspc::TypeDirective::INT_TYPE;
                    if(directive != nullptr){
                        termType = directive->getTermTypeFromPos(i);
                    }
                    if(i != predArity-1)
                        outfile << "term" << i << " " << termType << ", ";
                    else
                        outfile << "term" << i << " " << termType;
                }
                outfile << "\").option(\"sep\", \";\").load(instancePath + \"" << predName << ".csv\");\n";
                --ind;
                outfile << ind++ << "else\n";
                outfile  << ind << predName << " = " << compileEmptyDatasetWithLitTerms(lit) << ";\n";
                --ind;
            }else{
                outfile  << ind << predName << " = " << compileEmptyDatasetWithLitTerms(lit) << ";\n";
            }
        }else{
            outfile << ind << predName << " = " << compileEmptyDatasetWithLitTerms(lit) << ";\n";
        }
    }else{
        outfile << ind <<"boolean exists_" << predName << " = Main.instanceFileExists(instancePath + \"" << predName << ".csv\", session);\n";
    }
}



std::unordered_set<std::string> SparkJobsCompiler::computeExternalVariablesForAggregate(unsigned ruleId, unsigned formulaId){
    const aspc::Rule& rule = program.getRule(ruleId);
    const aspc::Formula* formula = rule.getFormulas().at(formulaId);
    //rules with aggregates are normalized
    assert(rule.getArithmeticRelations().size() == 0);
    assert(rule.getFormulas().at(formulaId)->containsAggregate());
    unsigned bodyLiteralIdx =  formulaId == 0 ? 1 : 0;
    const aspc::Formula* f = rule.getFormulas().at(bodyLiteralIdx);
    assert(f->isLiteral());
    const aspc::Literal* lit = (const aspc::Literal*)f;
    std::unordered_set<std::string> externalVars;
    for(std::string var : lit->getVariables()){
        externalVars.insert(var); 
    }
    return externalVars;
}

std::unordered_map<std::string, std::string> SparkJobsCompiler::printJoinBetweenRelations(Relation* leftRelation, Relation* rightRelation, std::string& newRelationName, SparkJobsCompiler::JoinType joinType, unsigned id, std::unordered_set<std::string>& headVars, std::unordered_set<std::string>& toKeepVars, std::unordered_set<std::string>& nextBodyVars){
    std::unordered_map<std::string, std::string> toKeepVarsToNewCols;
    //Give name to join (if there is rule id at the end of name trim it) - names are text_ruleId
    size_t pos = leftRelation->name.find_last_of("_");
    if(pos == std::string::npos){
        newRelationName = leftRelation->name + rightRelation->name + "_" + std::to_string(id);
    }
    else{
        newRelationName = leftRelation->name.substr(0, pos) + rightRelation->name + "_" + std::to_string(id);
    }
    bool cartesian = true;
    std::vector<std::string> joiningVars;
    //define joining vars
    for(auto varNameAndTerm : rightRelation->variableToTerm){
        if(leftRelation->variableToTerm.count(varNameAndTerm.first)){
            cartesian = false;
            joiningVars.push_back(varNameAndTerm.first);
        }
    }

    if(!cartesian){
        //inner join
        outfile << ind << "Dataset<Row> " << newRelationName << " = " << leftRelation->name << ".alias(\"" << leftRelation->name << "\").join(";
        outfile << rightRelation->name << ".alias(\"" << rightRelation->name << "\"), ";
        //join condition
        for(int joiningVarIdx = 0; joiningVarIdx < joiningVars.size(); ++joiningVarIdx){
            std::string joiningVar = joiningVars[joiningVarIdx];
            outfile << "col(\"" << leftRelation->name << ".term" << leftRelation->variableToTerm[joiningVar] << "\").equalTo(col(\"" << rightRelation->name << ".term" << rightRelation->variableToTerm[joiningVar] << "\"))" << separatorIfNotLast(joiningVarIdx, joiningVars.size() -1, ".and(");
            //close current and (no and if joinin var is just one)
            if(joiningVarIdx > 0)
                outfile << ")";
        }
        //join type
        outfile << ", \"" << SparkJobsCompiler::JoinTypeToSparkJoin[joinType] << "\"";
        //close join
        outfile << ")";
    }else{
        //cross join
        //TODO if 0 varaibles are selected from right relation, this cartesian can be translated into a .size() > 0 over right relation
        outfile << ind << "Dataset<Row> " << newRelationName << " = " <<leftRelation->name << ".alias(\"" << leftRelation->name << "\").crossJoin(";
        outfile << rightRelation->name << ".alias(\"" << rightRelation->name << "\"))";
    }
    

    if(toKeepVars.size() > 0){
        outfile << ".select(";
        std::unordered_map<std::string, int> newRelationTerms;
        //variables that appear in head but are not in the current join are not toKeep
        for(std::string toKeepVar : headVars){
            if(toKeepVars.count(toKeepVar) && !leftRelation->variableToTerm.count(toKeepVar) && !rightRelation->variableToTerm.count(toKeepVar)){
                toKeepVars.erase(toKeepVar);
            }
        }
        //variables that appear later in the body but not in the join are not toKeep
        for(std::string toKeepVar : nextBodyVars){
            if(toKeepVars.count(toKeepVar) && !leftRelation->variableToTerm.count(toKeepVar) && !rightRelation->variableToTerm.count(toKeepVar)){
                toKeepVars.erase(toKeepVar);
            }
        }
        std::cout <<"ToKeep vars:  " << toKeepVars.size() << "\n";
        for(std::string var : toKeepVars){
            std::cout << var << " ";
        }
        std::cout <<"\n";
        int newTermIdx = 0;
        //print selection with aliases
        //each term of left and right relation is taken and has as name termn
        //with n the position it occupies in the new relation
        for(unsigned i = 0; i < 2; ++i){
            Relation* currentRelation;
            if(i == 0) currentRelation = leftRelation;
            else currentRelation = rightRelation;

            for(auto varNameAndTerm : currentRelation->variableToTerm){
                //take first occurence of each toKeep variable
                if(toKeepVars.count(varNameAndTerm.first)){
                    toKeepVars.erase(varNameAndTerm.first);
                    std::string oldTerm = "term" + std::to_string(varNameAndTerm.second);
                    std::string newTerm = "term" + std::to_string(newTermIdx);
                    outfile <<"col(\"" << currentRelation->name<< "." << oldTerm << "\").alias(\"" << newTerm << "\")" << separatorIfNotLast(toKeepVars.size(), 0, ", ");
                    toKeepVarsToNewCols.emplace(std::make_pair(oldTerm, newTerm));
                    newRelationTerms.emplace(std::make_pair(varNameAndTerm.first, newTermIdx));
                    newTermIdx++;
                }
            }
        }
        //close select
        outfile << ")";
        rightRelation->variableToTerm.clear();
        for(auto varNameAndTerm : newRelationTerms){
            rightRelation->variableToTerm.emplace(std::make_pair(varNameAndTerm.first, varNameAndTerm.second));
        }   
    }

    //close join
    outfile <<";\n";
    return toKeepVarsToNewCols;
}