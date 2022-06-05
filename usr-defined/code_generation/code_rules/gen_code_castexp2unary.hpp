//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_CASTEXP2UNARY_HPP
#define COMPILER_GEN_CODE_CASTEXP2UNARY_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// cast_expr->unary_expr
class gen_code_castexp2unary : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::cast_expr>(tree_node);
        if (p->constant)
        {
            return genCodeForConstant(p->constant, context, tree_node);
        }

        auto ret = tree_node_genCode(p->children[0], context);
        if (p->implicit_cast_type)
        {
            return genCodeForCast(p->implicit_cast_type, context, ret, <#initializer#>);
        }
        return ret;
    }
};

#endif