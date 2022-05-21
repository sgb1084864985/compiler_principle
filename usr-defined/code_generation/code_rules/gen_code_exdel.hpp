//
// Created by lzy on 22-5-20.
//

#ifndef COMPILER_GEN_CODE_EXDEL_HPP
#define COMPILER_GEN_CODE_EXDEL_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// external_declaration->function_definition
class gen_code_trans_unit1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::external_declaration>(tree_node);
        tree_node_genCode(p->children[0], context);
        return nullptr;
    }
};

// external_declaration->declaration
class gen_code_trans_unit2 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::external_declaration>(tree_node);

        tree_node_genCode(p->children[0], context);
        return nullptr;
    }
};

#endif