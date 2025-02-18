#include "DependencyManager.h"
#include "../utils/Indentation.h"
#include "../utils/SharedFunctions.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <optional>
#include <unordered_set>


struct Relation{
    std::string name;
    std::unordered_map<std::string,int> variableToTerm;
    Relation(){}
};

class SparkJobsCompiler{
    DependencyManager dependencyManager;
    std::ofstream outfile;
    Indentation ind;
    aspc::Program program;
    std::unordered_map<unsigned, std::vector<unsigned>> ruleOrdering;
    std::unordered_set<std::string> loadedPredicates;
    std::unordered_map<int, std::unordered_set<std::string>> unpersistDatasetsAfterComponent;
    std::unordered_set<std::string> unpersistedPredicates;
    std::unordered_set<std::string> zeroArityPredicates;
    std::vector<std::string> declaredDeltas;
    std::unordered_set<std::string> headPredicates;
    public:
        SparkJobsCompiler(const aspc::Program&);
        void compile();
        void openMainFile();
        void compileCheckFileExists();
        std::string compileEmptyDatasetWithLitTerms(const aspc::Literal*);
        void importAndOpenMainMethod();
        void compileProgram();
        void compileSCC(std::vector<int>&, int);
        void computeToUnpersistDatasets(std::vector<std::vector<int>>&, int, std::unordered_set<std::string>&);
        void compileRule(unsigned id, bool declareDelta = false);
        void compileFilterConstantsAndPojectSameVariables(Relation*, const aspc::Literal*);
        std::string separatorIfNotLast(int , int, std::string);
        void closeMainFile();
        void defineRuleOrdering(const aspc::Rule&);
        void printPredicateLoading(const aspc::Literal* lit);
};