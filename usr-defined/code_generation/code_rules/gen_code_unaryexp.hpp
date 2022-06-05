//
// Created by lzy on 22-5-20.
//

#ifndef COMPILER_GEN_CODE_UNARYEXP_HPP
#define COMPILER_GEN_CODE_UNARYEXP_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// unary_expr->unary_operator cast_expr
class gen_code_unary_expr : public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override {
        auto p = std::dynamic_pointer_cast<CSym::unary_expr>(tree_node);

        UnaryOperatorType op = p->unary_operator;

        // TODO: not necessarily a rvalue
        auto val = getRValue(p->children[1], context);

        auto ret = val;
        switch (op) {
            case UnaryOperatorType::kMinus:
                ret=context.builder->CreateNeg(val);
                break;
            case UnaryOperatorType::kExclaim:
                ret=context.builder->CreateNot(val);
                break;
            default:
                throw std::logic_error("operator not supported!");
        }

        return ret;
    }
};

#endif
