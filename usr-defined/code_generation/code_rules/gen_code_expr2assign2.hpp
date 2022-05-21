//
// Created by lzy on 22-5-19.
//

#ifndef COMPILER_GEN_CODE_EXPR2ASSIGN2_HPP
#define COMPILER_GEN_CODE_EXPR2ASSIGN2_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// expr->assignment_expr
class gen_code_expr2assign2 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
        auto ret = tree_node_genCode(p->children[0], context);
        return ret;
    }
};

#endif
