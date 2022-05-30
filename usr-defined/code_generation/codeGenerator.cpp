//
// Created by zlz on 22-5-5.
//

#include "codeGenerator.h"
#include "CNameSpace.h"

#include "llvm/IR/Function.h"
#include "code_gen_productionInfo.h"
#include "code_gen_Context.h"

using llvm::Function;
using llvm::BasicBlock;

void codeGenerator::genCodeGlobal(ptrSymTable &symTable, std::shared_ptr<CSym::translation_unit> &AST_root,
                                  code_gen_Context&context) {
    auto nameSpace= std::dynamic_pointer_cast<CNameSpace>(AST_root->owner);
    for(auto& name:nameSpace->getDeclarationList()){
        auto item=nameSpace->get(name);
        if(item->type->isFunction()){
            auto* functionType= static_cast<llvm::FunctionType*>(code_gen_productionInfo::getLlvmType(item->type));
            Function::Create(functionType,Function::ExternalLinkage,name,context.module.get());

            if(item->func){
            }
        }
    }
}

void codeGenerator::genCodeFuncDef(ptr_func &func, const string &func_name, code_gen_Context &context) {
    Function* llvmFun=context.module->getFunction(func_name);
    BasicBlock* entryBB=BasicBlock::Create(*context.context,"entry",llvmFun);
    context.builder->SetInsertPoint(entryBB);

}
