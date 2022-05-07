//
// Created by zlz on 22-5-7.
//

#ifndef COMPILER_C_EXPR_HPP
#define COMPILER_C_EXPR_HPP

#include "AST.h"
#include "C_constant.h"
#include <utility>

namespace CSym{
    class C_expr: public AST::NonTerminal {
    public:
        // pointer empty if not constant
        ptr_constant constant;
        C_expr(Production &production, std::string label): NonTerminal(production, std::move(label)) {

        }
    };

}

#endif //COMPILER_C_EXPR_HPP
