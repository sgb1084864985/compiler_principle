//
// Created by zlz on 22-5-17.
//

#ifndef COMPILER_GEN_CODE_IF_STATEMENT_HPP
#define COMPILER_GEN_CODE_IF_STATEMENT_HPP

#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// selection_statement->if ( expr ) statement else statement
class gen_code_rule_if1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::selection_statement>(tree_node);

        auto condition_node = tree_node_genCode(p->children[2], context);
        auto &builder = context.builder;
        auto &llvm_context = context.context;

        llvm::Function *parentFunction = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *thenBB =
            llvm::BasicBlock::Create(*llvm_context, "then", parentFunction);
        llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(*llvm_context, "else");
        llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(*llvm_context, "ifcont");

        builder->CreateCondBr(condition_node, thenBB, elseBB);

        builder->SetInsertPoint(thenBB);

        // handle then part statement
        tree_node_genCode(p->children[4], context);

        builder->CreateBr(mergeBB); // branch

        parentFunction->getBasicBlockList().push_back(elseBB);
        builder->SetInsertPoint(elseBB);

        // handle else part statement
        tree_node_genCode(p->children[6], context);

        builder->CreateBr(mergeBB);

        parentFunction->getBasicBlockList().push_back(mergeBB);
        builder->SetInsertPoint(mergeBB);

        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*llvm_context));
    }
};

// selection_statement->if ( expr ) statement
class gen_code_rule_if1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::selection_statement>(tree_node);

        auto condition_node = tree_node_genCode(p->children[2], context);
        auto &builder = context.builder;
        auto &llvm_context = context.context;

        llvm::Function *parentFunction = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *thenBB =
            llvm::BasicBlock::Create(*llvm_context, "then", parentFunction);
        llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(*llvm_context, "else");
        llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(*llvm_context, "ifcont");
        builder->CreateCondBr(condition_node, thenBB, elseBB);

        builder->SetInsertPoint(thenBB);
        // handle then part statement
        tree_node_genCode(p->children[4], context);

        builder->CreateBr(mergeBB); // branch

        parentFunction->getBasicBlockList().push_back(mergeBB);
        builder->SetInsertPoint(mergeBB);

        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*llvm_context));
    }
};
#endif // COMPILER_GEN_CODE_IF_STATEMENT_HPP
