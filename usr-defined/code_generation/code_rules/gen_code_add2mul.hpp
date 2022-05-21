//
// Created by lzy on 22-5-15.
//

#ifndef COMPILER_GEN_CODE_ADD2MUL_HPP
#define COMPILER_GEN_CODE_ADD2MUL_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

//add_expr->mul_expr
class gen_code_add2mul : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::add_expr>(tree_node);
        if (p->constant)
        {
            return genCodeForConstant(p->constant, context, tree_node);
        }
        
        auto ret = tree_node_genCode(p->children[0], context);
        if (p->implicit_cast_type)
        {
            return genCodeForCast(p->implicit_cast_type, context, ret);
        }
        return ret;
    }
};

#endif
