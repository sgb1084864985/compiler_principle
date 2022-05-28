//
// Created by zlz on 22-5-7.
//

#ifndef COMPILER_C_EXPR_HPP
#define COMPILER_C_EXPR_HPP

#include "AST.h"
#include <utility>

class C_type;
using ptrType=std::shared_ptr<C_type>;

namespace CSym{
    using C_expr=AST::NonTerminal;
}

#endif //COMPILER_C_EXPR_HPP
