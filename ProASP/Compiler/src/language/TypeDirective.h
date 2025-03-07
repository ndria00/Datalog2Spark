#ifndef TYPE_DIRECTIVE_H
#define TYPE_DIRECTIVE_H

#include <string>
#include <vector>
#include <iostream>
namespace aspc{
    class TypeDirective{
        private:
            std::string predicateName;
            std::vector<std::string> termTypes;

        public:
        static std::string INT_TYPE;
        static std::string FLOAT_TYPE;
        static std::string NUMERIC_TYPE;
        static std::string STRING_TYPE;
        static std::string DEFAULT_TYPE;
        TypeDirective(const std::string&, const std::vector<std::string>&);
        TypeDirective(const aspc::TypeDirective&);
        std::string getPredicateName()const;
        const std::vector<std::string>& getTermTypes()const;
        std::string getTermTypeFromPos(unsigned)const;
        unsigned getPredicateArity()const;
        void print()const;
    };
}

#endif /*TYPE_DIRECTIVE_H*/