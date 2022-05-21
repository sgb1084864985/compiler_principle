//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_EXPRSTMT1_HPP
#define COMPILER_GEN_CODE_EXPRSTMT1_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// expression_statement->;
class gen_code_exprstmt1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto &llvm_context = context.context;
        return llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*llvm_context));
    }
};

#endif
