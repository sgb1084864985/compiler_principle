//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CSYMBOLTABLE_H
#define COMPILER_CSYMBOLTABLE_H

#include "C_constant.h"
#include "CNameSpace.h"
#include "compiler.h"
#include "Csymbols.hpp"
#include "GlobalContext.h"
#include <memory>
#include <vector>

class CSymbolTable: public Context{
    using ptrSymTable=std::shared_ptr<CSymbolTable>;
public:
    // list of all constants
    std::vector<ptr_constant> constants;
    ptrCNamespace rootNamespace;
public:
    static ptrSymTable genSymbolTable(symbol_ptr& AST_root, GlobalContext &context);
};

using ptrSymTable=std::shared_ptr<CSymbolTable>;

#endif //COMPILER_CSYMBOLTABLE_H
