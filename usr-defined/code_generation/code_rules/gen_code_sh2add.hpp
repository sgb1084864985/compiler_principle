//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_SH2ADD_HPP
#define COMPILER_GEN_CODE_SH2ADD_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// shift_expr->add_expr
class gen_code_sh2add : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::shift_expr>(tree_node);
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
