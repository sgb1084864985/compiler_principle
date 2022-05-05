//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CODEGENERATOR_H
#define COMPILER_CODEGENERATOR_H

#include "compiler.h"
#include "CSymbolTable.h"
class codeGenerator {
public:
    void genCode(ptrSymTable& symTable,symbol_ptr& AST_root);
};


#endif //COMPILER_CODEGENERATOR_H
