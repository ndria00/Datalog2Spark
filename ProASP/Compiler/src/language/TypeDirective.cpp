#include "TypeDirective.h"

std::string aspc::TypeDirective::INT_TYPE = "int";
std::string aspc::TypeDirective::STRING_TYPE = "string";

aspc::TypeDirective::TypeDirective(const std::string& predicateName, const std::vector<std::string>& terms) : predicateName(predicateName){
    for(unsigned i = 0; i < terms.size(); ++i){
        if(terms[i] == aspc::TypeDirective::INT_TYPE)
            this->termTypes.push_back(aspc::TypeDirective::INT_TYPE);
        else if(terms[i] == aspc::TypeDirective::STRING_TYPE)
            this->termTypes.push_back(aspc::TypeDirective::STRING_TYPE);
        else
            this->termTypes.push_back(aspc::TypeDirective::STRING_TYPE);
    }
}

aspc::TypeDirective::TypeDirective(const aspc::TypeDirective& other){
    for(unsigned i = 0; i < other.termTypes.size(); ++i){
        termTypes.push_back(other.getTermTypes().at(i));
    }
    predicateName = other.predicateName;
}

std::string aspc::TypeDirective::getPredicateName() const{
    return predicateName;
}

const std::vector<std::string>& aspc::TypeDirective::getTermTypes()const{
    return termTypes;
}

std::string aspc::TypeDirective::getTermTypeFromPos(unsigned pos)const{
    if(pos >= termTypes.size())
        return aspc::TypeDirective::STRING_TYPE;
    return termTypes[pos];
}

unsigned aspc::TypeDirective::getPredicateArity()const{
    return termTypes.size();
}

void aspc::TypeDirective::print() const{
    std::cout <<"#type " << predicateName <<"(";
    for(unsigned i = 0; i < termTypes.size(); ++i){
        if(i != termTypes.size()-1)
            std::cout << termTypes[i] << ", ";
        else
            std::cout << termTypes[i];
    }
    std::cout <<").\n";
}