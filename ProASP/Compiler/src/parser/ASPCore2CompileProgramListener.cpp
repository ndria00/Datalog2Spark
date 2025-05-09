#include "ASPCore2CompileProgramListener.h"

std::set<int> ASPCore2CompileProgramListener::watchedTerminalTypes = std::set<int>({
    ASPCore2Parser::SYMBOLIC_CONSTANT,
    ASPCore2Parser::VARIABLE,
    ASPCore2Parser::STRING,
    ASPCore2Parser::NUMBER,
    ASPCore2Parser::EQUAL,
    ASPCore2Parser::UNEQUAL,
    ASPCore2Parser::LESS,
    ASPCore2Parser::LESS_OR_EQ,
    ASPCore2Parser::GREATER,
    ASPCore2Parser::GREATER_OR_EQ,
    ASPCore2Parser::PLUS,
    ASPCore2Parser::DASH,
    ASPCore2Parser::AGGR_COUNT, 
    ASPCore2Parser::AGGR_MAX,
    ASPCore2Parser::AGGR_MIN,
    ASPCore2Parser::AGGR_SUM,
    ASPCore2Parser::AGGR_AVG,
    ASPCore2Parser::AGGR_STD_DEV,
    ASPCore2Parser::AGGR_VAR,
    ASPCore2Parser::AGGR_MEDIAN,
    ASPCore2Parser::TIMES,
    ASPCore2Parser::DIRECTIVE_VALUE_INT,
    ASPCore2Parser::DIRECTIVE_VALUE_STRING
    
});

std::set<int> ASPCore2CompileProgramListener::forbiddenTerminalTypes = std::set<int>({
    ASPCore2Parser::SLASH,
    ASPCore2Parser::BACK_SLASH,
    ASPCore2Parser::ANON_VAR
});
