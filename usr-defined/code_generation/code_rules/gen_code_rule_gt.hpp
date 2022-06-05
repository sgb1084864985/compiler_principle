//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_RULE_GTEXPR_HPP
#define COMPILER_GEN_CODE_RULE_GTEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// relational_expr->relational_expr > shift_expr
class gen_code_rule_gtExpr : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        if(tree_node->type->isSigned()){
            return context.builder->CreateICmpSGT(v1,v2,"gt");
        }
        else{
            return context.builder->CreateICmpUGT(v1,v2,"gt");
        }
    }
};

#endif
