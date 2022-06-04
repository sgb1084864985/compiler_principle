//
// Created by zlz on 22-5-5.
//

#include "CSymbolTable.h"
#include "GlobalContext.h"
#include "attr_rule.hpp"

CSymbolTable::ptrSymTable CSymbolTable::genSymbolTable(symbol_ptr &AST_root, GlobalContext &context) {
    auto table= std::make_shared<CSymbolTable>();
    table->rootNamespace= std::make_shared<CNameSpace>(AST_root);
    AttrContext context1(context);
    context1.currentNameSpace=table->rootNamespace;
    AST_root->getAttr().FillAttributes(context1,AST_root);
    if(context.error || AST_root->error){
        throw std::logic_error("error occurred");
    }
    return table;
}
