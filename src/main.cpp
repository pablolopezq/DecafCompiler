#include <iostream>
#include <fstream>

#include "ExprParser.h"
#include "ExprSeman.h"
#include "ExprInter.h"

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc != 2 ) {
        cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    ifstream in(argv[1], ios::in);

    if (!in.is_open()) {
        cerr << "Cannot open input file " << argv[1] << endl;
        return 1;
    }

    ExprLexer lexer(in);
    Symbol token;
    ExprParser parser(lexer);

    // while(true) {
    //     token = lexer.getNextToken();
    //     if (token == Symbol::Eof)
    //         break;
    //     cout << lexer.tokenToString(token) << " '" << lexer.getText() << "'\n";
    // }

    try{
    	parser.parse();
        // std::cout << "Parsed successfully" << std::endl;
    }
    catch(std::string& e){
    	cerr << e << endl;
    }

    std::vector<ASTNode*> statements = parser.get_statements();

    ExprSemantic semantic(statements);

    try{
    	semantic.check();
        // std::cout << "Check semantics successfully" << std::endl;
    }
    catch(std::string& e){
    	cerr << e << endl;
    }

    ExprSemantic::SymbTbl tbl = semantic.get_table();
    // cout << "Obtained table\n";
    ExprInter::SymbTbl inter_table;

    for(auto& e : tbl){
        inter_table.emplace(e.first, Value(e.second));
        cout << e.first << endl;
    }

    // cout << "Built interp table\n";

    ExprInter interp(inter_table, statements);

    // cout << "Created interp\n";
    // cout << "Executing code...\n";

    interp.execute();

    // cout << "Finished executing\n";

    in.close();

    return 0;
}