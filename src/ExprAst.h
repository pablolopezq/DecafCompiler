#if !defined(ExprAst)
#define ExprAst

#include <string>

class ASTNode {

public:
    ASTNode(){}

    // virtual std::string toString() = 0;
    
};

class BinaryExpr : public ASTNode {

public:
    BinaryExpr(ASTNode * expr1, ASTNode * expr2) : expr1(expr1), expr2(expr2) {}

private:
    ASTNode * expr1;
    ASTNode * expr2;

};

#define DEFINE_BINARY_EXPR(name) \  
class name##Expr : public BinaryExpr { \
public: \
        name##Expr (ASTNode * expr1, ASTNode * expr2): BinaryExpr(expr1, expr2){} \
};

#define DEFINE_CONST_EXPR(name, type) \  
class name##Expr : public ASTNode { \
public: \
        name##Expr (type value) : value(value){} \
\
private:\
    type value;\
};

DEFINE_CONST_EXPR(Int, int);
DEFINE_CONST_EXPR(Char, char);
DEFINE_CONST_EXPR(Bool, bool);

DEFINE_BINARY_EXPR(Sum);
DEFINE_BINARY_EXPR(Sub);
DEFINE_BINARY_EXPR(Mult);
DEFINE_BINARY_EXPR(Div);
DEFINE_BINARY_EXPR(Mod);
DEFINE_BINARY_EXPR(ShiftRight);
DEFINE_BINARY_EXPR(ShiftLeft);
DEFINE_BINARY_EXPR(Greater);
DEFINE_BINARY_EXPR(Less);
DEFINE_BINARY_EXPR(GreaterEqual);
DEFINE_BINARY_EXPR(LessEqual);
DEFINE_BINARY_EXPR(Equal);
DEFINE_BINARY_EXPR(NotEqual);
DEFINE_BINARY_EXPR(And);
DEFINE_BINARY_EXPR(Or);
DEFINE_BINARY_EXPR(Negation);

#endif
