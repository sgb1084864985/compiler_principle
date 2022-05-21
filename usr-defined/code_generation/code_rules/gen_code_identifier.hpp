//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_IDENTIFIER_HPP
#define COMPILER_GEN_CODE_IDENTIFIER_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// identifier_list->id
// identifier_list->identifier_list , id


// identifier_list->id
class gen_code_identifier1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::identifier_list>(tree_node);
        auto id = tree_node_genCode(p->children[0], context);
        context.builder->CreateLoad(id);
        return id;
    }
};

// identifier_list->identifier_list , id
class gen_code_identifier2 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::identifier_list>(tree_node);
        tree_node_genCode(p->children[0], context);
        auto id = tree_node_genCode(p->children[0], context);
        context.builder->CreateLoad(id);
        return id;
    }
};

#endif
