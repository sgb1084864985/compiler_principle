//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_LOGIC_OR2AND_HPP
#define COMPILER_GEN_CODE_LOGIC_OR2AND_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// logic_or_expr->logic_and_expr
class gen_code_logic_or2and : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::logical_or_expr>(tree_node);
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

//logic_or_expr->logic_or_expr || logic_and_expr
class gen_code_logic_or : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::logical_or_expr>(tree_node);
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

        auto ret=context.builder->CreateOr(v1,v2);
        if (p->implicit_cast_type)
        {
            return genCodeForCast(p->implicit_cast_type, context, ret);
        }
        return ret;
    }
};

#endif
