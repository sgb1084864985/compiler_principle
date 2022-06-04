//
// Created by lzy on 22-5-13.
//

#ifndef COMPILER_GEN_CODE_RULE_GTEXPR_HPP
#define COMPILER_GEN_CODE_RULE_GTEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// relational_expr->relational_expr > shift_expr
class gen_code_rule_gtExpr : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::relational_expr>(tree_node);
        if (p->constant)
        {
            return genCodeForConstant(p->constant, context, tree_node);
        }
        auto v1 = tree_node_genCode(p->children[0], context);
        auto v2 = tree_node_genCode(p->children[2], context);
        if(p->children[0]->lValue){
            v1=context.builder->CreateLoad(v1);
        }
        if(p->children[2]->lValue){
            v2=context.builder->CreateLoad(v2);
        }
        auto ret = context.builder->CreateICmpSGT(v1, v2, "gt");
        if (p->implicit_cast_type)
        {
            return genCodeForCast(p->implicit_cast_type, context, ret);
        }
        return ret;
    }
};

#endif
