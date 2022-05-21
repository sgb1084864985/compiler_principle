//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_EXPRSTMT2_HPP
#define COMPILER_GEN_CODE_EXPRSTMT2_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// expression_statement->expr ;
class gen_code_exprstmt2 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::expression_statement>(tree_node);
        auto ret = tree_node_genCode(p->children[0], context);
        return ret;
    }
};

#endif
