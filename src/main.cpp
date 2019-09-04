#include <iostream>
#include <fstream>

#include "ExprLexer.h"

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

    while(true) {
        token = lexer.getNextToken();
        if (token == Symbol::Eof)
            break;
        cout << lexer.tokenToString(token) << " '" << lexer.getText() << "'\n";
    }

    in.close();

    return 0;
}