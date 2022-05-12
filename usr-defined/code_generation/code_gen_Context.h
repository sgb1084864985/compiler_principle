//
// Created by zlz on 22-5-12.
//

#ifndef COMPILER_CODE_GEN_CONTEXT_H
#define COMPILER_CODE_GEN_CONTEXT_H

#include <memory>

#include "compiler.h"
#include "GlobalContext.h"
#include "CSymbolTable.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

class code_gen_Context:Context{
public:
    // reference:
    // https://github.com/mukul-rathi/bolt/blob/master/src/llvm-backend/llvm_ir_codegen/ir_codegen_visitor.h
    GlobalContext& global;
    ptrSymTable symTable;

    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> module;

    explicit code_gen_Context(ptrSymTable & symbolTable,GlobalContext &global) : global(global),symTable(symbolTable){
        context = std::make_unique<llvm::LLVMContext>();
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
        module = std::make_unique<llvm::Module>("Module", *context);
    }
};


#endif //COMPILER_CODE_GEN_CONTEXT_H
