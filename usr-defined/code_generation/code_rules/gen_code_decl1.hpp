//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_DECL1_HPP
#define COMPILER_GEN_CODE_DECL1_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// declaration->declaration_specifiers ;
class gen_code_decl1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::declaration>(tree_node);
        tree_node_genCode(p->children[0], context);
        return nullptr;
    }
};

#endif
