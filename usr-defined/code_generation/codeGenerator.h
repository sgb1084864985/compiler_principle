//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CODEGENERATOR_H
#define COMPILER_CODEGENERATOR_H

#include "compiler.h"
#include "CSymbolTable.h"
#include "code_gen_Context.h"
#include "unordered_map"

// Interface, should be implemented
class codeGenerator {
public:
    static void
    genCode(ptrSymTable &symTable, std::shared_ptr<CSym::translation_unit> &AST_root, GlobalContext &context);

    static void genCodeGlobal(ptrSymTable &symTable, std::shared_ptr<CSym::translation_unit> &AST_root, code_gen_Context&context);
    static void genCodeFuncDef(ptr_func &func, const string &func_name, code_gen_Context &context);
    static void optimize(code_gen_Context&context);
private:
};


#endif //COMPILER_CODEGENERATOR_H
