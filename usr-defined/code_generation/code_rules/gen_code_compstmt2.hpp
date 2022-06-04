//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_COMPSTMT2_HPP
#define COMPILER_GEN_CODE_COMPSTMT2_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// compound_statement->{ block_item_list }
class gen_code_compstmt2 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto nameSpace=std::static_pointer_cast<CNameSpace>(tree_node->owner);
        for(auto& name:nameSpace->getDeclarationList()){
            auto item=nameSpace->get(name);
            if(item->alloc_order!=CNameSpace::name_item::NO_ALLOC){
                auto var=context.builder->CreateAlloca(getLlvmType(item->type, context), nullptr, name);
                context.env[item.get()]=var;
            }
        }

        auto p = std::dynamic_pointer_cast<CSym::compound_statement>(tree_node);
        tree_node_genCode(p->children[1], context);

        auto &llvm_context = context.context; 
        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*llvm_context));
    }
};

#endif
