#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <cassert>
#include "../language/TypeDirective.h"

struct PairHash {
    std::size_t operator()(const std::pair<std::string, int>& p) const {
        auto h1 = std::hash<std::string>{}(p.first);
        auto h2 = std::hash<int>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

struct PairEqual {
    bool operator()(const std::pair<std::string, int>& lhs, 
                    const std::pair<std::string, int>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

class TypesManager{
    private:
        std::unordered_map<std::pair<std::string, int>, std::string, PairHash, PairEqual> predicateAndTermToType;
        TypesManager();
    
    public:
        static TypesManager& getInstance(){
            static TypesManager instance;
            return instance;
        }
        void addTermTypeForPredicate(std::string, int, std::string);
        bool isPredicateTermNumeric(std::string, int);
        bool isPredicateTermString(std::string, int);
        bool isTypeMismatch(std::string, int, std::string);
        std::string getTypeForPredicateTerm(std::string, int);
        void printPredicateTypes();

};