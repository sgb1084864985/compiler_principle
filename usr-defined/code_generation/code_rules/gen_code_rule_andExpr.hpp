//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_RULE_ANDEXPR_HPP
#define COMPILER_GEN_CODE_RULE_ANDEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

class gen_code_rule_andExpr : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::and_expr>(tree_node);
        if (p->constant)
        {
            return genCodeForConstant(p->constant, context, tree_node);
        }
        auto v1 = tree_node_genCode(p->children[0], context);
        auto v2 = tree_node_genCode(p->children[1], context);
        auto ret = context.builder->CreateAnd(v1, v2, "and");
        // if (p->implicit_cast_type)
        // {
        //     return genCodeForCast(p->implicit_cast_type, context, ret);
        // }
        return ret;
    }
};

#endif 
