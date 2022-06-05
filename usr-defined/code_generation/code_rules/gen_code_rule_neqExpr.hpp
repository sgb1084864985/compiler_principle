//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_RULE_NEQEXPR_HPP
#define COMPILER_GEN_CODE_RULE_NEQEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// eq_expr->eq_expr != relational_expr
class gen_code_rule_neqExpr : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        return context.builder->CreateICmpNE(v1,v2,"ne");
    }
};

#endif
