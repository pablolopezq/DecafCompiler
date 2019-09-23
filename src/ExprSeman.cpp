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

    // case NodeKind::ReadExpr:
    //     return visit(reinterpret_cast<ReadExpr *>(node));
    //     break;

    // case NodeKind::RandomExpr:
    //     return visit(reinterpret_cast<RandomExpr *>(node));
    //     break;

    // case NodeKind::FieldExpr:
    //     return visit(reinterpret_cast<FieldExpr *>(node));
    //     break;

    // case NodeKind::IntExpr:
    //     return visit(reinterpret_cast<IntExpr *>(node));
    //     break;

    // case NodeKind::CharExpr:
    //     return visit(reinterpret_cast<CharExpr *>(node));
    //     break;

    // case NodeKind::BoolExpr:
    //     return visit(reinterpret_cast<BoolExpr *>(node));
    //     break;

    // case NodeKind::StringExpr:
    //     return visit(reinterpret_cast<StringExpr *>(node));
    //     break;

    // case NodeKind::SumExpr:
    //     return visit(reinterpret_cast<SumExpr *>(node));
    //     break;

    // case NodeKind::SubExpr:
    //     return visit(reinterpret_cast<SubExpr *>(node));
    //     break;

    // case NodeKind::MultExpr:
    //     return visit(reinterpret_cast<MultExpr *>(node));
    //     break;

    // case NodeKind::DivExpr:
    //     return visit(reinterpret_cast<DivExpr *>(node));
    //     break;

    // case NodeKind::ModExpr:
    //     return visit(reinterpret_cast<ModExpr *>(node));
    //     break;

    // case NodeKind::ShiftLeftExpr:
    //     return visit(reinterpret_cast<ShiftLeftExpr *>(node));
    //     break;

    // case NodeKind::ShiftRightExpr:
    //     return visit(reinterpret_cast<ShiftRightExpr *>(node));
    //     break;

    // case NodeKind::GreaterEqualExpr:
    //     return visit(reinterpret_cast<GreaterEqualExpr *>(node));
    //     break;

    // case NodeKind::GreaterExpr:
    //     return visit(reinterpret_cast<GreaterExpr *>(node));
    //     break;

    // case NodeKind::LessEqualExpr:
    //     return visit(reinterpret_cast<LessEqualExpr *>(node));
    //     break;

    // case NodeKind::LessExpr:
    //     return visit(reinterpret_cast<LessExpr *>(node));
    //     break;

    // case NodeKind::EqualExpr:
    //     return visit(reinterpret_cast<EqualExpr *>(node));
    //     break;

    // case NodeKind::NotEqualExpr:
    //     return visit(reinterpret_cast<NotEqualExpr *>(node));
    //     break;

    // case NodeKind::AndExpr:
    //     return visit(reinterpret_cast<AndExpr *>(node));
    //     break;

    // case NodeKind::OrExpr:
    //     return visit(reinterpret_cast<OrExpr *>(node));
    //     break;

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
