#include "TypesManager.h"


TypesManager::TypesManager(){}

void TypesManager::addTermTypeForPredicate(std::string predName, int termIdx, std::string type){
    assert(type == aspc::TypeDirective::NUMERIC_TYPE || type == aspc::TypeDirective::STRING_TYPE);
    predicateAndTermToType.emplace(std::make_pair(std::make_pair(predName, termIdx), type));
}

bool TypesManager::isPredicateTermNumeric(std::string predName, int termIdx){
    if(predicateAndTermToType.count(std::make_pair(predName, termIdx)) == 0)
        return false;
    return predicateAndTermToType[std::make_pair(predName, termIdx)] == aspc::TypeDirective::NUMERIC_TYPE;
}

bool TypesManager::isPredicateTermString(std::string predName, int termIdx){
    if(predicateAndTermToType.count(std::make_pair(predName, termIdx)) == 0)
        return false;
    return predicateAndTermToType[std::make_pair(predName, termIdx)] == aspc::TypeDirective::STRING_TYPE;
}

bool TypesManager::isTypeMismatch(std::string predName, int termIdx, std::string type){
    if(predicateAndTermToType.count(std::make_pair(predName, termIdx)) == 0)
        return false;
    return predicateAndTermToType[std::make_pair(predName, termIdx)] != type;
}

std::string TypesManager::getTypeForPredicateTerm(std::string predName, int termIdx){
    assert(predicateAndTermToType.count(std::make_pair(predName, termIdx)) != 0);
    return predicateAndTermToType[std::make_pair(predName, termIdx)];
}

void TypesManager::printPredicateTypes(){
    std::cout << "Types:\n";
    for(auto pair : predicateAndTermToType){
        std::cout <<"Predicate " << pair.first.first << " term " << pair.first.second << " maps to type " << pair.second << "\n";
    }
}