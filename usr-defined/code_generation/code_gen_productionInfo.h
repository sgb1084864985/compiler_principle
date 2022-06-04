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
using llvm::Type;
class code_gen_productionInfo : public ProductionInfo
{
public:
    virtual Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) {
        std::cout<<"In production:"<<std::endl;
        std::cout<<tree_node->production.left_hand_side<<" -> "<<tree_node->production.right_hand_side<<std::endl;
        throw std::logic_error("Method genCode not implemented");
    }

    static Value *genCode(ProductionInfo &info, code_gen_Context &context, symbol_ptr &tree_node)
    {
        auto &code_info = dynamic_cast<code_gen_productionInfo &>(info);
        return code_info.genCode(context, tree_node);
    }
    static Value *tree_node_genCode(symbol_ptr &tree_node, code_gen_Context &context)
    {
        auto item = std::dynamic_pointer_cast<AST::NonTerminal>(tree_node);
        return genCode(item->production.getGenCodeInfo(), context, tree_node);
    }


    static Type *getLlvmType(ptrType &type, code_gen_Context &context);
    static Value* genCodeForConstant(ptr_constant & constant, code_gen_Context& context,symbol_ptr& tree_node);
    static Value* genCodeForCast(ptrType& type, code_gen_Context& context,Value* val);
    static Value* getRValue(symbol_ptr &tree_node, code_gen_Context &context){
        auto item = std::dynamic_pointer_cast<AST::NonTerminal>(tree_node);
        auto val=genCode(item->production.getGenCodeInfo(), context, tree_node);
        if(tree_node->lValue){
            val=context.builder->CreateLoad(val);
        }
        return val;
    }
};

class code_genInChild:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::statement>(tree_node);
        return tree_node_genCode(p->children[0], context);
    }
};

// constant folding
class code_genInChildC:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::logical_or_expr>(tree_node);
        if (p->constant)
        {
            return genCodeForConstant(p->constant, context, tree_node);
        }

        auto ret = tree_node_genCode(p->children[0], context);
        if (p->implicit_cast_type)
        {
            return genCodeForCast(p->implicit_cast_type, context, ret);
        }
        return ret;
    }
};

class code_genNull:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        return nullptr;
    }
};

#endif // COMPILER_CODE_GEN_PRODUCTIONINFO_H
