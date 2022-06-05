//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_RULE_MULEXPR_HPP
#define COMPILER_GEN_CODE_RULE_MULEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// mul_expr->mul_expr * unary_expr
class gen_code_rule_mulExpr : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        if(tree_node->type->isFPType()){
            return context.builder->CreateFMul(v1,v2,"f_mul");
        }
        else{
            return context.builder->CreateMul(v1,v2,"mul");
        }
    }
};

#endif
