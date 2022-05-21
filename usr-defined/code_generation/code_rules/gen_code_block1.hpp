//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_BLOCK1_HPP
#define COMPILER_GEN_CODE_BLOCK1_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// block_item->statement
class gen_code_block1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::block_item>(tree_node);
        tree_node_genCode(p->children[0], context);
        
        auto &llvm_context = context.context; 
        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*llvm_context));
    }
};

#endif
