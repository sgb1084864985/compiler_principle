//
// Created by zlz on 22-5-17.
//

#ifndef COMPILER_GEN_CODE_LOOP_STATEMENT_HPP
#define COMPILER_GEN_CODE_LOOP_STATEMENT_HPP

#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

//iteration_statement->while ( expr ) statement
class gen_code_rule_while1:public code_gen_productionInfo{
    Value * genCode(code_gen_Context &context, symbol_ptr &tree_node) override{
        auto p= std::dynamic_pointer_cast<CSym::iteration_statement>(tree_node);

        auto condition_node= tree_node_genCode(p->children[2],context);
        auto& builder=context.builder;
        auto& llvm_context=context.context;

        llvm::Function *parentFunction = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *condBB = llvm::BasicBlock::Create(*llvm_context, "cond");
        llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(*llvm_context, "loop");
        llvm::BasicBlock *loopEndBB = llvm::BasicBlock::Create(*llvm_context, "loop_end");

        parentFunction->getBasicBlockList().push_back(condBB);
        builder->SetInsertPoint(condBB);

        builder->CreateCondBr(condition_node, loopBB, loopEndBB);

        parentFunction->getBasicBlockList().push_back(loopBB);
        builder->SetInsertPoint(loopBB);

        // handle loop part statement
        tree_node_genCode(p->children[4],context);

        // jump to condition block
        builder->CreateBr(condBB);

        parentFunction->getBasicBlockList().push_back(loopEndBB);
        builder->SetInsertPoint(loopEndBB);

        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*llvm_context));
    }
};

#endif //COMPILER_GEN_CODE_LOOP_STATEMENT_HPP