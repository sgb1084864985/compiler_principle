//
// Created by zlz on 22-6-2.
//

#ifndef COMPILER_GEN_CODE_PRIMARY_H
#define COMPILER_GEN_CODE_PRIMARY_H

#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

//primary_expr->id
class gen_code_primary_expr1:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::identifier_list>(tree_node);
        auto nameSpace= std::static_pointer_cast<CNameSpace>(tree_node->owner);
        auto node= std::static_pointer_cast<TerminalValue>(tree_node->children[0]);
        auto name_item=nameSpace->get(node->getText());
        if(name_item->type->isFunction()){
            return context.module->getFunction(node->getText());
        }
        auto val=context.env[name_item.get()];
        assert(val);
        return val;
    }
};

//primary_expr-> ( expr )
class gen_code_primary_expr2:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::identifier_list>(tree_node);

        return tree_node_genCode(tree_node->children[1],context);
    }
};

#endif //COMPILER_GEN_CODE_PRIMARY_H
