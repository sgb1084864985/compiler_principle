//
// Created by zlz on 22-5-11.
//

#ifndef COMPILER_CODE_GEN_PRODUCTIONINFO_H
#define COMPILER_CODE_GEN_PRODUCTIONINFO_H

#include "ProductionInfo.h"
#include "code_gen_Context.h"
#include "compiler.h"
#include "C_constant.h"
#include "C_type.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

using llvm::Value;
class code_gen_productionInfo:public ProductionInfo{
public:
    virtual Value* genCode(code_gen_Context& context,symbol_ptr& tree_node)=0;

    static Value* genCode(ProductionInfo& info,code_gen_Context& context,symbol_ptr& tree_node){
        auto&code_info =dynamic_cast<code_gen_productionInfo&>(info);
        return code_info.genCode(context,tree_node);
    }
    static Value* tree_node_genCode(symbol_ptr& tree_node,code_gen_Context& context){
        auto item= std::dynamic_pointer_cast<AST::NonTerminal>(tree_node);
        return genCode(item->production.getGenCodeInfo(),context,tree_node);
    }

    static Value* genCodeForConstant(ptr_constant & constant, code_gen_Context& context,symbol_ptr& tree_node);
    static Value* genCodeForCast(ptrType type, code_gen_Context& context,Value* val);

};


#endif //COMPILER_CODE_GEN_PRODUCTIONINFO_H
