//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_RULE_SUBEXPR_HPP
#define COMPILER_GEN_CODE_RULE_SUBEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// add_expr->add_expr - mul_expr
class gen_code_rule_subExpr : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        if(tree_node->type->isFPType()){
            return context.builder->CreateFSub(v1,v2,"f_mul");
        }
        else{
            return context.builder->CreateSub(v1,v2,"mul");
        }
    }
};

#endif
