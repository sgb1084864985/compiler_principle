//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_RULE_SHLEXPR_HPP
#define COMPILER_GEN_CODE_RULE_SHLEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// shift_expr->shift_expr << add_expr
class gen_code_rule_shlExpr : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        return context.builder->CreateShl(v1,v2,"shl");
    }
};

#endif
