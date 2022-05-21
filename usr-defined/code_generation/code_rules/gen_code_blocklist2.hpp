//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_BLOCKLIST2_HPP
#define COMPILER_GEN_CODE_BLOCKLIST2_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// block_item_list->block_item_list block_item
class gen_code_blocklist2 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::block_item_list>(tree_node);
        auto v1 = tree_node_genCode(p->children[0], context);
        auto v2 = tree_node_genCode(p->children[1], context);

        auto &llvm_context = context.context; 
        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*llvm_context));

    }
};

#endif
