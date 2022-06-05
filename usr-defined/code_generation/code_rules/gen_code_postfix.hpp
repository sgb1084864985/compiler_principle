//
// Created by zlz on 22-6-2.
//

#ifndef COMPILER_GEN_CODE_POSTFIX_HPP
#define COMPILER_GEN_CODE_POSTFIX_HPP

#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

//postfix_expr->primary_expr
//class gen_code_postfix_expr1:public code_gen_productionInfo{
//    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
//    {
//        auto p = std::dynamic_pointer_cast<CSym::postfix_expr>(tree_node);
//
//        auto val = tree_node_genCode(p->children[0], context);
//        return val;
//    }
//};

//postfix_expr->postfix_expr ( )
class gen_code_postfix_expr2:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::identifier_list>(tree_node);
        auto val = static_cast<llvm::Function*>(tree_node_genCode(p->children[0], context));
        return context.builder->CreateCall(val);
    }
};

//postfix_expr->postfix_expr ( argument_expression_list )
class gen_code_postfix_expr3:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::identifier_list>(tree_node);
        auto val=tree_node_genCode(p->children[0], context);
        auto func = static_cast<llvm::Function*>(val);
        vector<llvm::Value*> args;
        visitArgs(args,context,tree_node->children[2]);
        return context.builder->CreateCall(func,args);
    }
    void visitArgs(vector<llvm::Value*>& args,code_gen_Context &context, symbol_ptr &tree_node){
        if(tree_node->children.size()==1){
            auto expr=tree_node->children[0];
            auto val=getRValue(expr,context);
            args.push_back(val);
        }
        else if(tree_node->children.size()==3){
            visitArgs(args,context,tree_node->children[0]);
            auto expr=tree_node->children[2];
            auto val=getRValue(expr,context);
            args.push_back(val);
        }
    }
};


//postfix_expr->postfix_expr [ expr ]
class gen_code_postfix_array:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::identifier_list>(tree_node);
        auto array= tree_node_genCode(p->children[0],context);
        auto index= getRValue(p->children[2],context);
        if(p->children[0]->type->isArray()){
            return context.builder->CreateGEP(array, {llvm::ConstantInt::getNullValue(Type::getInt32Ty(*context.context)),index});
        }
        else{
            return context.builder->CreateGEP(array, index);
        }
    }
};

#endif //COMPILER_GEN_CODE_POSTFIX_HPP
