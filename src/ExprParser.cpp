#include "ExprParser.h"
#include "Symbols.h"

#include <cstring>

void ExprParser::parse(){
    token = lexer.getNextToken();
    Program();
    if(token != Symbol::Eof){
        throw std::string("Parser stopped on token: ") + lexer.getText();
    }
}

ASTNode * ExprParser::Expr(){

    ASTNode * left = Expr1();
    ASTNode * right = nullptr;

    while(token == Symbol::OR){

        right = Expr1();
        left = new OrExpr(left, right);
    }

    return left;
}

ASTNode * ExprParser::Expr1(){

    ASTNode * left = Expr2();
    ASTNode * right = nullptr;

    while(token == Symbol::AND){

        right = Expr2();
        left = new AndExpr(left, right);
    }

    return left;
}

ASTNode * ExprParser::Expr2(){

    ASTNode * left = Expr3();
    ASTNode * right = nullptr;

    while(token == Symbol::EQUAL || token == Symbol::NOT_EQUAL){

        Symbol temp = lexer.getNextToken();
        right = Expr3();

        if(token == Symbol::EQUAL){
            left = new EqualExpr(left, right);
        }
        else{
            left = new NotEqualExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr3(){

    ASTNode * left = Expr4();
    ASTNode * right = nullptr;

    while(token == Symbol::GT || token == Symbol::GTE ||
          token == Symbol::LT || token == Symbol::LTE){

        Symbol temp = lexer.getNextToken();
        right = Expr4();

        if(token == Symbol::GT){
            left = new GreaterExpr(left, right);
        }
        else if(token == Symbol::GTE){
            left = new GreaterEqualExpr(left, right);
        }
        else if(token == Symbol::LT){
            left = new LessExpr(left, right);
        }
        else{
            left = new LessEqualExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr4(){

    ASTNode * left = Expr5();
    ASTNode * right = nullptr;

    while(token == Symbol::SHIFT_LEFT || token == Symbol::SHIFT_RIGHT){

        Symbol temp = lexer.getNextToken();
        right = Expr5();

        if(token == Symbol::SHIFT_LEFT){
            left = new ShiftLeftExpr(left, right);
        }
        else{
            left = new ShiftRightExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr5(){

    ASTNode * left = Expr6();
    ASTNode * right = nullptr;

    while(token == Symbol::MOD){

        right = Expr6();
        left = new ModExpr(left, right);
    }

    return left;
}

ASTNode * ExprParser::Expr6(){

    ASTNode * left = Expr7();
    ASTNode * right = nullptr;

    while(token == Symbol::SUM || token == Symbol::SUB){

        Symbol temp = lexer.getNextToken();
        right = Expr6();

        if(token == Symbol::SUM){
            left = new SumExpr(left, right);
        }
        else{
            left = new SubExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr7(){

    ASTNode * left = Expr8();
    ASTNode * right = nullptr;

    while(token == Symbol::MULT || token == Symbol::DIV){

        Symbol temp = lexer.getNextToken();
        right = Expr8();

        if(token == Symbol::MULT){
            left = new MultExpr(left, right);
        }
        else{
            left = new DivExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr8(){

    ASTNode * left = Expr9();
    ASTNode * right = nullptr;

    while(token == Symbol::NEGATION){

        right = Expr9();
        left = new NegationExpr(left, right);
    }

    return left;
}

ASTNode * ExprParser::Expr9(){

    ASTNode * ret;

    if(token == Symbol::OPEN_PAREN){
        token = lexer.getNextToken();
        ret = Expr();
    }
    else if(token == Symbol::ID){
        ret = HandleID();
    }
    else if(lexer.getText() == "System" || lexer.getText() == "Random"){
        ret = MethodCall();
    }
    else{
        ret = Constant();
    }
}

ASTNode * ExprParser::Constant(){

    ASTNode * ret;

    if(token == Symbol::Number){
        ret = new IntExpr(stoi(lexer.getText()));
    }
    else if(token == Symbol::CHAR_CONST){
        ret = new CharExpr(lexer.getText()[0]);
    }
    else if(token == Symbol::KW_TRUE){
        ret = new BoolExpr(true);
    }
    else{
        ret = new BoolExpr(false);
    }
}

ASTNode * ExprParser::HandleID(){

    ASTNode * ret;

    std::string name = lexer.getText();
    token = lexer.getNextToken();

    if(token == Symbol::OPEN_BRACKET){
        
        token = lexer.getNextToken();
        ASTNode * expr = Expr();
        expect(Symbol::CLOSE_BRACKET);

        ret = new IdExpr(name, nullptr);
    }
    else if(token == Symbol::OPEN_PAREN){
        
        ASTNode * args = nullptr;
        token = lexer.getNextToken();
        if(token != Symbol::CLOSE_PAREN){
            args = Args();
        }
        ret = new MethodExpr(name, args);
    }
}

// void ExprParser::Program(){
//     expect(Symbol::KW_CLASS);
//     ClassName();
//     expect(Symbol::OPEN_KEY);
//     FieldDecl();
//     MethodDecl();
//     expect(Symbol::CLOSE_KEY);
// }

// void ExprParser::ClassName(){
//     expect(Symbol::ID);
// }

// void ExprParser::FieldDecl(){
//     Type();
//     // cout << "Current token is " << lexer.getText() << endl;
//     FieldDeclPrime();
//     // cout << "Finished parsing field decl\n";
// }

// void ExprParser::FieldDeclPrime(){
//     // cout << "FDP\n";
//     // cout << "Current token is " << lexer.getText() << endl;
//     expect(Symbol::ID);
//     if(token == Symbol::ASSIGN){
//         Constant();
//         expect(Symbol::SEMICOLON);
//     }
//     else{
//         //expect(Symbol::ID);
//         if(token == Symbol::OPEN_BRACKET){
//             token = lexer.getNextToken();
//             expect(Symbol::Number);
//             expect(Symbol::CLOSE_BRACKET);
//         }
//         while(token == Symbol::COMMA){
//             token = lexer.getNextToken();
//             expect(Symbol::ID);
//             if(token == Symbol::OPEN_BRACKET){
//                 token = lexer.getNextToken();
//                 expect(Symbol::Number);
//                 expect(Symbol::CLOSE_BRACKET);
//             }
//         }
//     }
//     expect(Symbol::SEMICOLON);
// }

// void ExprParser::Constant(){
//     if(token == Symbol::Number ||
//        token == Symbol::CHAR_CONST ||
//        token == Symbol::KW_TRUE ||
//        token == Symbol::KW_FALSE){

//            token = lexer.getNextToken();
//        }
// }

// void ExprParser::Type(){
//     if(token == Symbol::KW_BOOL || token == Symbol::KW_INT){
//         token = lexer.getNextToken();
//         cout << "Found type\n";
//     }
//     else{
//         std::string error = std::string("Expected type keyword, but found ") + lexer.getText()+ " in line " + std::to_string(lexer.getLine());
//         throw_error(error);
//     }
// }

// void ExprParser::MethodDecl(){
//     if(token == Symbol::KW_BOOL || token == Symbol::KW_INT || token == Symbol::KW_VOID){
//         token = lexer.getNextToken();
//     }
//     else{
//         std::string error = std::string("Expected type keyword, but found") + lexer.getText()+ " in line " + std::to_string(lexer.getLine());
//         throw_error(error);
//     }
//     expect(Symbol::ID);
//     expect(Symbol::OPEN_PAREN);
//     // get params
//     if(token == Symbol::CLOSE_PAREN){
//         // cout << "Method has no args\n";
//         token = lexer.getNextToken();
//     }
//     else{
//         while(token != Symbol::CLOSE_PAREN){
//             Type();
//             expect(Symbol::ID);
//             while(token == Symbol::COMMA){
//                 token = lexer.getNextToken();
//                 Type();
//                 expect(Symbol::ID);
//             }
//         }
//         token = lexer.getNextToken();
//     }
//     // cout << "Current token is " << lexer.getText() << endl;
//     Block();
// }

// void ExprParser::Block(){
//     expect(Symbol::OPEN_KEY);
//     VarDecl();
//     while(token == Symbol::SEMICOLON){
//         token = lexer.getNextToken();
//         if(token != Symbol::KW_BOOL && token != Symbol::KW_INT)
//             break;
//         VarDecl();
//     }
//     while(token != Symbol::CLOSE_KEY){
//         Statement();
//     }
//     // Statement();
//     expect(Symbol::CLOSE_KEY);
// }

// void ExprParser::VarDecl(){
//     Type();
//     expect(Symbol::ID);
//     while(token == Symbol::COMMA){
//         token = lexer.getNextToken();
//         expect(Symbol::ID);
//     }
// }

// void ExprParser::Statement(){
//     if(token == Symbol::KW_BREAK){
//         token = lexer.getNextToken();
//         expect(Symbol::SEMICOLON);
//     }
//     else if(token == Symbol::KW_CONTINUE){
//         token = lexer.getNextToken();
//         expect(Symbol::SEMICOLON);
//     }
//     else if(token == Symbol::KW_RETURN){
//         token = lexer.getNextToken();
//         if(token != Symbol::SEMICOLON){
//             Expr();
//             expect(Symbol::SEMICOLON);
//         }
//     }
//     else if(token == Symbol::KW_WHILE){
//         expect(Symbol::OPEN_PAREN);
//         Expr();
//         expect(Symbol::CLOSE_PAREN);
//         Block();
//     }
//     else if(token == Symbol::KW_IF){
//         expect(Symbol::OPEN_PAREN);
//         Expr();
//         expect(Symbol::CLOSE_PAREN);
//         Block();
//         if(token == Symbol::KW_ELSE){
//             token = lexer.getNextToken();
//             Block();
//         }
//     }
//     else if(token == Symbol::KW_FOR){
//         token = lexer.getNextToken();
//         expect(Symbol::OPEN_PAREN);
//         Assign();
//         while(token == Symbol::COMMA){
//             token = lexer.getNextToken();
//             Assign();
//         }
//         expect(Symbol::SEMICOLON);
//         Expr();
//         expect(Symbol::SEMICOLON);
//         Assign();
//         while(token == Symbol::COMMA){
//             token = lexer.getNextToken();
//             Assign();
//         }
//         expect(Symbol::CLOSE_PAREN);
//         Block();
//     }
//     else if(token == Symbol::OPEN_KEY){
//         Block();
//     }
//     else if(token == Symbol::ID){
//         cout << "Found ID\n";
//         token = lexer.getNextToken();
//         ID_Next();
//     }
//     else{
//         MethodCall();
//     }
// }

// void ExprParser::ID_Next(){
//     if(token == Symbol::OPEN_PAREN){
//         token = lexer.getNextToken();
//         if(token != Symbol::CLOSE_PAREN){
//             Expr();
//             while(token == Symbol::COMMA){
//                 Expr();
//             }
//         }
//         expect(Symbol::CLOSE_PAREN);
//     }
//     else if(token == Symbol::OPEN_BRACKET){
//         token = lexer.getNextToken();
//         Expr();
//         expect(Symbol::CLOSE_BRACKET);
//     }
//     else if(token == Symbol::ASSIGN){
//         token = lexer.getNextToken();
//         Expr();
//     }
// }

// void ExprParser::Argument(){
//     if(token == Symbol::STRING_CONST){
//         token = lexer.getNextToken();
//     }
//     else {
//         Expr();
//     }
// }

// void ExprParser::Assign(){
//     LValue();
//     expect(Symbol::ASSIGN);
//     Expr();
// }

// void ExprParser::LValue(){
//     if(token == Symbol::ID){
//         token = lexer.getNextToken();
//         if(token == Symbol::OPEN_BRACKET){
//             token = lexer.getNextToken();
//             expect(Symbol::CLOSE_BRACKET);
//         }
//     }
// }

// void ExprParser::Expr(){
//     Expr1();
    
//     while(token == Symbol::OR){
//         token = lexer.getNextToken();
//         Expr1();
//     }
// }

// void ExprParser::Expr1(){
//     Expr2();
    
//     while(token == Symbol::AND){
//         token = lexer.getNextToken();
//         Expr2();
//     }
// }

// void ExprParser::Expr2(){
//     Expr3();
    
//     while(token == Symbol::EQUAL || token == Symbol::NOT_EQUAL){
//         token = lexer.getNextToken();
//         Expr3();
//     }
// }

// void ExprParser::Expr3(){
//     Expr4();
    
//     while(token == Symbol::LT || token == Symbol::LTE || token == Symbol::GT || token == Symbol::GTE){
//         token = lexer.getNextToken();
//         Expr4();
//     }
// }

// void ExprParser::Expr4(){
//     Expr5();
    
//     while(token == Symbol::SHIFT_LEFT || token == Symbol::SHIFT_RIGHT){
//         token = lexer.getNextToken();
//         Expr5();
//     }
// }

// void ExprParser::Expr5(){
//     Expr6();
    
//     while(token == Symbol::MOD){
//         token = lexer.getNextToken();
//         Expr6();
//     }
// }

// void ExprParser::Expr6(){
//     Expr7();
    
//     while(token == Symbol::SUM || token == Symbol::SUB){
//         token = lexer.getNextToken();
//         Expr7();
//     }
// }

// void ExprParser::Expr7(){
//     Expr8();
    
//     while(token == Symbol::MULT || token == Symbol::DIV){
//         token = lexer.getNextToken();
//         Expr8();
//     }
// }

// void ExprParser::Expr8(){
//     Expr9();
    
//     while(token == Symbol::NEGATION){
//         token = lexer.getNextToken();
//         Expr9();
//     }
// }

// void ExprParser::Expr9(){
//     Expr10();
    
//     while(token == Symbol::SUB){
//         token = lexer.getNextToken();
//         Expr10();
//     }
// }

// void ExprParser::Expr10(){
//     if(token == Symbol::OPEN_PAREN){
//         token = lexer.getNextToken();
//         Expr();
//     }
//     else if(token == Symbol::Number){
//         token = lexer.getNextToken();
//     }
//     else if(token == Symbol::CHAR_CONST){
//         token = lexer.getNextToken();
//     }
//     else if(token == Symbol::KW_TRUE){
//         token = lexer.getNextToken();
//     }
//     else if(token == Symbol::KW_FALSE){
//         token = lexer.getNextToken();
//     }
//     //handle lvalue and methodcall
// }

// void ExprParser::MethodCall(){
//     if(token == Symbol::ID){
//         expect(Symbol::OPEN_PAREN);
//         if(token != Symbol::CLOSE_PAREN){
//             Expr();
//             while(token == Symbol::COMMA){
//                 Expr();
//             }
//         }
//         expect(Symbol::CLOSE_PAREN);
//     }
//     else if(lexer.getText() == "Random"){
//         expect(Symbol::POINT);
//         if(lexer.getText() == "nextInt"){
//             expect(Symbol::OPEN_PAREN);
//             Expr();
//             expect(Symbol::CLOSE_PAREN);
//         }
//     }
//     else if(lexer.getText() == "System"){
//         expect(Symbol::POINT);
//         if(lexer.getText() == "in"){
//             expect(Symbol::POINT);
//             if(lexer.getText() == "read"){
//                 expect(Symbol::OPEN_PAREN);
//                 expect(Symbol::CLOSE_PAREN);
//             }
//         }
//         else if(lexer.getText() == "out"){
//             expect(Symbol::POINT);
//             if(lexer.getText() == "print"){
//                 expect(Symbol::OPEN_PAREN);
//                 Argument();
//                 expect(Symbol::CLOSE_PAREN);
//             }
//             else if(lexer.getText() == "println"){
//                 expect(Symbol::OPEN_PAREN);
//                 Argument();
//                 expect(Symbol::CLOSE_PAREN);
//             }
//         }
//     }
// }