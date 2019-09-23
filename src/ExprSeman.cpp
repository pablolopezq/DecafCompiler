#include "ExprSeman.h"
#include <iostream>

void ExprSemantic::check(){

    Visitor visitor(tbl);

    for(ASTNode * node : statements){
        visitor.visit(node);
    }
}

Type ExprSemantic::Visitor::visit(ASTNode* node){

    NodeKind kind = node->getKind();

    switch (kind){

    // case NodeKind::IdExpr:
    //     return visit(reinterpret_cast<IdExpr *>(node));
    //     break;

    // case NodeKind::MethodCallExpr:
    //     return visit(reinterpret_cast<MethodCallExpr *>(node));
    //     break;

    // case NodeKind::ArgsExpr:
    //     return visit(reinterpret_cast<ArgsExpr *>(node));
    //     break;

    case NodeKind::PrintExpr:
        return visit(reinterpret_cast<PrintExpr *>(node));
        break;

    case NodeKind::PrintlnExpr:
        return visit(reinterpret_cast<PrintlnExpr *>(node));
        break;

    case NodeKind::MethodDeclExpr:
        return visit(reinterpret_cast<MethodDeclExpr *>(node));
        break;

    case NodeKind::FieldExpr:
        return visit(reinterpret_cast<FieldExpr *>(node));
        break;

    case NodeKind::VarAssignExpr:
        return visit(reinterpret_cast<VarAssignExpr *>(node));
        break;

    // case NodeKind::ReadExpr:
    //     return visit(reinterpret_cast<ReadExpr *>(node));
    //     break;

    // case NodeKind::RandomExpr:
    //     return visit(reinterpret_cast<RandomExpr *>(node));
    //     break;

    case NodeKind::IntExpr:
        return visit(reinterpret_cast<IntExpr *>(node));
        break;

    case NodeKind::CharExpr:
        return visit(reinterpret_cast<CharExpr *>(node));
        break;

    case NodeKind::BoolExpr:
        return visit(reinterpret_cast<BoolExpr *>(node));
        break;

    case NodeKind::StringExpr:
        return visit(reinterpret_cast<StringExpr *>(node));
        break;

    case NodeKind::SumExpr:
        return visit(reinterpret_cast<SumExpr *>(node));
        break;

    case NodeKind::SubExpr:
        return visit(reinterpret_cast<SubExpr *>(node));
        break;

    case NodeKind::MultExpr:
        return visit(reinterpret_cast<MultExpr *>(node));
        break;

    case NodeKind::DivExpr:
        return visit(reinterpret_cast<DivExpr *>(node));
        break;

    case NodeKind::ModExpr:
        return visit(reinterpret_cast<ModExpr *>(node));
        break;

    case NodeKind::ShiftLeftExpr:
        return visit(reinterpret_cast<ShiftLeftExpr *>(node));
        break;

    case NodeKind::ShiftRightExpr:
        return visit(reinterpret_cast<ShiftRightExpr *>(node));
        break;

    case NodeKind::GreaterEqualExpr:
        return visit(reinterpret_cast<GreaterEqualExpr *>(node));
        break;

    case NodeKind::GreaterExpr:
        return visit(reinterpret_cast<GreaterExpr *>(node));
        break;

    case NodeKind::LessEqualExpr:
        return visit(reinterpret_cast<LessEqualExpr *>(node));
        break;

    case NodeKind::LessExpr:
        return visit(reinterpret_cast<LessExpr *>(node));
        break;

    case NodeKind::EqualExpr:
        return visit(reinterpret_cast<EqualExpr *>(node));
        break;

    case NodeKind::NotEqualExpr:
        return visit(reinterpret_cast<NotEqualExpr *>(node));
        break;

    case NodeKind::AndExpr:
        return visit(reinterpret_cast<AndExpr *>(node));
        break;

    case NodeKind::OrExpr:
        return visit(reinterpret_cast<OrExpr *>(node));
        break;

    case NodeKind::IfExpr:
        return visit(reinterpret_cast<IfExpr *>(node));
        break;

    case NodeKind::WhileExpr:
        return visit(reinterpret_cast<WhileExpr *>(node));
        break;

    case NodeKind::ForExpr:
        return visit(reinterpret_cast<ForExpr *>(node));
        break;

    case NodeKind::ReturnExpr:
        return visit(reinterpret_cast<ReturnExpr *>(node));
        break;

    // case NodeKind::NegationExpr:
    //     return visit(reinterpret_cast<NegationExpr *>(node));
    //     break;

    default:
        break;
    }
}

Type ExprSemantic::Visitor::visit(IdExpr* node){
    return Type::Void;
}

Type ExprSemantic::Visitor::visit(PrintExpr* node){
    return Type::Void;
}

Type ExprSemantic::Visitor::visit(PrintlnExpr* node){
    return Type::Void;
}

Type ExprSemantic::Visitor::visit(MethodDeclExpr* node){
    SymbTbl::iterator it = tbl.find(node->name);
    if(it == tbl.end()){
        tbl.emplace(node->name, node->type);
    }
    else{
        throw std::string("Method " + node->name + " is already defined\n");
    }

    for(ASTNode* s : node->block){
        visit(s);
    }

    return Type::Void;
}

Type ExprSemantic::Visitor::visit(FieldExpr* node){
    SymbTbl::iterator it = tbl.find(node->name);
    if(it == tbl.end()){
        tbl.emplace(node->name, node->type);
        // std::cout << "Defined\n";
    }
    else{
        throw std::string("Variable " + node->name + " is already defined\n");
    }

    return Type::Void;
}

Type ExprSemantic::Visitor::visit(VarAssignExpr* node){
    SymbTbl::iterator it = tbl.find(node->name);
    if(it == tbl.end()){
        throw std::string("Variable " + node->name + " is not defined\n");
    }

    return Type::Void;
}

Type ExprSemantic::Visitor::visit(IntExpr * node){
    return Type::Int;
}
Type ExprSemantic::Visitor::visit(CharExpr * node){
    return Type::Char;
}
Type ExprSemantic::Visitor::visit(BoolExpr * node){
    return Type::Bool;
}
Type ExprSemantic::Visitor::visit(StringExpr * node){
    return Type::String;
}
Type ExprSemantic::Visitor::visit(SubExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}

Type ExprSemantic::Visitor::visit(SumExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(MultExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(DivExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(ModExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(ShiftRightExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(ShiftLeftExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(GreaterEqualExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(GreaterExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(LessEqualExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(LessExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(EqualExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(NotEqualExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}
Type ExprSemantic::Visitor::visit(AndExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}

Type ExprSemantic::Visitor::visit(OrExpr * node){

    Value v1, v2;

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    if(v1.type == v2.type){
        return v1.type;
    }
}

Type ExprSemantic::Visitor::visit(IfExpr * node){
    
    Value val = visit(node->expr);
    if(val.type == Type::Bool){
        return val.type;
    }
    return Type::Void;
}

Type ExprSemantic::Visitor::visit(WhileExpr * node){
    
    Value val = visit(node->expr);
    if(val.type == Type::Bool){
        return val.type;
    }
    return Type::Void;
}

Type ExprSemantic::Visitor::visit(ForExpr * node){
    
    Value val = visit(node->expr);
    if(val.type == Type::Bool){
        return val.type;
    }
    return Type::Void;
}

Type ExprSemantic::Visitor::visit(ReturnExpr * node){
    return Type::Void;
}
// Type ExprSemantic::Visitor::visit(NegationExpr * node){

//     Value v1, v2;

//     v1 = visit(node->expr1);
//     v2 = visit(node->expr2);

//     if(v1.type == v2.type){
//         return v1.type;
//     }
//     else{
//         throw std::string("Error - Tried to operate different types\n");
//     }
// }