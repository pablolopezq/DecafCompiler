#include "ExprInter.h"
#include <iostream>

void ExprInter::execute(){

    Visitor visitor(tbl, statements);

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

    case NodeKind::IdExpr:{
        // std::cout << "Visiting print expr...\n";
        return visit(reinterpret_cast<IdExpr *>(node));
        break;
    }

    case NodeKind::PrintlnExpr:
        // std::cout << "Visiting print expr...\n";
        return visit(reinterpret_cast<PrintlnExpr *>(node));
        break;
    
    case NodeKind::StringExpr:
        return visit(reinterpret_cast<StringExpr *>(node));
        break;

    case NodeKind::MethodCallExpr:
        // std::cout << "Visiting method call expr...\n";
        return visit(reinterpret_cast<MethodCallExpr *>(node));
        break;

    case NodeKind::MethodDeclExpr:
        // std::cout << "Visiting method decl expr...\n";
        return visit(reinterpret_cast<MethodDeclExpr *>(node));
        break;

    case NodeKind::FieldExpr:
        break;

    case NodeKind::VarAssignExpr:
        // std::cout << "Visiting var assign expr...\n";
        return visit(reinterpret_cast<VarAssignExpr *>(node));
        break;

    case NodeKind::IntExpr:
        return visit(reinterpret_cast<IntExpr *>(node));
        break;

    case NodeKind::CharExpr:
        return visit(reinterpret_cast<CharExpr *>(node));
        break;

    case NodeKind::BoolExpr:
        return visit(reinterpret_cast<BoolExpr *>(node));
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

    // case NodeKind::ShiftLeftExpr:
    //     return visit(reinterpret_cast<ShiftLeftExpr *>(node));
    //     break;

    // case NodeKind::ShiftRightExpr:
    //     return visit(reinterpret_cast<ShiftRightExpr *>(node));
    //     break;

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
        Value ret;
        return ret;
        break;
    }
    Value ret;
    return ret;
}

Value ExprInter::Visitor::visit(PrintExpr * node){
    
    // std::cout << "Getting kind\n";
    NodeKind arg_kind = node->argument->getKind();
    Value ret;

    switch (arg_kind){
    case NodeKind::StringExpr:{
        StringExpr* arg = reinterpret_cast<StringExpr*>(node->argument);
        std::string val = arg->value;
        val.pop_back();
        val.erase(0,1);

        std::cout << val;
        // std::cout << visit(reinterpret_cast<StringExpr*>(node->argument)).string_val;
        break;
    }
    case NodeKind::IntExpr:{
        IntExpr* arg = reinterpret_cast<IntExpr*>(node->argument);
        std::cout << arg->value;
        break;
    }
    case NodeKind::SumExpr:{
        SumExpr* arg = reinterpret_cast<SumExpr*>(node->argument);
        Value sum = visit(arg);
        std::cout << sum.num_val << std::endl;
        break;
    }
    case NodeKind::SubExpr:{
        SubExpr* arg = reinterpret_cast<SubExpr*>(node->argument);
        Value sub = visit(arg);
        std::cout << sub.num_val << std::endl;
        break;
    }
    case NodeKind::MultExpr:{
        MultExpr* arg = reinterpret_cast<MultExpr*>(node->argument);
        Value mult = visit(arg);
        std::cout << mult.num_val << std::endl;
        break;
    }
    case NodeKind::DivExpr:{
        DivExpr* arg = reinterpret_cast<DivExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << div.num_val << std::endl;
        break;
    }
    case NodeKind::ModExpr:{
        ModExpr* arg = reinterpret_cast<ModExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << div.num_val << std::endl;
        break;
    }
    case NodeKind::GreaterExpr:{
        GreaterExpr* arg = reinterpret_cast<GreaterExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::LessExpr:{
        LessExpr* arg = reinterpret_cast<LessExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::GreaterEqualExpr:{
        GreaterEqualExpr* arg = reinterpret_cast<GreaterEqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::LessEqualExpr:{
        LessEqualExpr* arg = reinterpret_cast<LessEqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::EqualExpr:{
        EqualExpr* arg = reinterpret_cast<EqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::NotEqualExpr:{
        NotEqualExpr* arg = reinterpret_cast<NotEqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::IdExpr:{
        IdExpr* arg = reinterpret_cast<IdExpr*>(node->argument);
        Value id = visit(arg);
        if(id.type == Type::Int)
            std::cout << id.num_val << std::endl;
        else if(id.type == Type::String)
            std::cout << id.string_val << std::endl;
        break;
    }
    default:
        break;
    }
    return ret;
}

Value ExprInter::Visitor::visit(PrintlnExpr * node){
    
    // std::cout << "Getting kind ln\n";
    NodeKind arg_kind = node->argument->getKind();
    Value arg;

    switch (arg_kind)
    {
    case NodeKind::StringExpr:{
        // std::cout << "Found string expr\n";
        StringExpr* arg = reinterpret_cast<StringExpr*>(node->argument);
        std::string val = arg->value;
        // val.pop_back();
        // val.erase(val[0]);

        std::cout << arg->value << std::endl;
        // std::cout << visit(reinterpret_cast<StringExpr*>(node->argument)).string_val;
        break;
    }
    case NodeKind::IntExpr:{
        // std::cout << "Found int expr\n";
        IntExpr* arg = reinterpret_cast<IntExpr*>(node->argument);
        std::cout << arg->value;
        break;
    }
    case NodeKind::SumExpr:{
        // std::cout << "Found sum expr\n";
        SumExpr* arg = reinterpret_cast<SumExpr*>(node->argument);
        Value sum = visit(arg);
        std::cout << sum.num_val << std::endl;
        break;
    }
    case NodeKind::SubExpr:{
        // std::cout << "Found sub expr\n";
        SubExpr* arg = reinterpret_cast<SubExpr*>(node->argument);
        Value sub = visit(arg);
        std::cout << sub.num_val << std::endl;
        break;
    }
    case NodeKind::MultExpr:{
        // std::cout << "Found mult expr\n";
        MultExpr* arg = reinterpret_cast<MultExpr*>(node->argument);
        Value mult = visit(arg);
        std::cout << mult.num_val << std::endl;
        break;
    }
    case NodeKind::DivExpr:{
        // std::cout << "Found div expr\n";
        DivExpr* arg = reinterpret_cast<DivExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << div.num_val << std::endl;
        break;
    }
    case NodeKind::ModExpr:{
        ModExpr* arg = reinterpret_cast<ModExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << div.num_val << std::endl;
        break;
    }
    case NodeKind::GreaterExpr:{
        GreaterExpr* arg = reinterpret_cast<GreaterExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::LessExpr:{
        LessExpr* arg = reinterpret_cast<LessExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::GreaterEqualExpr:{
        GreaterEqualExpr* arg = reinterpret_cast<GreaterEqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::LessEqualExpr:{
        LessEqualExpr* arg = reinterpret_cast<LessEqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::EqualExpr:{
        EqualExpr* arg = reinterpret_cast<EqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::NotEqualExpr:{
        NotEqualExpr* arg = reinterpret_cast<NotEqualExpr*>(node->argument);
        Value div = visit(arg);
        std::cout << std::boolalpha;
        std::cout << div.bool_val << std::endl;
        break;
    }
    case NodeKind::IdExpr:{
        // std::cout << "Found id expr\n";
        IdExpr* arg = reinterpret_cast<IdExpr*>(node->argument);
        Value id = visit(arg);
        if(id.type == Type::Int)
            std::cout << id.num_val << std::endl;
        else if(id.type == Type::String)
            std::cout << id.string_val << std::endl;
        break;
    }
    default:
        // std::cout << "Didnt find expr\n";
        return arg;
        break;
    }
    return arg;
}

Value ExprInter::Visitor::visit(IdExpr * node){

    SymbTbl::iterator it = tbl.find(node->name);
    Value val(it->second.type);
    val = it->second;
    // std::cout << "\t\t" << val.num_val << '\n';
    return val;
}

Value ExprInter::Visitor::visit(StringExpr * node){

    // std::cout << node->value << std::endl;

    Value val(Type::String);
    val.string_val = node->value;

    // std::cout << val.string_val << std::endl;
    
    return val;
}

Value ExprInter::Visitor::visit(MethodCallExpr * node){

    Value val;

    for(ASTNode* s : statements){
        NodeKind kind = s->getKind();
        if(kind == NodeKind::MethodCallExpr){
            MethodCallExpr * meth_call = reinterpret_cast<MethodCallExpr*>(s);
            if(meth_call->name == node->name){
                // std::cout << "Found method " << meth_call->name << std::endl;
                // for(ASTNode* s : meth_call->block){
                //     visit(s);
                // }
                break;
            }
        }
    }

    return val;
}

Value ExprInter::Visitor::visit(MethodDeclExpr * node){

    Value val;

    if(node->name == "main"){
        // std::cout << "Found main func of size ";        
        // std::cout << node->block.size() << std::endl;

        for(ASTNode* s : node->block){
            // std::cout << "Visiting node\n";
            visit(s);
        }
    }

    return val;
}

Value ExprInter::Visitor::visit(VarAssignExpr * node){

    Value val;

    SymbTbl::iterator it = tbl.find(node->name);
    // std::cout << "Assigning value to " << node->name << std::endl;
    Value expr = visit(node->expr);
    it->second = expr;
    // std::cout << it->second.num_val << "\n";

    return val;
}

Value ExprInter::Visitor::visit(IntExpr * node){
    
    Value val(Type::Int);
    val.num_val = node->value;
    return val;
}

Value ExprInter::Visitor::visit(CharExpr * node){

    Value val(Type::Char);
    val.char_val = node->value;
    return val;
}

Value ExprInter::Visitor::visit(BoolExpr * node){

    Value val(Type::Bool);
    val.bool_val = node->value;
    return val;
}

Value ExprInter::Visitor::visit(SubExpr * node){

    Value v1(Type::Int);
    Value v2(Type::Int);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    // std::cout << "Subbing " << v1.num_val << " and " << v2.num_val << std::endl;

    return v1 - v2;
}

Value ExprInter::Visitor::visit(SumExpr * node){

    Value v1(Type::Int);
    Value v2(Type::Int);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    // std::cout << "Adding " << v1.num_val << " and " << v2.num_val << std::endl;

    return v1 + v2;
}
Value ExprInter::Visitor::visit(MultExpr * node){

    Value v1(Type::Int);
    Value v2(Type::Int);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    // std::cout << "Multing " << v1.num_val << " and " << v2.num_val << std::endl;

    return v1 * v2;
}
Value ExprInter::Visitor::visit(DivExpr * node){

    Value v1(Type::Int);
    Value v2(Type::Int);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    // std::cout << "Diving " << v1.num_val << " and " << v2.num_val << std::endl;

    return v1 / v2;
}
Value ExprInter::Visitor::visit(ModExpr * node){

    Value v1(Type::Int);
    Value v2(Type::Int);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    // std::cout << "Moding " << v1.num_val << " and " << v2.num_val << std::endl;

    return v1 % v2;
}

Value ExprInter::Visitor::visit(GreaterEqualExpr * node){

    Value v1(Type::Bool);
    Value v2(Type::Bool);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    return v1 >= v2;
}
Value ExprInter::Visitor::visit(GreaterExpr * node){

    Value v1(Type::Bool);
    Value v2(Type::Bool);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    return v1 > v2;
}
Value ExprInter::Visitor::visit(LessEqualExpr * node){

    Value v1(Type::Bool);
    Value v2(Type::Bool);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    return v1 <= v2;
}
Value ExprInter::Visitor::visit(LessExpr * node){

    Value v1(Type::Bool);
    Value v2(Type::Bool);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    return v1 < v2;
}
Value ExprInter::Visitor::visit(EqualExpr * node){

    Value v1(Type::Bool);
    Value v2(Type::Bool);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    return v1 == v2;
}
Value ExprInter::Visitor::visit(NotEqualExpr * node){

    Value v1(Type::Bool);
    Value v2(Type::Bool);

    v1 = visit(node->expr1);
    v2 = visit(node->expr2);

    return v1 != v2;
}