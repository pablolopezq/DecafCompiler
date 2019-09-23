#if !defined(ExprAst)
#define ExprAst

#include <string>
#include <vector>

class Visitor;

enum class Type{
    Bool,
    Int,
    Char,
    String,
    Void
};

struct Value{

    Value(){}
    Value(Type type) : type(type) {}
    // ~Value(){}

    Type type;
    union{
        int num_val;
        bool bool_val;
    };
    std::string string_val;
    
};

enum class NodeKind{
    ProgramExpr,
    BinaryExpr,
    IdExpr,
    MethodCallExpr,
    ArgsExpr,
    PrintExpr,
    PrintlnExpr,
    ReadExpr,
    RandomExpr,
    FieldExpr,
    IntExpr,
    CharExpr,
    BoolExpr,
    StringExpr,
    SumExpr,
    SubExpr,
    MultExpr,
    DivExpr,
    ModExpr,
    ShiftLeftExpr,
    ShiftRightExpr,
    GreaterExpr,
    LessExpr,
    GreaterEqualExpr,
    LessEqualExpr,
    EqualExpr,
    NotEqualExpr,
    AndExpr,
    OrExpr,
    NegationExpr,
    MethodDecl
};

class ASTNode {

public:
    ASTNode(){}

    void accept(Visitor visitor);

    NodeKind getKind(){
        return kind;
    }

    NodeKind kind;
    
};

class ProgramExpr : public ASTNode{

public:
    ProgramExpr(std::string name, std::vector<ASTNode*> * fields, std::vector<ASTNode*> * methods) : 
                name(name), fields(fields), methods(methods)
                { kind = NodeKind::ProgramExpr; }
            
    std::string name;
    std::vector<ASTNode*> * fields;
    std::vector<ASTNode*> * methods;
};

class FieldExpr : public ASTNode{

public:
    FieldExpr(){ kind = NodeKind::FieldExpr; }

    Type type;
    ASTNode * id;
};

class MethodDecl : public ASTNode{

public:
    MethodDecl(Type type, std::string name, ASTNode * args, ASTNode * block) : 
    type(type), name(name), args(args), block(block) 
    { kind = NodeKind::MethodDecl; }

    Type type;
    std::string name;
    ASTNode * args;
    ASTNode * block;

};

class BinaryExpr : public ASTNode {

public:
    BinaryExpr(ASTNode * expr1, ASTNode * expr2) : expr1(expr1), expr2(expr2) 
    { kind = NodeKind::BinaryExpr; }

    ASTNode * expr1;
    ASTNode * expr2;

};

class IdExpr : public ASTNode{

public:
    IdExpr(std::string name, ASTNode * expr) : name(name), expr(expr)
    { kind = NodeKind::IdExpr; }

    std::string name;
    ASTNode * expr;
};

class MethodCallExpr : public ASTNode{

public:
    MethodCallExpr(std::string name, ASTNode * args) : name(name), args(args) 
    { kind = NodeKind::MethodCallExpr; }

    std::string name;
    ASTNode * args;
};

class ArgsExpr : public ASTNode{

public:
    ArgsExpr(std::vector<ASTNode*> * args) : args(args) 
    { kind = NodeKind::ArgsExpr; }

    std::vector<ASTNode*> * args;
};

class PrintExpr : public ASTNode{

public:
    PrintExpr(ASTNode * argument) : argument(argument) 
    { kind = NodeKind::PrintExpr; }

    ASTNode * argument;
};

class PrintlnExpr : public ASTNode{

public:
    PrintlnExpr(ASTNode * argument) : argument(argument) 
    { kind = NodeKind::PrintlnExpr; }

    ASTNode * argument;
};

class ReadExpr : public ASTNode{

public:
    ReadExpr() 
    { kind = NodeKind::ReadExpr; }
};

class RandomExpr : public ASTNode{

public:
    RandomExpr(ASTNode * expr) : expr(expr) 
    { kind = NodeKind::RandomExpr; }

    ASTNode * expr;
};


#define DEFINE_BINARY_EXPR(name) \
class name##Expr : public BinaryExpr { \
public: \
        name##Expr (ASTNode * expr1, ASTNode * expr2): BinaryExpr(expr1, expr2)\
        { kind = NodeKind::name##Expr; } \
};

#define DEFINE_CONST_EXPR(name, type) \
class name##Expr : public ASTNode { \
public: \
        name##Expr (type value) : value(value)\
        { kind = NodeKind::name##Expr; } \
\
    type value;\
};

DEFINE_CONST_EXPR(Int, int);
DEFINE_CONST_EXPR(Char, char);
DEFINE_CONST_EXPR(Bool, bool);
DEFINE_CONST_EXPR(String, std::string);

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
