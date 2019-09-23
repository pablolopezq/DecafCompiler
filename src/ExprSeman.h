#if !defined(ExprSeman)
#define ExprSeman

#include <unordered_map>
#include <vector>

#include "ExprAst.h"

class ExprSemantic {

public:
    ExprSemantic(std::vector<ASTNode*> statements) : statements(statements) {}

    using SymbTbl = std::unordered_map<std::string, Type>;
    
    void check();

    SymbTbl get_table(){
        return tbl;
    }

private:

    std::vector<ASTNode*> statements;
    SymbTbl tbl;

    class Visitor{
    
    public:
        Visitor(SymbTbl& tbl) : tbl(tbl) {}

        Type visit(ASTNode* node);

    private:
        SymbTbl& tbl;

        // Type visit(ProgramExpr * node);
        Type visit(VarAssignExpr * node);
        Type visit(MethodDeclExpr * node);
        Type visit(IdExpr * node);
        Type visit(MethodCallExpr * node);
        Type visit(ArgsExpr * node);
        Type visit(PrintlnExpr * node);
        Type visit(PrintExpr * node);
        Type visit(ReadExpr * node);
        Type visit(RandomExpr * node);
        Type visit(FieldExpr * node);
        Type visit(IntExpr * node);
        Type visit(CharExpr * node);
        Type visit(BoolExpr * node);
        Type visit(StringExpr * node);
        Type visit(SubExpr * node);
        Type visit(SumExpr * node);
        Type visit(MultExpr * node);
        Type visit(DivExpr * node);
        Type visit(ModExpr * node);
        Type visit(ShiftRightExpr * node);
        Type visit(ShiftLeftExpr * node);
        Type visit(GreaterEqualExpr * node);
        Type visit(GreaterExpr * node);
        Type visit(LessEqualExpr * node);
        Type visit(LessExpr * node);
        Type visit(EqualExpr * node);
        Type visit(NotEqualExpr * node);
        Type visit(AndExpr * node);
        Type visit(OrExpr * node);
        Type visit(NegationExpr * node);
    };

};

#endif // ExprSema
