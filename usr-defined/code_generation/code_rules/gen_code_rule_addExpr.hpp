//
// Created by zlz on 22-5-12.
//

#ifndef COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
#define COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
#include "code_gen_productionInfo.h"
#include "gen_code_rule_BinaryOpExpr.h"
#include "Csymbols.hpp"

//add_expr->add_expr + mul_expr
class gen_code_rule_addExpr : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        if(tree_node->type->isFPType()){
            return context.builder->CreateFAdd(v1,v2,"f_add");
        }
        else{
            return context.builder->CreateAdd(v1,v2,"add");
        }
    }
};

#endif // COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
