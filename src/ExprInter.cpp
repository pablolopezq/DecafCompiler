#include "ExprInter.h"
#include <iostream>

void ExprInter::execute(){

    Visitor visitor(tbl);

    // std::cout << statements.size() << std::endl;

    // std::cout << "Visiting...\n";

    for(ASTNode* s : statements){
        // PrintExpr* print = reinterpret_cast<PrintExpr*>(s);
        // StringExpr* arg = reinterpret_cast<StringExpr*>(print->argument);
        // std::cout << arg->value << std::endl;
        visitor.visit(s);
    }

        // std::cout << "Finished visiting\n";
}

Value ExprInter::Visitor::visit(ASTNode * node){

    // std::cout << "Visiting node...\n";

    NodeKind kind = node->getKind();

    switch (kind)
    {
    case NodeKind::PrintExpr:
        // std::cout << "Visiting print expr...\n";
        return visit(reinterpret_cast<PrintExpr *>(node));
        break;

    case NodeKind::PrintlnExpr:
        // std::cout << "Visiting print expr...\n";
        return visit(reinterpret_cast<PrintlnExpr *>(node));
        break;
    
    case NodeKind::StringExpr:
        return visit(reinterpret_cast<StringExpr *>(node));
        break;
    
    default:
        Value ret;
        return ret;
        break;
    }
}

Value ExprInter::Visitor::visit(PrintExpr * node){
    
    // std::cout << "Getting kind\n";
    NodeKind arg_kind = node->argument->getKind();
    Value ret;

    switch (arg_kind)
    {
    case NodeKind::StringExpr:{
        StringExpr* arg = reinterpret_cast<StringExpr*>(node->argument);
        std::cout << arg->value;
        // std::cout << visit(reinterpret_cast<StringExpr*>(node->argument)).string_val;
        break;
    }
    default:
        break;
    }
    return ret;
}

Value ExprInter::Visitor::visit(PrintlnExpr * node){
    
    // std::cout << "Getting kind\n";
    NodeKind arg_kind = node->argument->getKind();
    Value arg;

    switch (arg_kind)
    {
    case NodeKind::StringExpr:{
        StringExpr* arg = reinterpret_cast<StringExpr*>(node->argument);
        std::cout << arg->value << std::endl;
        // std::cout << visit(reinterpret_cast<StringExpr*>(node->argument)).string_val;
        break;
    }
    default:
        return arg;
        break;
    }
}

Value ExprInter::Visitor::visit(StringExpr * node){

    // std::cout << node->value << std::endl;

    Value val(Type::String);
    val.string_val = node->value;

    // std::cout << val.string_val << std::endl;
    
    return val;
}