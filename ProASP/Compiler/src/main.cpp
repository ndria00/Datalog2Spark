#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "language/Program.h"
#include "antlr4-runtime.h"
#include "parser/ASPCore2Lexer.h"
#include "parser/ASPCore2Parser.h"
#include "parser/ASPCore2CompileProgramListener.h"
#include "compilers/SparkJobsCompiler.h"
#include "compilers/AggregateRewriter.h"

int main(int argc, char *argv[])
{
	ASPCore2CompileProgramListener listener;
	std::string filename(argv[1]);
	antlr4::ANTLRFileStream input;
	input.loadFromFile(filename);
	ASPCore2Lexer lexer (&input);
	antlr4::CommonTokenStream tokens(&lexer);
	ASPCore2Parser parser (&tokens);
	parser.addParseListener(&listener);
	parser.program();
	std::cout <<"------------------------------------------------------------\n";
	std::cout <<"Input program\n";
	listener.getProgram().print();
	std::cout <<"------------------------------------------------------------\n";
	const aspc::Program& program = listener.getProgram();
	AggregateRewriter rewriter(program);
	SparkJobsCompiler compiler(rewriter.getRewrittenProgram());
	std::cout <<"------------------------------------------------------------\n";
	std::cout <<"Rewritten program\n";
	rewriter.getRewrittenProgram().print();
	std::cout <<"------------------------------------------------------------\n";
	compiler.compile();
}

