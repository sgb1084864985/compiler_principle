//
// Created by zlz on 22-4-26.
//
#include <iostream>
#include <memory>

#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"

int main(){

    auto context = std::make_unique<llvm::LLVMContext>();
    std::unique_ptr<llvm::IRBuilder<>> builder;
    auto p=builder->CreateLoad(nullptr, nullptr);
    return 0;
}