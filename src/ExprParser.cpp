#include "ExprParser.h"

void ExprParser::parse(){
    token = lexer.getNextToken();
    Program();
}

void ExprParser::Program(){
    expect(Symbol::KW_CLASS);
    ClassName();
    expect(Symbol::OPEN_BRACKET);
    FieldDecl();
    MethodDecl();
    expect(Symbol::CLOSE_BRACKET);
}

void ExprParser::ClassName(){
    expect(Symbol::ID);
}

void ExprParser::FieldDecl(){
    Type();
    FieldDeclPrime();
}

void ExprParser::Type(){
    if(token == Symbol::KW_BOOL || token == Symbol::KW_INT){
        token = lexer.getNextToken();
    }
    else{
        std::string error = std::string("Expected type keyword, but found") + lexer.getText();
        throw_error(error.c_str());
    }
}

void ExprParser::MethodDecl(){
    if(token == Symbol::KW_BOOL || token == Symbol::KW_INT || token == Symbol::KW_VOID){
        token = lexer.getNextToken();
    }
    else{
        std::string error = std::string("Expected type keyword, but found") + lexer.getText();
        throw_error(error.c_str());
    }
    expect(Symbol::ID);
    expect(Symbol::OPEN_PAREN);
    // get params
    if(token == Symbol::CLOSE_PAREN){
        token = lexer.getNextToken();
    }
    else{
        while(token != Symbol::CLOSE_PAREN){
            Type();
            expect(Symbol::ID);
            while(token == Symbol::COMMA){
                token = lexer.getNextToken();
                Type();
                expect(Symbol::ID);
            }
        }
        token = lexer.getNextToken();
    }
    Block();
}

void ExprParser::Block(){
    expect(Symbol::OPEN_BRACKET);
    VarDecl();
    Statement();
    expect(Symbol::CLOSE_BRACKET);
}

void ExprParser::VarDecl(){
    Type();
    expect(Symbol::ID);
    while(token == Symbol::COMMA){
        token = lexer.getNextToken();
        expect(Symbol::ID);
    }
    expect(Symbol::SEMICOLON);
}

void ExprParser::Statement(){
    if(token == Symbol::KW_BREAK){
        token = lexer.getNextToken();
        expect(Symbol::SEMICOLON);
    }
}