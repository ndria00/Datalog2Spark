#include "SparkJobsCompiler.h"


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
    for(unsigned i = 0; i< lit->getTerms().size(); ++i){
        output = output + ".add(\"term" + std::to_string(i) + "\", DataTypes.StringType)";
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
    for(unsigned i = 0; i < program.getRulesSize(); ++i){
        const aspc::Rule& rule = program.getRule(i);
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
            defineRuleOrdering(program.getRule(id));
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
        deltaName = "delta_" + headLit.getPredicateName() +"_"+ std::to_string(rule.getRuleId());

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
            assert(leftRelation != nullptr);
            std::unordered_map<std::string, std::string> variableRemapping;
            for(auto entry : leftRelation->variableToTerm){
                variableRemapping.emplace(std::make_pair(entry.first, "term" + std::to_string(entry.second)));
            }
            const aspc::ArithmeticRelation* rel = (const aspc::ArithmeticRelation*) formula;
            std::unordered_set<std::string> relationVars;
            rel->addOccurringVariables(relationVars);
            //cast all columns involved in comparison to int
            if(rel->getComparisonType() == aspc::EQ){
                for(std::string var : relationVars){
                    outfile << ind << leftRelation->name << " = " << leftRelation->name << ".withColumn(\"term" << leftRelation->variableToTerm.at(var) << "\", col(\"term" << leftRelation->variableToTerm.at(var) << "\").cast(\"int\"));\n";
                }
            }
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
                    //cast column to int
                    for(std::string var : relationVars){
                        outfile << ind << leftRelation->name << " = " << leftRelation->name << ".withColumn(\"term" << leftRelation->variableToTerm.at(var) << "\", col(\"term" << leftRelation->variableToTerm.at(var) << "\").cast(\"int\"));\n";
                    }
                    //add bound var as last column of the left relation
                    int lastColumn = leftRelation->variableToTerm.size();
                    leftRelation->variableToTerm.emplace(boundedVar, lastColumn);   
                    variableRemapping.emplace(boundedVar, "term" + std::to_string(lastColumn));

                }
                boundVars.insert(boundedVar);
            }
        }else{
            const aspc::Literal* lit = (const aspc::Literal*) formula;
            for(std::string var : lit->getVariables()){
                boundVars.insert(var);
            }
            // zero arity predicates are all bound and are considered before all other predicates
            // a zero arity predicate p in the body is true if its corresponding flag exists_p is set to true
            if(lit->getAriety() == 0){
                //first conjunct
                if(zeroArityIfCondition == ""){
                    std::string negatedLit = lit->isNegated() ? "!" : "";
                    zeroArityIfCondition = zeroArityIfCondition + negatedLit + "exists_" + lit->getPredicateName();
                }
                else{
                    std::string negatedLit = lit->isNegated() ? "!" : "";
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

                //Give name to join (if there is rule id at the end of name trim it) - names are text_ruleId
                size_t pos = leftRelation->name.find_last_of("_");
                if(pos == std::string::npos){
                    newRelationName = leftRelation->name + rightRelation->name + "_" + std::to_string(rule.getRuleId());
                }
                else{
                    newRelationName = leftRelation->name.substr(0, pos) + rightRelation->name + "_" + std::to_string(rule.getRuleId());
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
                    if(!lit->isNegated())
                        outfile << ", \"inner\"";
                    else
                        outfile << ", \"left_anti\"";
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
                    //filter only useful variables
                    int newRelationVariableIndex = 0;
                    //variables that appear in head but are not in the current join are not toKeep
                    for(std::string toKeepVar : headVars){
                        if(toKeepVars.count(toKeepVar) && !leftRelation->variableToTerm.count(toKeepVar) && !rightRelation->variableToTerm.count(toKeepVar))
                            toKeepVars.erase(toKeepVar);
                    }
                    //variables that appear later in the body but not in the join are not toKeep
                    for(std::string toKeepVar : nextBodyVars){
                        if(toKeepVars.count(toKeepVar) && !leftRelation->variableToTerm.count(toKeepVar) && !rightRelation->variableToTerm.count(toKeepVar))
                            toKeepVars.erase(toKeepVar);
                    }
                    std::cout <<"ToKeep vars:  " << toKeepVars.size() << "\n";
                    for(std::string var : toKeepVars){
                        std::cout << var << " ";
                    }
                    std::cout <<"\n";
                    int termIdx = 0;
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
                                outfile <<"col(\"" << currentRelation->name<< ".term" << varNameAndTerm.second << "\").alias(\"term" << termIdx << "\")" << separatorIfNotLast(toKeepVars.size(), 0, ", ");
                                termIdx++;
                                newRelationTerms.emplace(std::make_pair(varNameAndTerm.first, newRelationVariableIndex));
                                newRelationVariableIndex++;
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

void SparkJobsCompiler::defineRuleOrdering(const aspc::Rule& rule){
    ruleOrdering.emplace(std::make_pair(rule.getRuleId(), std::vector<unsigned>()));
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
                if(body[i]-> isBoundedLiteral(boundVars)){
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
                ruleOrdering.at(rule.getRuleId()).push_back(selectedBoundFormula);

            }else{
                currentFormula = body[selectedFormula];
                visitedFormulas[selectedFormula] = true;
                ruleOrdering.at(rule.getRuleId()).push_back(selectedFormula);
                if(body[selectedFormula]->isLiteral()){
                    const aspc::Literal* literal = (const aspc::Literal*) body[selectedFormula];
                    for(std::string var : literal->getVariables()){
                        boundVars.insert(var);
                    }
                }else if(body[selectedFormula]->isBoundedValueAssignment(boundVars)){
                    const aspc::ArithmeticRelation* relation = (const aspc::ArithmeticRelation*) body[selectedFormula];
                    boundVars.insert(relation->getAssignedVariable(boundVars));

                }else
                    assert(false);
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
        outfile << ind++ << "if(Main.instanceFileExists(instancePath + \"" << predName << ".csv\", session))\n";
        outfile << ind << predName << " = session.read().format(\"csv\").option(\"header\", false).schema(\"";
        for(int i = 0; i < predArity; ++i){
            if(i != predArity-1)
                outfile << "term" << i << " string, ";
            else
                outfile << "term" << i << " string";
        }
        outfile << "\").option(\"sep\", \";\").load(instancePath + \"" << predName << ".csv\");\n";
        --ind;
        outfile << ind++ << "else\n";
        outfile  << ind << predName << " = " << compileEmptyDatasetWithLitTerms(lit) << ";\n";
        --ind;
    }else{
        outfile << ind <<"boolean exists_" << predName << " = Main.instanceFileExists(instancePath + \"" << predName << ".csv\", session);\n";
    }
    

}