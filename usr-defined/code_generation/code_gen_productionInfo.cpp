//
// Created by zlz on 22-5-11.
//

#include "code_gen_productionInfo.h"

using llvm::Type;
Type *code_gen_productionInfo::getLlvmType(ptrType &type, code_gen_Context &context) {
    llvm::Type* basic_type= nullptr;
    switch (type->getTypeSpecifier()) {
        case CTS::INT:
            basic_type=Type::getIntNTy(*context.context,sizeof(int)*8);
            break;
        case CTS::FLOAT:
            basic_type=Type::getFloatTy(*context.context);
            break;
        case CTS::DOUBLE:
            basic_type=Type::getDoubleTy(*context.context);
            break;
        case CTS::LONGLONG:
            basic_type=Type::getIntNTy(*context.context,sizeof(long long)*8);
            break;
        case CTS::LONG:
            basic_type=Type::getIntNTy(*context.context,sizeof(long)*8);
            break;
        case CTS::SHORT:
            basic_type=Type::getIntNTy(*context.context,sizeof(short)*8);
            break;
//        case CTS::BOOL:
        case CTS::CHAR:
            basic_type=Type::getIntNTy(*context.context,sizeof(char)*8);
            break;
        case CTS::VOID:
            basic_type=Type::getVoidTy(*context.context);
            break;
        default:
            throw std::logic_error("type not supported yet");
    };
    for(int i=0;i<type->getPointerQuantifiers().size();i++){
        basic_type=basic_type->getPointerTo();
    }
    if(type->isArray()){
        auto& sizes=type->getArraySizes();
        for(unsigned int size : sizes){
            basic_type=llvm::ArrayType::get(basic_type,size);
        }
        return basic_type;
    }
    if(type->isFunction()){
        vector<Type*> paramTypes;
        for(auto& item:type->getParameterTypes()->param_list){
            paramTypes.push_back(getLlvmType(item,context));
        }
        bool va=type->getParameterTypes()->ellipse;
        return llvm::FunctionType::get(basic_type,paramTypes,va);
    }
    else{
        return basic_type;
    }
}

Value *
code_gen_productionInfo::genCodeForConstant(ptr_constant &constant, code_gen_Context &context, symbol_ptr &tree_node) {
    return constant->getLlvmValue(*context.context,*context.builder);
}

Value *code_gen_productionInfo::genCodeForCast(ptrType &type, code_gen_Context &context, Value *val,
                                               ptrType &src_type) {
    if(src_type->isIntegerType()){
        if(type->isFPType()){
            if(src_type->isSigned()){
                return context.builder->CreateSIToFP(val, getLlvmType(type,context));
            }
            else{
                return context.builder->CreateUIToFP(val, getLlvmType(type,context));
            }
        }
        if(type->isIntegerType()){
            return context.builder->CreateIntCast(val, getLlvmType(type,context),src_type->isSigned());
        }
    }
    else{
        if(src_type->isFPType()){
            if(type->isIntegerType()){
                if(type->isSigned()){
                    return context.builder->CreateFPToSI(val, getLlvmType(type,context));
                }
                else{
                    return context.builder->CreateFPToUI(val, getLlvmType(type,context));
                }
            }
            if(type->isFPType()){
                return context.builder->CreateFPCast(val, getLlvmType(type,context));
            }
        }
    }
    throw std::logic_error("not supported type conversion");
}
