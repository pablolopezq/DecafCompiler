#if !defined(EXPRPARSER_H))
#define EXPRPARSER_H

#include "ExprLexer.h"

class ExprParser{

public:
	ExprParser(ExprLexer& lexer) : lexer(lexer) {}
	void parse();

private:
    ExprLexer &lexer;
    Symbol token;

    void parse();
    void Program();
    void ClassName();
    void FieldDecl();
    void FieldDeclPrime();
    void MethodDecl();
    void Block();
    void VarDecl();
    void Type();
    void Statement();
    void Assign();
    void MethodCall();
    void Argument();
    void LValue();
    void Expr();
    void Expr1();
    void Expr2();
    void Expr3();
    void Expr4();
    void Expr5();
    void Expr6();
    void Expr7();
    void Expr8();
    void Expr9();
    void Expr10();
    void RelOp();
    void EqOp();
    void Constant();
    void BoolConstant();

    void throw_error(const char * error){
        throw error;
    }

    void expect(Symbol tk){
        if(token == tk)
            token = lexer.getNextToken();
        else
           throw std::string("Expected ") + lexer.tokenToString(tk) + std::string(" but found ") + lexer.getText();
    }
};


#endif //(EXPRPARSER_H)
