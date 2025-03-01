
// Generated from ASPCore2.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"




class  ASPCore2Parser : public antlr4::Parser {
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

  enum {
    RuleProgram = 0, RuleRule_ = 1, RuleSimple_rule = 2, RuleHead = 3, RuleBody = 4, 
    RuleWeight_at_levels = 5, RuleLevels_and_terms = 6, RuleDisjunction = 7, 
    RuleConjunction = 8, RuleChoice_atom = 9, RuleLower_guard = 10, RuleUpper_guard = 11, 
    RuleChoice_elements = 12, RuleChoice_element = 13, RuleChoice_element_atom = 14, 
    RuleChoice_elements_literals = 15, RuleNaf_literals = 16, RuleNaf_literal = 17, 
    RuleNaf_literal_aggregate = 18, RuleExistential_atom = 19, RuleClassic_literal = 20, 
    RuleAtom = 21, RuleExtAtom = 22, RuleExtSemicol = 23, RuleTerms = 24, 
    RuleBasic_terms = 25, RuleBuiltin_atom = 26, RuleCompareop = 27, RuleBinop = 28, 
    RuleArithop1 = 29, RuleArithop2 = 30, RuleTerm_ = 31, RuleTerm__ = 32, 
    RuleTerm = 33, RuleExpr = 34, RuleFactor = 35, RuleBasic_term = 36, 
    RuleGround_term = 37, RuleVariable_term = 38, RuleFunctional_term = 39, 
    RuleVars = 40, RuleIdentifier = 41, RuleDirective = 42, RuleDirective_types = 43, 
    RuleDirective_val = 44, RuleQuery = 45, RuleLower_guard_compare_aggregate = 46, 
    RuleUpper_guard_compare_aggregate = 47, RuleCompare_aggregate = 48, 
    RuleLower_guard_leftward_left_aggregate = 49, RuleLeftward_left_aggregate = 50, 
    RuleLeft_aggregate = 51, RuleLower_guard_rightward_left_aggregate = 52, 
    RuleRightward_left_aggregate = 53, RuleUpper_guard_leftward_right_aggregate = 54, 
    RuleUpper_guard_rightward_right_aggregate = 55, RuleRight_aggregate = 56, 
    RuleAggregate_atom = 57, RuleLeftwardop = 58, RuleRightwardop = 59, 
    RuleAggregate = 60, RuleAggregate_elements = 61, RuleAggregate_element = 62, 
    RuleAggregate_function = 63, RuleAnnotation_global = 64, RuleAnnotations_rule = 65, 
    RuleAnnotation_rule = 66, RuleAnnotation_rule_to_decompose = 67, RuleAnnotation_rule_to_not_decompose = 68, 
    RuleAnnotation_rule_ordering = 69, RuleAnnotation_global_ordering = 70, 
    RuleAnnotation_global_extatom_conversion = 71, RuleAnnotation_extpredicate = 72, 
    RuleExtatom_conv_types = 73, RuleExtatom_conv_type = 74, RuleRule_ordering_type = 75, 
    RuleGlobal_ordering_type = 76, RuleAnnotation_rule_atom_indexed = 77, 
    RuleAnnotation_global_atom_indexed = 78, RuleRule_indexing_arguments = 79, 
    RuleRule_naf_literal_annotation = 80, RuleGlobal_indexing_arguments = 81, 
    RuleGlobal_naf_literal_annotation = 82, RuleRule_atom_annotation_before = 83, 
    RuleGlobal_atom_annotation_before = 84, RuleRule_atom_annotation_after = 85, 
    RuleGlobal_atom_annotation_after = 86, RuleRule_atoms_annotation_before = 87, 
    RuleGlobal_atoms_annotation_before = 88, RuleRule_atoms_annotation_after = 89, 
    RuleGlobal_atoms_annotation_after = 90, RuleAnnotation_rule_partial_order_begin = 91, 
    RuleAnnotation_global_partial_order_begin = 92, RuleAnnotation_rule_partial_order = 93, 
    RuleAnnotation_global_partial_order = 94, RuleAnnotation_rule_projection = 95, 
    RuleAnnotation_rule_projection_value = 96, RuleAnnotation_rule_rewriting_arith = 97, 
    RuleAnnotation_rule_align_substitutions = 98, RuleAnnotation_rule_look_ahead = 99, 
    RuleAnnotation_global_wasp_propagator = 100, RuleAnnotation_global_wasp_propagator_begin = 101, 
    RuleAnnotation_global_wasp_heuristic = 102, RuleAnnotation_global_wasp_heuristic_begin = 103, 
    RuleHeuristic_python_file = 104, RuleAggregate_element_heuristic = 105, 
    RuleAggregate_elements_heuristic = 106
  };

  explicit ASPCore2Parser(antlr4::TokenStream *input);

  ASPCore2Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ASPCore2Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class Rule_Context;
  class Simple_ruleContext;
  class HeadContext;
  class BodyContext;
  class Weight_at_levelsContext;
  class Levels_and_termsContext;
  class DisjunctionContext;
  class ConjunctionContext;
  class Choice_atomContext;
  class Lower_guardContext;
  class Upper_guardContext;
  class Choice_elementsContext;
  class Choice_elementContext;
  class Choice_element_atomContext;
  class Choice_elements_literalsContext;
  class Naf_literalsContext;
  class Naf_literalContext;
  class Naf_literal_aggregateContext;
  class Existential_atomContext;
  class Classic_literalContext;
  class AtomContext;
  class ExtAtomContext;
  class ExtSemicolContext;
  class TermsContext;
  class Basic_termsContext;
  class Builtin_atomContext;
  class CompareopContext;
  class BinopContext;
  class Arithop1Context;
  class Arithop2Context;
  class Term_Context;
  class Term__Context;
  class TermContext;
  class ExprContext;
  class FactorContext;
  class Basic_termContext;
  class Ground_termContext;
  class Variable_termContext;
  class Functional_termContext;
  class VarsContext;
  class IdentifierContext;
  class DirectiveContext;
  class Directive_typesContext;
  class Directive_valContext;
  class QueryContext;
  class Lower_guard_compare_aggregateContext;
  class Upper_guard_compare_aggregateContext;
  class Compare_aggregateContext;
  class Lower_guard_leftward_left_aggregateContext;
  class Leftward_left_aggregateContext;
  class Left_aggregateContext;
  class Lower_guard_rightward_left_aggregateContext;
  class Rightward_left_aggregateContext;
  class Upper_guard_leftward_right_aggregateContext;
  class Upper_guard_rightward_right_aggregateContext;
  class Right_aggregateContext;
  class Aggregate_atomContext;
  class LeftwardopContext;
  class RightwardopContext;
  class AggregateContext;
  class Aggregate_elementsContext;
  class Aggregate_elementContext;
  class Aggregate_functionContext;
  class Annotation_globalContext;
  class Annotations_ruleContext;
  class Annotation_ruleContext;
  class Annotation_rule_to_decomposeContext;
  class Annotation_rule_to_not_decomposeContext;
  class Annotation_rule_orderingContext;
  class Annotation_global_orderingContext;
  class Annotation_global_extatom_conversionContext;
  class Annotation_extpredicateContext;
  class Extatom_conv_typesContext;
  class Extatom_conv_typeContext;
  class Rule_ordering_typeContext;
  class Global_ordering_typeContext;
  class Annotation_rule_atom_indexedContext;
  class Annotation_global_atom_indexedContext;
  class Rule_indexing_argumentsContext;
  class Rule_naf_literal_annotationContext;
  class Global_indexing_argumentsContext;
  class Global_naf_literal_annotationContext;
  class Rule_atom_annotation_beforeContext;
  class Global_atom_annotation_beforeContext;
  class Rule_atom_annotation_afterContext;
  class Global_atom_annotation_afterContext;
  class Rule_atoms_annotation_beforeContext;
  class Global_atoms_annotation_beforeContext;
  class Rule_atoms_annotation_afterContext;
  class Global_atoms_annotation_afterContext;
  class Annotation_rule_partial_order_beginContext;
  class Annotation_global_partial_order_beginContext;
  class Annotation_rule_partial_orderContext;
  class Annotation_global_partial_orderContext;
  class Annotation_rule_projectionContext;
  class Annotation_rule_projection_valueContext;
  class Annotation_rule_rewriting_arithContext;
  class Annotation_rule_align_substitutionsContext;
  class Annotation_rule_look_aheadContext;
  class Annotation_global_wasp_propagatorContext;
  class Annotation_global_wasp_propagator_beginContext;
  class Annotation_global_wasp_heuristicContext;
  class Annotation_global_wasp_heuristic_beginContext;
  class Heuristic_python_fileContext;
  class Aggregate_element_heuristicContext;
  class Aggregate_elements_heuristicContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Rule_Context *> rule_();
    Rule_Context* rule_(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  Rule_Context : public antlr4::ParserRuleContext {
  public:
    Rule_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Simple_ruleContext *simple_rule();
    Annotations_ruleContext *annotations_rule();
    Annotation_globalContext *annotation_global();
    DirectiveContext *directive();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_Context* rule_();

  class  Simple_ruleContext : public antlr4::ParserRuleContext {
  public:
    Simple_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    HeadContext *head();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *CONS();
    BodyContext *body();
    antlr4::tree::TerminalNode *WCONS();
    Weight_at_levelsContext *weight_at_levels();
    QueryContext *query();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Simple_ruleContext* simple_rule();

  class  HeadContext : public antlr4::ParserRuleContext {
  public:
    HeadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DisjunctionContext *disjunction();
    Choice_atomContext *choice_atom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HeadContext* head();

  class  BodyContext : public antlr4::ParserRuleContext {
  public:
    BodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConjunctionContext *conjunction();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BodyContext* body();

  class  Weight_at_levelsContext : public antlr4::ParserRuleContext {
  public:
    Weight_at_levelsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SQUARE_OPEN();
    TermContext *term();
    antlr4::tree::TerminalNode *SQUARE_CLOSED();
    Levels_and_termsContext *levels_and_terms();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Weight_at_levelsContext* weight_at_levels();

  class  Levels_and_termsContext : public antlr4::ParserRuleContext {
  public:
    Levels_and_termsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT();
    TermContext *term();
    antlr4::tree::TerminalNode *COMMA();
    TermsContext *terms();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Levels_and_termsContext* levels_and_terms();

  class  DisjunctionContext : public antlr4::ParserRuleContext {
  public:
    DisjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *HEAD_SEPARATOR();
    DisjunctionContext *disjunction();
    Existential_atomContext *existential_atom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DisjunctionContext* disjunction();

  class  ConjunctionContext : public antlr4::ParserRuleContext {
  public:
    ConjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Naf_literal_aggregateContext *naf_literal_aggregate();
    antlr4::tree::TerminalNode *COMMA();
    ConjunctionContext *conjunction();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConjunctionContext* conjunction();

  class  Choice_atomContext : public antlr4::ParserRuleContext {
  public:
    Choice_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Lower_guardContext *lower_guard();
    antlr4::tree::TerminalNode *CURLY_OPEN();
    Choice_elementsContext *choice_elements();
    antlr4::tree::TerminalNode *CURLY_CLOSE();
    Upper_guardContext *upper_guard();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Choice_atomContext* choice_atom();

  class  Lower_guardContext : public antlr4::ParserRuleContext {
  public:
    Lower_guardContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    BinopContext *binop();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Lower_guardContext* lower_guard();

  class  Upper_guardContext : public antlr4::ParserRuleContext {
  public:
    Upper_guardContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BinopContext *binop();
    TermContext *term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Upper_guardContext* upper_guard();

  class  Choice_elementsContext : public antlr4::ParserRuleContext {
  public:
    Choice_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Choice_elementContext *choice_element();
    antlr4::tree::TerminalNode *SEMICOLON();
    Choice_elementsContext *choice_elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Choice_elementsContext* choice_elements();

  class  Choice_elementContext : public antlr4::ParserRuleContext {
  public:
    Choice_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Choice_element_atomContext *choice_element_atom();
    antlr4::tree::TerminalNode *COLON();
    Choice_elements_literalsContext *choice_elements_literals();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Choice_elementContext* choice_element();

  class  Choice_element_atomContext : public antlr4::ParserRuleContext {
  public:
    Choice_element_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AtomContext *atom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Choice_element_atomContext* choice_element_atom();

  class  Choice_elements_literalsContext : public antlr4::ParserRuleContext {
  public:
    Choice_elements_literalsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Naf_literalContext *naf_literal();
    Naf_literalsContext *naf_literals();
    antlr4::tree::TerminalNode *COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Choice_elements_literalsContext* choice_elements_literals();

  class  Naf_literalsContext : public antlr4::ParserRuleContext {
  public:
    Naf_literalsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Naf_literalContext *naf_literal();
    antlr4::tree::TerminalNode *COMMA();
    Naf_literalsContext *naf_literals();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Naf_literalsContext* naf_literals();

  class  Naf_literalContext : public antlr4::ParserRuleContext {
  public:
    Naf_literalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *NAF();
    Builtin_atomContext *builtin_atom();
    ExtAtomContext *extAtom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Naf_literalContext* naf_literal();

  class  Naf_literal_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Naf_literal_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Naf_literalContext *naf_literal();
    Aggregate_atomContext *aggregate_atom();
    antlr4::tree::TerminalNode *NAF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Naf_literal_aggregateContext* naf_literal_aggregate();

  class  Existential_atomContext : public antlr4::ParserRuleContext {
  public:
    Existential_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXISTS();
    VarsContext *vars();
    AtomContext *atom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Existential_atomContext* existential_atom();

  class  Classic_literalContext : public antlr4::ParserRuleContext {
  public:
    Classic_literalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AtomContext *atom();
    antlr4::tree::TerminalNode *DASH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Classic_literalContext* classic_literal();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    TermsContext *terms();
    antlr4::tree::TerminalNode *PARAM_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtomContext* atom();

  class  ExtAtomContext : public antlr4::ParserRuleContext {
  public:
    ExtAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AMPERSAND();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    std::vector<TermsContext *> terms();
    TermsContext* terms(size_t i);
    ExtSemicolContext *extSemicol();
    antlr4::tree::TerminalNode *PARAM_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExtAtomContext* extAtom();

  class  ExtSemicolContext : public antlr4::ParserRuleContext {
  public:
    ExtSemicolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExtSemicolContext* extSemicol();

  class  TermsContext : public antlr4::ParserRuleContext {
  public:
    TermsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    antlr4::tree::TerminalNode *COMMA();
    TermsContext *terms();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TermsContext* terms();

  class  Basic_termsContext : public antlr4::ParserRuleContext {
  public:
    Basic_termsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_termContext *basic_term();
    antlr4::tree::TerminalNode *COMMA();
    Basic_termsContext *basic_terms();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Basic_termsContext* basic_terms();

  class  Builtin_atomContext : public antlr4::ParserRuleContext {
  public:
    Builtin_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    BinopContext *binop();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Builtin_atomContext* builtin_atom();

  class  CompareopContext : public antlr4::ParserRuleContext {
  public:
    CompareopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *UNEQUAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CompareopContext* compareop();

  class  BinopContext : public antlr4::ParserRuleContext {
  public:
    BinopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CompareopContext *compareop();
    LeftwardopContext *leftwardop();
    RightwardopContext *rightwardop();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BinopContext* binop();

  class  Arithop1Context : public antlr4::ParserRuleContext {
  public:
    Arithop1Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *DASH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Arithop1Context* arithop1();

  class  Arithop2Context : public antlr4::ParserRuleContext {
  public:
    Arithop2Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *BACK_SLASH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Arithop2Context* arithop2();

  class  Term_Context : public antlr4::ParserRuleContext {
  public:
    Term_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANON_VAR();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    TermsContext *terms();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    antlr4::tree::TerminalNode *DDOT();
    antlr4::tree::TerminalNode *DASH();
    TermContext *term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Term_Context* term_();

  class  Term__Context : public antlr4::ParserRuleContext {
  public:
    Term__Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    TermContext *term();
    antlr4::tree::TerminalNode *PARAM_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Term__Context* term__();

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Term_Context *term_();
    IdentifierContext *identifier();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TermContext* term();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FactorContext *factor();
    Arithop1Context *arithop1();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();

  class  FactorContext : public antlr4::ParserRuleContext {
  public:
    FactorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Term__Context *term__();
    Arithop2Context *arithop2();
    FactorContext *factor();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FactorContext* factor();

  class  Basic_termContext : public antlr4::ParserRuleContext {
  public:
    Basic_termContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Ground_termContext *ground_term();
    Variable_termContext *variable_term();
    Functional_termContext *functional_term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Basic_termContext* basic_term();

  class  Ground_termContext : public antlr4::ParserRuleContext {
  public:
    Ground_termContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOLIC_CONSTANT();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *DASH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Ground_termContext* ground_term();

  class  Variable_termContext : public antlr4::ParserRuleContext {
  public:
    Variable_termContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *ANON_VAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Variable_termContext* variable_term();

  class  Functional_termContext : public antlr4::ParserRuleContext {
  public:
    Functional_termContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    TermsContext *terms();
    antlr4::tree::TerminalNode *PARAM_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Functional_termContext* functional_term();

  class  VarsContext : public antlr4::ParserRuleContext {
  public:
    VarsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *COMMA();
    VarsContext *vars();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarsContext* vars();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYMBOLIC_CONSTANT();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentifierContext* identifier();

  class  DirectiveContext : public antlr4::ParserRuleContext {
  public:
    DirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DIRECTIVE_NAME();
    antlr4::tree::TerminalNode *SYMBOLIC_CONSTANT();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    Directive_typesContext *directive_types();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DirectiveContext* directive();

  class  Directive_typesContext : public antlr4::ParserRuleContext {
  public:
    Directive_typesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Directive_valContext *directive_val();
    antlr4::tree::TerminalNode *COMMA();
    Directive_typesContext *directive_types();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Directive_typesContext* directive_types();

  class  Directive_valContext : public antlr4::ParserRuleContext {
  public:
    Directive_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DIRECTIVE_VALUE_INT();
    antlr4::tree::TerminalNode *DIRECTIVE_VALUE_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Directive_valContext* directive_val();

  class  QueryContext : public antlr4::ParserRuleContext {
  public:
    QueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AtomContext *atom();
    antlr4::tree::TerminalNode *QUERY_MARK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QueryContext* query();

  class  Lower_guard_compare_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Lower_guard_compare_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    CompareopContext *compareop();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Lower_guard_compare_aggregateContext* lower_guard_compare_aggregate();

  class  Upper_guard_compare_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Upper_guard_compare_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CompareopContext *compareop();
    TermContext *term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Upper_guard_compare_aggregateContext* upper_guard_compare_aggregate();

  class  Compare_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Compare_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Lower_guard_compare_aggregateContext *lower_guard_compare_aggregate();
    AggregateContext *aggregate();
    Upper_guard_compare_aggregateContext *upper_guard_compare_aggregate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Compare_aggregateContext* compare_aggregate();

  class  Lower_guard_leftward_left_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Lower_guard_leftward_left_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    LeftwardopContext *leftwardop();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Lower_guard_leftward_left_aggregateContext* lower_guard_leftward_left_aggregate();

  class  Leftward_left_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Leftward_left_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Lower_guard_leftward_left_aggregateContext *lower_guard_leftward_left_aggregate();
    AggregateContext *aggregate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Leftward_left_aggregateContext* leftward_left_aggregate();

  class  Left_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Left_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Leftward_left_aggregateContext *leftward_left_aggregate();
    Rightward_left_aggregateContext *rightward_left_aggregate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Left_aggregateContext* left_aggregate();

  class  Lower_guard_rightward_left_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Lower_guard_rightward_left_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    RightwardopContext *rightwardop();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Lower_guard_rightward_left_aggregateContext* lower_guard_rightward_left_aggregate();

  class  Rightward_left_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Rightward_left_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Lower_guard_rightward_left_aggregateContext *lower_guard_rightward_left_aggregate();
    AggregateContext *aggregate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rightward_left_aggregateContext* rightward_left_aggregate();

  class  Upper_guard_leftward_right_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Upper_guard_leftward_right_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LeftwardopContext *leftwardop();
    TermContext *term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Upper_guard_leftward_right_aggregateContext* upper_guard_leftward_right_aggregate();

  class  Upper_guard_rightward_right_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Upper_guard_rightward_right_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RightwardopContext *rightwardop();
    TermContext *term();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Upper_guard_rightward_right_aggregateContext* upper_guard_rightward_right_aggregate();

  class  Right_aggregateContext : public antlr4::ParserRuleContext {
  public:
    Right_aggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AggregateContext *aggregate();
    Upper_guard_leftward_right_aggregateContext *upper_guard_leftward_right_aggregate();
    Upper_guard_rightward_right_aggregateContext *upper_guard_rightward_right_aggregate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Right_aggregateContext* right_aggregate();

  class  Aggregate_atomContext : public antlr4::ParserRuleContext {
  public:
    Aggregate_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Left_aggregateContext *left_aggregate();
    Right_aggregateContext *right_aggregate();
    Compare_aggregateContext *compare_aggregate();
    Leftward_left_aggregateContext *leftward_left_aggregate();
    Upper_guard_leftward_right_aggregateContext *upper_guard_leftward_right_aggregate();
    Rightward_left_aggregateContext *rightward_left_aggregate();
    Upper_guard_rightward_right_aggregateContext *upper_guard_rightward_right_aggregate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Aggregate_atomContext* aggregate_atom();

  class  LeftwardopContext : public antlr4::ParserRuleContext {
  public:
    LeftwardopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *LESS_OR_EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LeftwardopContext* leftwardop();

  class  RightwardopContext : public antlr4::ParserRuleContext {
  public:
    RightwardopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *GREATER_OR_EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RightwardopContext* rightwardop();

  class  AggregateContext : public antlr4::ParserRuleContext {
  public:
    AggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Aggregate_functionContext *aggregate_function();
    antlr4::tree::TerminalNode *CURLY_OPEN();
    Aggregate_elementsContext *aggregate_elements();
    antlr4::tree::TerminalNode *CURLY_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AggregateContext* aggregate();

  class  Aggregate_elementsContext : public antlr4::ParserRuleContext {
  public:
    Aggregate_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Aggregate_elementContext *aggregate_element();
    antlr4::tree::TerminalNode *SEMICOLON();
    Aggregate_elementsContext *aggregate_elements();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Aggregate_elementsContext* aggregate_elements();

  class  Aggregate_elementContext : public antlr4::ParserRuleContext {
  public:
    Aggregate_elementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_termsContext *basic_terms();
    antlr4::tree::TerminalNode *COLON();
    Naf_literalsContext *naf_literals();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Aggregate_elementContext* aggregate_element();

  class  Aggregate_functionContext : public antlr4::ParserRuleContext {
  public:
    Aggregate_functionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AGGR_COUNT();
    antlr4::tree::TerminalNode *AGGR_MAX();
    antlr4::tree::TerminalNode *AGGR_MIN();
    antlr4::tree::TerminalNode *AGGR_SUM();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Aggregate_functionContext* aggregate_function();

  class  Annotation_globalContext : public antlr4::ParserRuleContext {
  public:
    Annotation_globalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotation_global_orderingContext *annotation_global_ordering();
    Annotation_global_atom_indexedContext *annotation_global_atom_indexed();
    Annotation_global_partial_orderContext *annotation_global_partial_order();
    Annotation_global_extatom_conversionContext *annotation_global_extatom_conversion();
    Annotation_global_wasp_heuristicContext *annotation_global_wasp_heuristic();
    Annotation_global_wasp_propagatorContext *annotation_global_wasp_propagator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_globalContext* annotation_global();

  class  Annotations_ruleContext : public antlr4::ParserRuleContext {
  public:
    Annotations_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotation_ruleContext *annotation_rule();
    Annotations_ruleContext *annotations_rule();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotations_ruleContext* annotations_rule();

  class  Annotation_ruleContext : public antlr4::ParserRuleContext {
  public:
    Annotation_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotation_rule_orderingContext *annotation_rule_ordering();
    Annotation_rule_atom_indexedContext *annotation_rule_atom_indexed();
    Annotation_rule_partial_orderContext *annotation_rule_partial_order();
    Annotation_rule_projectionContext *annotation_rule_projection();
    Annotation_rule_rewriting_arithContext *annotation_rule_rewriting_arith();
    Annotation_rule_align_substitutionsContext *annotation_rule_align_substitutions();
    Annotation_rule_look_aheadContext *annotation_rule_look_ahead();
    Annotation_rule_to_decomposeContext *annotation_rule_to_decompose();
    Annotation_rule_to_not_decomposeContext *annotation_rule_to_not_decompose();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_ruleContext* annotation_rule();

  class  Annotation_rule_to_decomposeContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_to_decomposeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_TO_DECOMPOSE();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_to_decomposeContext* annotation_rule_to_decompose();

  class  Annotation_rule_to_not_decomposeContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_to_not_decomposeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_TO_NOT_DECOMPOSE();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_to_not_decomposeContext* annotation_rule_to_not_decompose();

  class  Annotation_rule_orderingContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_orderingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_ORDERING();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_ORDERING_VALUE();
    antlr4::tree::TerminalNode *EQUAL();
    Rule_ordering_typeContext *rule_ordering_type();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_orderingContext* annotation_rule_ordering();

  class  Annotation_global_orderingContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_orderingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_ORDERING();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_ORDERING_VALUE();
    antlr4::tree::TerminalNode *EQUAL();
    Global_ordering_typeContext *global_ordering_type();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_orderingContext* annotation_global_ordering();

  class  Annotation_global_extatom_conversionContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_extatom_conversionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_EXTATOM_CONVERSION();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_PREDICATE();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    Annotation_extpredicateContext *annotation_extpredicate();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE();
    Extatom_conv_typesContext *extatom_conv_types();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_extatom_conversionContext* annotation_global_extatom_conversion();

  class  Annotation_extpredicateContext : public antlr4::ParserRuleContext {
  public:
    Annotation_extpredicateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AMPERSAND();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_extpredicateContext* annotation_extpredicate();

  class  Extatom_conv_typesContext : public antlr4::ParserRuleContext {
  public:
    Extatom_conv_typesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Extatom_conv_typeContext *extatom_conv_type();
    antlr4::tree::TerminalNode *COMMA();
    Extatom_conv_typesContext *extatom_conv_types();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Extatom_conv_typesContext* extatom_conv_types();

  class  Extatom_conv_typeContext : public antlr4::ParserRuleContext {
  public:
    Extatom_conv_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE_QCONST();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE_CONST();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE_U_INT();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE_UT_INT();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE_UR_INT();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE_T_INT();
    antlr4::tree::TerminalNode *ANNOTATION_EXTATOM_TYPE_R_INT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Extatom_conv_typeContext* extatom_conv_type();

  class  Rule_ordering_typeContext : public antlr4::ParserRuleContext {
  public:
    Rule_ordering_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_ordering_typeContext* rule_ordering_type();

  class  Global_ordering_typeContext : public antlr4::ParserRuleContext {
  public:
    Global_ordering_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_ordering_typeContext* global_ordering_type();

  class  Annotation_rule_atom_indexedContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_atom_indexedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_ATOM_INDEXED();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_ATOM_INDEXED_ATOM();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    Rule_naf_literal_annotationContext *rule_naf_literal_annotation();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *ANNOTATION_ATOM_INDEXED_ARGUMENTS();
    antlr4::tree::TerminalNode *CURLY_OPEN();
    Rule_indexing_argumentsContext *rule_indexing_arguments();
    antlr4::tree::TerminalNode *CURLY_CLOSE();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_atom_indexedContext* annotation_rule_atom_indexed();

  class  Annotation_global_atom_indexedContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_atom_indexedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_ATOM_INDEXED();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_ATOM_INDEXED_ATOM();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    Global_naf_literal_annotationContext *global_naf_literal_annotation();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *ANNOTATION_ATOM_INDEXED_ARGUMENTS();
    antlr4::tree::TerminalNode *CURLY_OPEN();
    Global_indexing_argumentsContext *global_indexing_arguments();
    antlr4::tree::TerminalNode *CURLY_CLOSE();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_atom_indexedContext* annotation_global_atom_indexed();

  class  Rule_indexing_argumentsContext : public antlr4::ParserRuleContext {
  public:
    Rule_indexing_argumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *COMMA();
    Rule_indexing_argumentsContext *rule_indexing_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_indexing_argumentsContext* rule_indexing_arguments();

  class  Rule_naf_literal_annotationContext : public antlr4::ParserRuleContext {
  public:
    Rule_naf_literal_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *NAF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_naf_literal_annotationContext* rule_naf_literal_annotation();

  class  Global_indexing_argumentsContext : public antlr4::ParserRuleContext {
  public:
    Global_indexing_argumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *COMMA();
    Global_indexing_argumentsContext *global_indexing_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_indexing_argumentsContext* global_indexing_arguments();

  class  Global_naf_literal_annotationContext : public antlr4::ParserRuleContext {
  public:
    Global_naf_literal_annotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *NAF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_naf_literal_annotationContext* global_naf_literal_annotation();

  class  Rule_atom_annotation_beforeContext : public antlr4::ParserRuleContext {
  public:
    Rule_atom_annotation_beforeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *NAF();
    Builtin_atomContext *builtin_atom();
    Aggregate_atomContext *aggregate_atom();
    ExtAtomContext *extAtom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_atom_annotation_beforeContext* rule_atom_annotation_before();

  class  Global_atom_annotation_beforeContext : public antlr4::ParserRuleContext {
  public:
    Global_atom_annotation_beforeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *NAF();
    Builtin_atomContext *builtin_atom();
    Aggregate_atomContext *aggregate_atom();
    ExtAtomContext *extAtom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_atom_annotation_beforeContext* global_atom_annotation_before();

  class  Rule_atom_annotation_afterContext : public antlr4::ParserRuleContext {
  public:
    Rule_atom_annotation_afterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *NAF();
    Builtin_atomContext *builtin_atom();
    Aggregate_atomContext *aggregate_atom();
    ExtAtomContext *extAtom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_atom_annotation_afterContext* rule_atom_annotation_after();

  class  Global_atom_annotation_afterContext : public antlr4::ParserRuleContext {
  public:
    Global_atom_annotation_afterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Classic_literalContext *classic_literal();
    antlr4::tree::TerminalNode *NAF();
    Builtin_atomContext *builtin_atom();
    Aggregate_atomContext *aggregate_atom();
    ExtAtomContext *extAtom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_atom_annotation_afterContext* global_atom_annotation_after();

  class  Rule_atoms_annotation_beforeContext : public antlr4::ParserRuleContext {
  public:
    Rule_atoms_annotation_beforeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Rule_atom_annotation_beforeContext *rule_atom_annotation_before();
    antlr4::tree::TerminalNode *COMMA();
    Rule_atoms_annotation_beforeContext *rule_atoms_annotation_before();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_atoms_annotation_beforeContext* rule_atoms_annotation_before();

  class  Global_atoms_annotation_beforeContext : public antlr4::ParserRuleContext {
  public:
    Global_atoms_annotation_beforeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Global_atom_annotation_beforeContext *global_atom_annotation_before();
    antlr4::tree::TerminalNode *COMMA();
    Global_atoms_annotation_beforeContext *global_atoms_annotation_before();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_atoms_annotation_beforeContext* global_atoms_annotation_before();

  class  Rule_atoms_annotation_afterContext : public antlr4::ParserRuleContext {
  public:
    Rule_atoms_annotation_afterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Rule_atom_annotation_afterContext *rule_atom_annotation_after();
    antlr4::tree::TerminalNode *COMMA();
    Rule_atoms_annotation_afterContext *rule_atoms_annotation_after();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_atoms_annotation_afterContext* rule_atoms_annotation_after();

  class  Global_atoms_annotation_afterContext : public antlr4::ParserRuleContext {
  public:
    Global_atoms_annotation_afterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Global_atom_annotation_afterContext *global_atom_annotation_after();
    antlr4::tree::TerminalNode *COMMA();
    std::vector<Global_atoms_annotation_afterContext *> global_atoms_annotation_after();
    Global_atoms_annotation_afterContext* global_atoms_annotation_after(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Global_atoms_annotation_afterContext* global_atoms_annotation_after();

  class  Annotation_rule_partial_order_beginContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_partial_order_beginContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_PARTIAL_ORDER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_partial_order_beginContext* annotation_rule_partial_order_begin();

  class  Annotation_global_partial_order_beginContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_partial_order_beginContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_PARTIAL_ORDER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_partial_order_beginContext* annotation_global_partial_order_begin();

  class  Annotation_rule_partial_orderContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_partial_orderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotation_rule_partial_order_beginContext *annotation_rule_partial_order_begin();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_PARTIAL_ORDER_BEFORE();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CURLY_OPEN();
    antlr4::tree::TerminalNode* CURLY_OPEN(size_t i);
    Rule_atoms_annotation_beforeContext *rule_atoms_annotation_before();
    std::vector<antlr4::tree::TerminalNode *> CURLY_CLOSE();
    antlr4::tree::TerminalNode* CURLY_CLOSE(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *ANNOTATION_PARTIAL_ORDER_AFTER();
    Rule_atoms_annotation_afterContext *rule_atoms_annotation_after();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_partial_orderContext* annotation_rule_partial_order();

  class  Annotation_global_partial_orderContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_partial_orderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotation_global_partial_order_beginContext *annotation_global_partial_order_begin();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_PARTIAL_ORDER_BEFORE();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CURLY_OPEN();
    antlr4::tree::TerminalNode* CURLY_OPEN(size_t i);
    Global_atoms_annotation_beforeContext *global_atoms_annotation_before();
    std::vector<antlr4::tree::TerminalNode *> CURLY_CLOSE();
    antlr4::tree::TerminalNode* CURLY_CLOSE(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *ANNOTATION_PARTIAL_ORDER_AFTER();
    Global_atoms_annotation_afterContext *global_atoms_annotation_after();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_partial_orderContext* annotation_global_partial_order();

  class  Annotation_rule_projectionContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_projectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_PROJECTION();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_ORDERING_VALUE();
    antlr4::tree::TerminalNode *EQUAL();
    Annotation_rule_projection_valueContext *annotation_rule_projection_value();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_projectionContext* annotation_rule_projection();

  class  Annotation_rule_projection_valueContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_projection_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_projection_valueContext* annotation_rule_projection_value();

  class  Annotation_rule_rewriting_arithContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_rewriting_arithContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_REWRITING_ARITH();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_rewriting_arithContext* annotation_rule_rewriting_arith();

  class  Annotation_rule_align_substitutionsContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_align_substitutionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_ALIGN_SUBSTITUTIONS();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_align_substitutionsContext* annotation_rule_align_substitutions();

  class  Annotation_rule_look_aheadContext : public antlr4::ParserRuleContext {
  public:
    Annotation_rule_look_aheadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_RULE_LOOK_AHEAD();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_rule_look_aheadContext* annotation_rule_look_ahead();

  class  Annotation_global_wasp_propagatorContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_wasp_propagatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotation_global_wasp_propagator_beginContext *annotation_global_wasp_propagator_begin();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_WASP_HEURISTIC_FILE();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    Heuristic_python_fileContext *heuristic_python_file();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_WASP_HEURISTIC_ELEMENTS();
    antlr4::tree::TerminalNode *CURLY_OPEN();
    Aggregate_elements_heuristicContext *aggregate_elements_heuristic();
    antlr4::tree::TerminalNode *CURLY_CLOSE();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_wasp_propagatorContext* annotation_global_wasp_propagator();

  class  Annotation_global_wasp_propagator_beginContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_wasp_propagator_beginContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_WASP_PROPAGATOR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_wasp_propagator_beginContext* annotation_global_wasp_propagator_begin();

  class  Annotation_global_wasp_heuristicContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_wasp_heuristicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Annotation_global_wasp_heuristic_beginContext *annotation_global_wasp_heuristic_begin();
    antlr4::tree::TerminalNode *PARAM_OPEN();
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_WASP_HEURISTIC_FILE();
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    Heuristic_python_fileContext *heuristic_python_file();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_WASP_HEURISTIC_ELEMENTS();
    antlr4::tree::TerminalNode *CURLY_OPEN();
    Aggregate_elements_heuristicContext *aggregate_elements_heuristic();
    antlr4::tree::TerminalNode *CURLY_CLOSE();
    antlr4::tree::TerminalNode *PARAM_CLOSE();
    antlr4::tree::TerminalNode *DOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_wasp_heuristicContext* annotation_global_wasp_heuristic();

  class  Annotation_global_wasp_heuristic_beginContext : public antlr4::ParserRuleContext {
  public:
    Annotation_global_wasp_heuristic_beginContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION_GLOBAL_WASP_HEURISTIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Annotation_global_wasp_heuristic_beginContext* annotation_global_wasp_heuristic_begin();

  class  Heuristic_python_fileContext : public antlr4::ParserRuleContext {
  public:
    Heuristic_python_fileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Heuristic_python_fileContext* heuristic_python_file();

  class  Aggregate_element_heuristicContext : public antlr4::ParserRuleContext {
  public:
    Aggregate_element_heuristicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Aggregate_elementContext *aggregate_element();
    Classic_literalContext *classic_literal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Aggregate_element_heuristicContext* aggregate_element_heuristic();

  class  Aggregate_elements_heuristicContext : public antlr4::ParserRuleContext {
  public:
    Aggregate_elements_heuristicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Aggregate_element_heuristicContext *aggregate_element_heuristic();
    antlr4::tree::TerminalNode *SEMICOLON();
    Aggregate_elements_heuristicContext *aggregate_elements_heuristic();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Aggregate_elements_heuristicContext* aggregate_elements_heuristic();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

