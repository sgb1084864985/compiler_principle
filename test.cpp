//
// Created by zlz on 22-4-26.
//
#include <iostream>
#include <memory>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"

int main(){
    auto context= std::make_unique<llvm::LLVMContext>();
    auto builder= std::make_unique<llvm::IRBuilder<>>(*context);
    auto module= std::make_unique<llvm::Module>("Module",*context);

    llvm::FunctionType *mainType =
            llvm::FunctionType::get(llvm::IntegerType::getInt32Ty(*context),
                                    std::vector<llvm::Type *>(), false /* isVarArgs */
            );
    llvm::Function *Main = llvm::Function::Create(
            mainType, llvm::Function::ExternalLinkage, "main", module.get());
    llvm::BasicBlock *mainBasicBlock =
            llvm::BasicBlock::Create(*context, "entry", Main);
    builder->SetInsertPoint(mainBasicBlock);


    llvm::APInt retVal(32 /* bitSize */, (uint32_t)0, true /* signed */);
    builder->CreateRet(llvm::ConstantInt::get(*(context), retVal));
    llvm::verifyFunction(*Main);

    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    module->setTargetTriple(TargetTriple);

    module->print(llvm::outs(), nullptr);
}