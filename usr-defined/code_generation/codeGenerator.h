//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CODEGENERATOR_H
#define COMPILER_CODEGENERATOR_H

#include "compiler.h"
#include "CSymbolTable.h"

// Interface, should be implemented
class codeGenerator {
public:
    virtual void
    genCode(ptrSymTable &symTable, std::shared_ptr<CSym::translation_unit> &AST_root, GlobalContext &context) =0;
};


#endif //COMPILER_CODEGENERATOR_H
