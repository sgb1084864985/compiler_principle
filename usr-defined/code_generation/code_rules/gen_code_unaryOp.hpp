//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_LOGIC_UNARYOP_HPP
#define COMPILER_GEN_CODE_LOGIC_UNARYOP_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// unary_operator->-
class gen_code_neg : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::unary_operator>(tree_node);
        return llvm::ConstantInt::get(Type::getInt32Ty(context), 1);
    }
};

// unary_operator->!
class gen_code_neg : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::unary_operator>(tree_node);
        return llvm::ConstantInt::get(Type::getInt32Ty(context), 2);
    }
};

#endif