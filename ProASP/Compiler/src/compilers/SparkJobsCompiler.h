#ifndef SPARKJOBSCOMPILER_H
#define SPARKJOBSCOMPILER_H
#include "DependencyManager.h"
#include "../language/TypeDirective.h"
#include "../language/Aggregate.h"
#include "../utils/Indentation.h"
#include "../utils/SharedFunctions.h"
#include "../utils/TypesManager.h"
#include <limits>
#include "AggregateRewriter.h"
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
    enum JoinType{INNER=0, ANTI, LEFT};
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
    void setInputTypes();
    void inferTypes(int);
    void abortDueToTypeMismatch(std::string);
    void checkLiteralTerms(const aspc::Literal&, std::unordered_map<std::string, std::string>&);

    static std::unordered_map<std::string, std::string> aggregateToFunction;
    static std::unordered_map<std::string, std::string> aggregateToDefaultValue;
    static std::unordered_map<JoinType, std::string> JoinTypeToSparkJoin;
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
        void defineRuleOrdering(unsigned id);
        void printPredicateLoading(const aspc::Literal* lit);
        void printPredicateSaving(std::string, bool);
        void printSparkConfiguration();
        std::unordered_set<std::string> computeExternalVariablesForAggregate(unsigned, unsigned);
        std::string printJoinBetweenRelations(Relation*, Relation*, std::string&, SparkJobsCompiler::JoinType, unsigned id, std::unordered_set<std::string>&, std::unordered_set<std::string>&, std::unordered_set<std::string>&, std::string);
};
#endif /*SPARKJOBSCOMPILER_H*/