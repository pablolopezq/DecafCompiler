#if !defined(ExprAst)
#define ExprAst

#include <string>
#include <vector>
#include <iostream>

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
        char char_val;
    };
    std::string string_val;

    Value operator +(Value v){
        Value ret(Type::Int);
        ret.num_val = this->num_val + v.num_val;
        // std::cout << "Sum is " << ret.num_val << std::endl;
        return ret;
    }

    Value operator -(Value v){
        Value ret(Type::Int);
        ret.num_val = this->num_val - v.num_val;
        return ret;
    }

    Value operator *(Value v){
        Value ret(Type::Int);
        ret.num_val = this->num_val * v.num_val;
        return ret;
    }

    Value operator /(Value v){
        Value ret(Type::Int);
        ret.num_val = this->num_val / v.num_val;
        return ret;
    }

    Value operator %(Value v){
        Value ret(Type::Int);
        ret.num_val = this->num_val % v.num_val;
        return ret;
    }

    Value operator <(Value v){
        Value ret(Type::Bool);
        ret.bool_val = this->bool_val < v.bool_val;
        return ret;
    }

    Value operator >(Value v){
        Value ret(Type::Bool);
        ret.bool_val = this->bool_val > v.bool_val;
        return ret;
    }

    Value operator <=(Value v){
        Value ret(Type::Bool);
        ret.bool_val = this->bool_val <= v.bool_val;
        return ret;
    }

    Value operator >=(Value v){
        Value ret(Type::Bool);
        ret.bool_val = this->bool_val >= v.bool_val;
        return ret;
    }

    Value operator ==(Value v){
        Value ret(Type::Bool);
        ret.bool_val = this->bool_val == v.bool_val;
        return ret;
    }

    Value operator !=(Value v){
        Value ret(Type::Bool);
        ret.bool_val = this->bool_val != v.bool_val;
        return ret;
    }
    
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
    MethodDeclExpr,
    FieldAssignExpr,
    BlockExpr,
    VarAssignExpr,
    IfExpr,
    WhileExpr,
    ForExpr
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

// class ProgramExpr : public ASTNode{

// public:
//     ProgramExpr(std::string name, std::vector<ASTNode*> fields, std::vector<ASTNode*> methods) : 
//                 name(name), fields(fields), methods(methods)
//                 { kind = NodeKind::ProgramExpr; }
            
//     std::string name;
//     std::vector<ASTNode*> fields;
//     std::vector<ASTNode*> methods;
// };

class FieldExpr : public ASTNode{

public:
    FieldExpr(Type type, std::string name) : 
    type(type), name(name) { kind = NodeKind::FieldExpr; }

    Type type;
    std::string name;
};

class VarAssignExpr : public ASTNode{

public:
    VarAssignExpr(std::string name, ASTNode * expr) :
    name(name), expr(expr) { kind = NodeKind::VarAssignExpr; }

    std::string name;
    ASTNode * expr;
};

class FieldAssignExpr : public ASTNode{

public:
    FieldAssignExpr(Type type, std::string name, ASTNode * constant) :
    type(type), name(name), constant(constant) { kind = NodeKind::FieldAssignExpr; }

    Type type;
    std::string name;
    ASTNode * constant;
};

class MethodDeclExpr : public ASTNode{

public:
    MethodDeclExpr(Type type, std::string name, std::vector<ASTNode*> args, std::vector<ASTNode*> block) : 
    type(type), name(name), args(args), block(block) 
    { kind = NodeKind::MethodDeclExpr; }

    Type type;
    std::string name;
    std::vector<ASTNode*> args;
    std::vector<ASTNode*> block;

};

class BlockExpr : public ASTNode{

public:
    BlockExpr(std::vector<ASTNode*> statements):
    statements(statements) { kind = NodeKind::BlockExpr; }

    std::vector<ASTNode*> statements;
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

class NegationExpr : public ASTNode{

public:
    NegationExpr(ASTNode * expr) : expr(expr) { kind = NodeKind::NegationExpr; }

    ASTNode * expr;
};

class IfExpr : public ASTNode{

public:

    IfExpr(ASTNode* expr, std::vector<ASTNode*> then_block, std::vector<ASTNode*> else_block):
    expr(expr), then_block(then_block), else_block(else_block) 
    { kind = NodeKind::IfExpr; } 

    ASTNode * expr;
    std::vector<ASTNode*> then_block;
    std::vector<ASTNode*> else_block;
};

class WhileExpr : public ASTNode{

public:

    WhileExpr(ASTNode* expr, std::vector<ASTNode*> block):
    expr(expr), block(block)
    { kind = NodeKind::WhileExpr; } 

    ASTNode * expr;
    std::vector<ASTNode*> block;
};

class ForExpr : public ASTNode{

public:

    ForExpr(std::vector<ASTNode*> f_assign, ASTNode * expr,
            std::vector<ASTNode*> s_assign, std::vector<ASTNode*> block):
            f_assign(f_assign), expr(expr), s_assign(s_assign), block(block)
            { kind = NodeKind::ForExpr; }

    ASTNode * expr;
    std::vector<ASTNode*> f_assign;
    std::vector<ASTNode*> s_assign;
    std::vector<ASTNode*> block;

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

#endif
