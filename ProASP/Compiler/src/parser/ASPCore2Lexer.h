
// Generated from ASPCore2.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"




class  ASPCore2Lexer : public antlr4::Lexer {
public:
  enum {
    NAF = 1, DIRECTIVE_NAME = 2, DIRECTIVE_VALUE_INT = 3, DIRECTIVE_VALUE_STRING = 4, 
    SYMBOLIC_CONSTANT = 5, VARIABLE = 6, STRING = 7, NUMBER = 8, WS = 9, 
    DOT = 10, DDOT = 11, COMMA = 12, HEAD_SEPARATOR = 13, SEMICOLON = 14, 
    COLON = 15, AT = 16, CONS = 17, WCONS = 18, PLUS = 19, DASH = 20, TIMES = 21, 
    SLASH = 22, BACK_SLASH = 23, PARAM_OPEN = 24, PARAM_CLOSE = 25, SQUARE_OPEN = 26, 
    SQUARE_CLOSED = 27, CURLY_OPEN = 28, CURLY_CLOSE = 29, QUERY_MARK = 30, 
    ANON_VAR = 31, EQUAL = 32, UNEQUAL = 33, LESS = 34, GREATER = 35, LESS_OR_EQ = 36, 
    GREATER_OR_EQ = 37, AMPERSAND = 38, EXISTS = 39, AGGR_COUNT = 40, AGGR_MAX = 41, 
    AGGR_MIN = 42, AGGR_SUM = 43, ANNOTATION_GLOBAL_WASP_PROPAGATOR = 44, 
    ANNOTATION_RULE_ALIGN_SUBSTITUTIONS = 45, ANNOTATION_RULE_LOOK_AHEAD = 46, 
    ANNOTATION_RULE_PROJECTION = 47, ANNOTATION_RULE_REWRITING_ARITH = 48, 
    ANNOTATION_RULE_ORDERING = 49, ANNOTATION_ORDERING_VALUE = 50, ANNOTATION_RULE_ATOM_INDEXED = 51, 
    ANNOTATION_ATOM_INDEXED_ATOM = 52, ANNOTATION_ATOM_INDEXED_ARGUMENTS = 53, 
    ANNOTATION_RULE_PARTIAL_ORDER = 54, ANNOTATION_PARTIAL_ORDER_BEFORE = 55, 
    ANNOTATION_PARTIAL_ORDER_AFTER = 56, ANNOTATION_EXTATOM_PREDICATE = 57, 
    ANNOTATION_EXTATOM_TYPE = 58, ANNOTATION_EXTATOM_TYPE_QCONST = 59, ANNOTATION_EXTATOM_TYPE_CONST = 60, 
    ANNOTATION_EXTATOM_TYPE_U_INT = 61, ANNOTATION_EXTATOM_TYPE_UR_INT = 62, 
    ANNOTATION_EXTATOM_TYPE_UT_INT = 63, ANNOTATION_EXTATOM_TYPE_R_INT = 64, 
    ANNOTATION_EXTATOM_TYPE_T_INT = 65, ANNOTATION_GLOBAL_ORDERING = 66, 
    ANNOTATION_GLOBAL_ATOM_INDEXED = 67, ANNOTATION_GLOBAL_PARTIAL_ORDER = 68, 
    ANNOTATION_GLOBAL_EXTATOM_CONVERSION = 69, ANNOTATION_RULE_TO_DECOMPOSE = 70, 
    ANNOTATION_RULE_TO_NOT_DECOMPOSE = 71, ANNOTATION_GLOBAL_WASP_HEURISTIC = 72, 
    ANNOTATION_GLOBAL_WASP_HEURISTIC_FILE = 73, ANNOTATION_GLOBAL_WASP_HEURISTIC_ELEMENTS = 74, 
    EMPTY_COMMENT = 75, COMMENT = 76
  };

  explicit ASPCore2Lexer(antlr4::CharStream *input);

  ~ASPCore2Lexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

