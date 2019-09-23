#if !defined(EXPRPARSER_H)
#define EXPRPARSER_H

#include "ExprLexer.h"
#include "ExprAst.h"

class ExprParser{

public:
	ExprParser(ExprLexer& lexer) : lexer(lexer) {}

	void parse();

    std::vector<ASTNode*> get_statements(){
        return statements;
    }

private:

    ExprLexer &lexer;
    Symbol token;

    std::vector<ASTNode*> statements;

    // void Program();
    // void ClassName();
    // void FieldDecl();
    // void MethodDecl();
    // void FieldDeclPrime();
    // void Block();
    // void VarDecl();
    // void Type();
    // void Statement();
    // void ID_Next();
    // void Assign();
    // void MethodCall();
    // void Argument();
    // void LValue();
    ASTNode * Expr();
    ASTNode * Expr1();
    ASTNode * Expr2();
    ASTNode * Expr3();
    ASTNode * Expr4();
    ASTNode * Expr5();
    ASTNode * Expr6();
    ASTNode * Expr7();
    ASTNode * Expr8();
    ASTNode * Expr9();
    ASTNode * Expr10();
    ASTNode * RelOp();
    ASTNode * EqOp();
    ASTNode * Constant();
    ASTNode * BoolConstant();
    ASTNode * MethodCall();
    ASTNode * HandleID();
    ASTNode * Argument();
    ASTNode * Program();
    ASTNode * Assign();
    ASTNode * Args();
    std::vector<ASTNode*> Block();
    std::vector<ASTNode*> FieldDecl();
    std::vector<ASTNode*> MethodDecl();

    void advanceToken(){
        token = lexer.getNextToken();
    }

    void throw_error(std::string error){
        throw error;
    }

    void expect(Symbol tk){
        if(token == tk)
            token = lexer.getNextToken();
        else
           throw std::string("Expected ") + lexer.tokenToString(tk) + std::string(" but found ") + lexer.getText() + " in line " + std::to_string(lexer.getLine());
    }
};


#endif //(EXPRPARSER_H)
