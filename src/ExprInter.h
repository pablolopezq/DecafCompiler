#if !defined(ExprInterp)
#define ExprInterp

#include <unordered_map>
#include <string>
#include <vector>

#include "ExprAst.h"

class ExprInter{

public:

    using SymbTbl = std::unordered_map<std::string, Value>;

    ExprInter(SymbTbl tbl, std::vector<ASTNode*> statements) : tbl(tbl), statements(statements) {}

    void execute();

private:
    SymbTbl tbl;
    std::vector<ASTNode*> statements;

    class Visitor{
    
    public:
        Visitor(SymbTbl& tbl, std::vector<ASTNode*>& statements) : tbl(tbl), statements(statements) {}

        Value visit(ASTNode* node);

    private:
        SymbTbl tbl;
        std::vector<ASTNode*> statements;

        Value visit(VarAssignExpr * node);
        Value visit(IfExpr * node);
        Value visit(IdExpr * node);
        Value visit(MethodCallExpr * node);
        Value visit(MethodDeclExpr * node);
        Value visit(ArgsExpr * node);
        Value visit(PrintlnExpr * node);
        Value visit(PrintExpr * node);
        Value visit(ReadExpr * node);
        Value visit(RandomExpr * node);
        Value visit(FieldExpr * node);
        Value visit(IntExpr * node);
        Value visit(CharExpr * node);
        Value visit(BoolExpr * node);
        Value visit(StringExpr * node);
        Value visit(SubExpr * node);
        Value visit(SumExpr * node);
        Value visit(MultExpr * node);
        Value visit(DivExpr * node);
        Value visit(ModExpr * node);
        Value visit(ShiftRightExpr * node);
        Value visit(ShiftLeftExpr * node);
        Value visit(GreaterEqualExpr * node);
        Value visit(GreaterExpr * node);
        Value visit(LessEqualExpr * node);
        Value visit(LessExpr * node);
        Value visit(EqualExpr * node);
        Value visit(NotEqualExpr * node);
        Value visit(AndExpr * node);
        Value visit(OrExpr * node);
        Value visit(NegationExpr * node);
    };
};

#endif // ExprInter
