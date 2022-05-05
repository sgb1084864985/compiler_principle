//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CSYMBOLTABLE_H
#define COMPILER_CSYMBOLTABLE_H

#include <vector>
#include "C_constant.h"
#include "CNameSpace.h"
#include "compiler.h"
#include "Csymbols.hpp"
#include <memory>

class CSymbolTable: public Context{
    using ptrSymTable=std::shared_ptr<CSymbolTable>;
public:
    std::vector<C_constant> constants;
    ptrNamespace rootNamespace;
public:
    static ptrSymTable genSymbolTable(symbol_ptr& AST_root,Context& context);
};

using ptrSymTable=std::shared_ptr<CSymbolTable>;

#endif //COMPILER_CSYMBOLTABLE_H
