//
// Created by zlz on 22-5-5.
//

#include "codeGenerator.h"
#include "CNameSpace.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include "code_gen_productionInfo.h"
#include "code_gen_Context.h"

using llvm::Function;
using llvm::BasicBlock;

void codeGenerator::genCodeGlobal(ptrSymTable &symTable, std::shared_ptr<CSym::translation_unit> &AST_root,
                                  code_gen_Context&context) {
    auto nameSpace= std::static_pointer_cast<CNameSpace>(AST_root->owner);
    for(auto& name:nameSpace->getDeclarationList()){
        auto item=nameSpace->get(name);
        if(item->type->isFunction()){
            auto* functionType= static_cast<llvm::FunctionType*>(code_gen_productionInfo::getLlvmType(item->type,
                                                                                                      context));
            Function::Create(functionType,Function::ExternalLinkage,name,context.module.get());

            if(item->func->idDefined()){
                genCodeFuncDef(item->func,name,context);
            }
        }
        else{
            auto type=code_gen_productionInfo::getLlvmType(item->type,context);
            context.module->getOrInsertGlobal(name,type);
            auto var=context.module->getGlobalVariable(name);
            var->setInitializer(llvm::Constant::getNullValue(type));
            context.env[item.get()]=var;
        }
    }
}

void codeGenerator::genCodeFuncDef(ptr_func &func, const string &func_name, code_gen_Context &context) {
    Function* llvmFun=context.module->getFunction(func_name);
    context.defined_functions.push_back(llvmFun);
    BasicBlock* entryBB=BasicBlock::Create(*context.context,"entry",llvmFun);
    context.builder->SetInsertPoint(entryBB);

    auto param_space=std::static_pointer_cast<CNameSpace>(func->func_namespace)->getParentSpace();
    for(auto& param: llvmFun->args()){
        auto param_no=param.getArgNo();
        const string&param_name=param_space->getDeclarationList()[param_no];
        llvm::Type* param_type=llvmFun->getFunctionType()->getParamType(param_no);
        auto ptr=context.builder->CreateAlloca(param_type, nullptr,llvm::Twine(param_name));
        context.env[param_space->getLocal(param_name).get()]=ptr;
        context.builder->CreateStore(&param,ptr);
    }

    auto ret_value= code_gen_productionInfo::tree_node_genCode(func->body,context);
    if (llvmFun->getReturnType()->isVoidTy()) {
        context.builder->CreateRetVoid();
    } else {
        context.builder->CreateRet(ret_value);
    }
    if(llvm::verifyFunction(*llvmFun,&llvm::outs())){
        std::cout<<"\ncode:\n"<<std::endl;
        context.module->print(llvm::outs(), nullptr);
        throw std::logic_error("function define error");
    }
}

void codeGenerator::genCode(ptrSymTable &symTable, std::shared_ptr<CSym::translation_unit> &AST_root,
                            GlobalContext &context) {
    code_gen_Context context1(symTable,context);
    genCodeGlobal(symTable,AST_root,context1);

//    optimize(context1);

    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    context1.module->setTargetTriple(TargetTriple);

    if(context.file_out.empty()){
        context1.module->print(llvm::outs(), nullptr);
    }
    else{
        std::error_code ec;
        llvm::raw_fd_ostream file_out(context.file_out,ec);
        context1.module->print(file_out, nullptr);
        file_out.close();
    }
}

void codeGenerator::optimize(code_gen_Context &context) {
    auto pass_manager=std::make_unique<llvm::legacy::FunctionPassManager>(context.module.get());
    pass_manager->add(llvm::createPromoteMemoryToRegisterPass());
    pass_manager->add(llvm::createInstructionCombiningPass());
    pass_manager->add(llvm::createReassociatePass());
    pass_manager->add(llvm::createGVNPass());
    pass_manager->add(llvm::createCFGSimplificationPass());
    pass_manager->doInitialization();

    for(auto func:context.defined_functions){
        pass_manager->run(*func);
    }
}
