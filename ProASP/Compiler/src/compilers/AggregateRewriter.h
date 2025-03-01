#ifndef AGGREGATE_REWRITER_H
#define AGGREGATE_REWRITER_H
#include "../language/Program.h"

class AggregateRewriter{

    private:
    aspc::Program program;
    aspc::Program rewrittenProgram;
    int nextAggId;
    
    void rewriteRuleWithAggregate(const aspc::Rule&);
    public:
    static std::string AGG_SET_PREFIX;
    static std::string BODY_PREFIX;
    AggregateRewriter(const aspc::Program&);
    void rewriteAggregates();
    const aspc::Program& getRewrittenProgram();

};

#endif /*AGGREGATE_REWRITER_H*/