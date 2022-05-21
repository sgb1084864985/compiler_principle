//
// Created by lzy on 22-5-19.
//

#ifndef COMPILER_GEN_CODE_EXPR2ASSIGN1_HPP
#define COMPILER_GEN_CODE_EXPR2ASSIGN1_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// expr->expr , assignment_expr
class gen_code_expr2assign1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
        tree_node_genCode(p->children[0], context);
        tree_node_genCode(p->children[2], context);
        return nullptr;
    }
};

#endif
