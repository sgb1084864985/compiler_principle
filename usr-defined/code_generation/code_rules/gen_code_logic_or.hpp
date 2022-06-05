//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_LOGIC_OR_HPP
#define COMPILER_GEN_CODE_LOGIC_OR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"


//logic_or_expr->logic_or_expr || logic_and_expr
class gen_code_logic_or : public gen_code_BinaryExpr
{
    Value * operation(code_gen_Context &context, symbol_ptr &tree_node, symbol_ptr &op1, symbol_ptr &op2, Value *v1, Value *v2) override{
        return context.builder->CreateOr(v1,v2,"or");
    }
};

#endif
