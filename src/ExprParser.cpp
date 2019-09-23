#include "ExprParser.h"
#include "Symbols.h"

#include <cstring>

void ExprParser::parse(){
    token = lexer.getNextToken();
    Program();
    // ASTNode* expr = Expr();
    if(token != Symbol::Eof){
        throw std::string("Parser stopped unexpectedly on token: ") + lexer.getText();
    }
    // statements.push_back(expr);
}

ASTNode * ExprParser::Program(){

    // std::vector<ASTNode*> statements;

    expect(Symbol::KW_CLASS);
    expect(Symbol::ID);
    expect(Symbol::OPEN_KEY);

    while(token != Symbol::CLOSE_KEY){
        if(token == Symbol::KW_VOID){
            std::vector<ASTNode*> args;
            advanceToken();
            std::string method_name = lexer.getText();
            expect(Symbol::ID);
            expect(Symbol::OPEN_PAREN);
            // if(token != Symbol::CLOSE_PAREN){
            //     while(token == Symbol::COMMA){
            //         if(token == Symbol::KW_BOOL){
            //             advanceToken();
            //             std::string param_name = lexer.getText();

            //         }
            //     }
            // }
            expect(Symbol::CLOSE_PAREN);
            std::vector<ASTNode*> block;
            block = Block();
            ASTNode* push = new MethodDeclExpr(Type::Void, method_name, args, block);
            statements.push_back(push);
        }
        // else if(token == Symbol::KW_BOOL){
        //     advanceToken();
        //     std::string name = lexer.getText();
        //     expect(Symbol::ID);
        //     if(token == Symbol::ASSIGN){
        //         advanceToken();
        //         ASTNode * con = Constant();
        //         expect(Symbol::SEMICOLON);
        //         fields.push_back(new FieldAssignExpr(Type::Bool, name, con));
        //     }
        //     else if(token == Symbol::OPEN_PAREN){

        //     }
        // }
        // else if(token == Symbol::KW_INT){
        //     advanceToken();
        //     std::string name = lexer.getText();
        //     expect(Symbol::ID);
        //     if(token == Symbol::ASSIGN){
        //         advanceToken();
        //         ASTNode * con = Constant();
        //         expect(Symbol::SEMICOLON);
        //         fields.push_back(new FieldAssignExpr(Type::Int, name, con));
        //     }
        // }
    }
    expect(Symbol::CLOSE_KEY);
}

std::vector<ASTNode*> ExprParser::Block(){

    std::vector<ASTNode*> ret;

    expect(Symbol::OPEN_KEY);

    while(token != Symbol::CLOSE_KEY){

        if(lexer.getText() == "System" || lexer.getText() == "Random"){
            ASTNode * stmt = MethodCall();
            expect(Symbol::SEMICOLON);
            ret.push_back(stmt);
        }
        else if(token == Symbol::KW_INT || token == Symbol::KW_BOOL){
            Symbol temp = token;
            std::string var_name;
            advanceToken();
            var_name = lexer.getText();
            expect(Symbol::ID);
            ASTNode * expr;
            if(temp == Symbol::KW_BOOL)
                expr = new FieldExpr(Type::Bool, var_name);
            else
                expr = new FieldExpr(Type::Int, var_name);
            
            ret.push_back(expr);
            
            while(token == Symbol::COMMA){
                advanceToken();
                var_name = lexer.getText();
                expect(Symbol::ID);
                if(temp == Symbol::KW_BOOL)
                    expr = new FieldExpr(Type::Bool, var_name);
                else
                    expr = new FieldExpr(Type::Int, var_name);
                
                ret.push_back(expr);
            }
            expect(Symbol::SEMICOLON);
        }
        else if(token == Symbol::ID){
            std::string var_name = lexer.getText();;
            advanceToken();
            if(token == Symbol::ASSIGN){
                advanceToken();
                ASTNode * expr = Expr();
                ASTNode * assign = new VarAssignExpr(var_name, expr);
                ret.push_back(assign);
            }
            expect(Symbol::SEMICOLON);
        }
        else if(token == Symbol::KW_IF){
            advanceToken();
            expect(Symbol::OPEN_PAREN);
            ASTNode * expr = Expr();
            expect(Symbol::CLOSE_PAREN);
            std::vector<ASTNode*> then_block = Block();
            std::vector<ASTNode*> else_block;
            if(token == Symbol::KW_ELSE){
                advanceToken();
                else_block = Block();
                // std::cout << "Pushing if expr\n";
                ret.push_back(new IfExpr(expr, then_block, else_block));
            }
            else{
                // std::cout << "Pushing if expr\n";
                ret.push_back(new IfExpr(expr, then_block, else_block));
            }
        }
    }
    expect(Symbol::CLOSE_KEY);
    return ret;
}

ASTNode * ExprParser::Expr(){

    // cout << "Entered Expr\n";

    ASTNode * left = Expr1();
    ASTNode * right = nullptr;

    while(token == Symbol::OR){

        advanceToken();

        right = Expr1();
        left = new OrExpr(left, right);
    }

    return left;
}

ASTNode * ExprParser::Expr1(){
    // cout << "Entered Expr1\n";

    ASTNode * left = Expr2();
    ASTNode * right = nullptr;

    while(token == Symbol::AND){

        advanceToken();

        right = Expr2();
        left = new AndExpr(left, right);
    }

    return left;
}

ASTNode * ExprParser::Expr2(){
    // cout << "Entered Expr2\n";

    ASTNode * left = Expr3();
    ASTNode * right = nullptr;

    while(token == Symbol::EQUAL || token == Symbol::NOT_EQUAL){

        Symbol temp = token;
        advanceToken();
        right = Expr3();

        if(temp == Symbol::EQUAL){
            left = new EqualExpr(left, right);
        }
        else{
            left = new NotEqualExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr3(){
    // cout << "Entered Expr3\n";

    ASTNode * left = Expr4();
    ASTNode * right = nullptr;

    while(token == Symbol::GT || token == Symbol::GTE ||
          token == Symbol::LT || token == Symbol::LTE){

        Symbol temp = token;
        advanceToken();
        right = Expr4();

        if(temp == Symbol::GT){
            left = new GreaterExpr(left, right);
        }
        else if(temp == Symbol::GTE){
            left = new GreaterEqualExpr(left, right);
        }
        else if(temp == Symbol::LT){
            left = new LessExpr(left, right);
        }
        else{
            left = new LessEqualExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr4(){
    // cout << "Entered Expr4\n";

    ASTNode * left = Expr5();
    ASTNode * right = nullptr;

    while(token == Symbol::SHIFT_LEFT || token == Symbol::SHIFT_RIGHT){

        Symbol temp = token;
        advanceToken();
        right = Expr5();

        if(temp == Symbol::SHIFT_LEFT){
            left = new ShiftLeftExpr(left, right);
        }
        else{
            left = new ShiftRightExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr5(){
    // cout << "Entered Expr5\n";

    ASTNode * left = Expr6();
    ASTNode * right = nullptr;

    while(token == Symbol::MOD){

        // std::cout << "Found mod expr\n";

        advanceToken();

        right = Expr6();
        left = new ModExpr(left, right);
    }

    return left;
}

ASTNode * ExprParser::Expr6(){
    // cout << "Entered Expr6\n";

    ASTNode * left = Expr7();
    ASTNode * right = nullptr;

    while(token == Symbol::SUM || token == Symbol::SUB){

        Symbol temp = token;
        // std::cout << lexer.getText();
        advanceToken();
        right = Expr6();

        if(temp == Symbol::SUM){
            // std::cout << "Found sum\n";
            left = new SumExpr(left, right);
        }
        else{
            // std::cout << "Found sub\n";
            left = new SubExpr(left, right);
        }
    }

    return left;
}

ASTNode * ExprParser::Expr7(){
    // cout << "Entered Expr7\n";

    ASTNode * left = Expr9();
    ASTNode * right = nullptr;

    while(token == Symbol::MULT || token == Symbol::DIV){

        Symbol temp = token;
        // std::cout << lexer.getText();
        advanceToken();
        right = Expr9();

        if(temp == Symbol::MULT){
            // std::cout << "Found mult\n";
            left = new MultExpr(left, right);
        }
        else{
            // std::cout << "Found div\n";
            left = new DivExpr(left, right);
        }
    }

    return left;
}

// ASTNode * ExprParser::Expr8(){
//     // cout << "Entered Expr8\n";

//     ASTNode * left = Expr9();
//     ASTNode * right = nullptr;

//     while(token == Symbol::NEGATION){

//         advanceToken();

//         right = Expr9();
//         left = new NegationExpr(left, right);
//     }

//     return left;
// }

ASTNode * ExprParser::Expr9(){
    // cout << "Entered Expr9\n";

    ASTNode * ret;

    if(token == Symbol::OPEN_PAREN){
        token = lexer.getNextToken();
        ret = Expr();
    }
    else if(lexer.getText() == "System" || lexer.getText() == "Random"){
        ret = MethodCall();
    }
    else if(token == Symbol::ID){
        ret = HandleID();
    }
    else{
        ret = Constant();
    }

    return ret;
}

ASTNode * ExprParser::Constant(){
    // cout << "Entered Constant with token " + lexer.getText() + " " + lexer.tokenToString(token) << endl;

    ASTNode * ret;

    if(token == Symbol::Number){
        // cout << "Found number\n";
        ret = new IntExpr(stoi(lexer.getText()));
    }
    else if(token == Symbol::CHAR_CONST){
        ret = new CharExpr(lexer.getText()[0]);
    }
    else if(token == Symbol::KW_TRUE){
        ret = new BoolExpr(true);
    }
    else if(token == Symbol::KW_FALSE){
        ret = new BoolExpr(false);
    }
    else{
        throw std::string("Error");
    }

    token = lexer.getNextToken();

    return ret;
}

ASTNode * ExprParser::HandleID(){

    ASTNode * ret = nullptr;

    std::string name = lexer.getText();
    token = lexer.getNextToken();

    // cout << "Found id: " << name << endl;

    // cout << "Follow is " << lexer.getText() << " " << lexer.tokenToString(token) << endl;

    if(token == Symbol::OPEN_BRACKET){
        
        token = lexer.getNextToken();
        ASTNode * expr = Expr();
        expect(Symbol::CLOSE_BRACKET);

        ret = new IdExpr(name, expr);
    }
    else if(token == Symbol::OPEN_PAREN){
        advanceToken();
        ASTNode * args = nullptr;
        if(token != Symbol::CLOSE_PAREN){
            // cout << "Call has arguments\n";
            args = Args();
        }
        // cout << "Obtained args\n";
        expect(Symbol::CLOSE_PAREN);
        ret = new MethodCallExpr(name, args);
    }
    else{
        ret = new IdExpr(name, nullptr);
        // cout << "Returning id " << name << "\n";;
    }

    return ret;
}

ASTNode * ExprParser::MethodCall(){

    ASTNode * ret;

    if(lexer.getText() == "System"){
        advanceToken();
        expect(Symbol::POINT);
        if(lexer.getText() == "out"){
            advanceToken();
            expect(Symbol::POINT);
            if(lexer.getText() == "print"){
                advanceToken();
                expect(Symbol::OPEN_PAREN);
                ASTNode * arg = Argument();
                expect(Symbol::CLOSE_PAREN);
                ret = new PrintExpr(arg);
            }
            else if(lexer.getText() == "println"){
                advanceToken();
                expect(Symbol::OPEN_PAREN);
                ASTNode * arg = Argument();
                expect(Symbol::CLOSE_PAREN);
                ret = new PrintlnExpr(arg);
            }
        }
        else if(lexer.getText() == "in"){
            advanceToken();
            expect(Symbol::OPEN_PAREN);
            expect(Symbol::CLOSE_PAREN);
            ret = new ReadExpr();
        }
    }
    else if(lexer.getText() == "Random"){
        advanceToken();
        expect(Symbol::POINT);
        if(lexer.getText() == "nextInt"){
            advanceToken();
            expect(Symbol::OPEN_PAREN);
            ASTNode * expr = Expr();
            ret = new RandomExpr(expr);
        }
    }

    return ret;
}

ASTNode * ExprParser::Argument(){
    if(token == Symbol::STRING_CONST){
        std::string param = lexer.getText();
        advanceToken();
        return new StringExpr(param);
    }
    else{
        // cout << "Getting expr param\n";
        return Expr();
    }
}

ASTNode * ExprParser::Args(){

    std::vector<ASTNode*> * args = new std::vector<ASTNode*>;

    // cout << "Getting arguments\n";

    ASTNode * arg = Expr();
    // cout << "Pushing first argument...\n";
    args->push_back(arg);
    // cout << "Pushed first argument\n";

    while(token == Symbol::COMMA){
        advanceToken();
        arg = Expr();
        // cout << "Pushing arg into vector\n";
        args->push_back(arg);
    }

    return new ArgsExpr(args);
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