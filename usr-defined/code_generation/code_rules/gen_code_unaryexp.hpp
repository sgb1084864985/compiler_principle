//
// Created by lzy on 22-5-20.
//

#ifndef COMPILER_GEN_CODE_UNARYEXP_HPP
#define COMPILER_GEN_CODE_UNARYEXP_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// unary_expr->unary_operator cast_expr
class gen_code_unaryexpr : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::unary_expr>(tree_node);

        auto op = tree_node_genCode(p->children[0], context);
        int unaryOp = op->getSExtValue();
        auto val = tree_node_genCode(p->children[1], context);
        if (op == 1)
        {
            auto ret = context.builder->CreateNeg(val, "neg");
            if (p->implicit_cast_type)
            {
                return genCodeForCast(p->implicit_cast_type, context, ret);
            }
        }
        
        else if (op == 2)
        {
            auto ret = context.builder->CreateNot(val, "not");
            if (p->implicit_cast_type)
            {
                return genCodeForCast(p->implicit_cast_type, context, ret);
            }
        }
    }
};

#endif
