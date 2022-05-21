//
// Created by lzy on 22-5-20.
//

#ifndef COMPILER_GEN_CODE_TRANS_UNIT_HPP
#define COMPILER_GEN_CODE_TRANS_UNIT_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// translation_unit->external_declaration
class gen_code_trans_unit1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::translation_unit>(tree_node);
        tree_node_genCode(p->children[0], context);
        return nullptr;
    }
};

// translation_unit->translation_unit external_declaration
class gen_code_trans_unit2 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::translation_unit>(tree_node);

        tree_node_genCode(p->children[0], context);
        tree_node_genCode(p->children[1], context);
        return nullptr;
    }
};

#endif