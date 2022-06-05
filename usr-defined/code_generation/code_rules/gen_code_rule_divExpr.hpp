//
// Created by lzy on 22-5-12.
//

#ifndef COMPILER_GEN_CODE_RULE_DIVEXPR_HPP
#define COMPILER_GEN_CODE_RULE_DIVEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// mul_expr->mul_expr / unary_expr
class gen_code_rule_divExpr : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        if(tree_node->type->isFPType()){
            return context.builder->CreateFDiv(v1,v2,"f_div");
        }
        else{
            if(tree_node->type->isSigned()){
                return context.builder->CreateSDiv(v1,v2,"div");
            }
            else{
                return context.builder->CreateUDiv(v1,v2,"div");
            }
        }
    }
};

#endif
