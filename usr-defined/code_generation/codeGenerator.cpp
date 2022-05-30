//
// Created by zlz on 22-5-5.
//

#include "codeGenerator.h"
#include "CNameSpace.h"

void codeGenerator::genCodeGlobal(ptrSymTable &symTable, std::shared_ptr<CSym::translation_unit> &AST_root,
                                  GlobalContext &context) {
    auto nameSpace= std::dynamic_pointer_cast<CNameSpace>(AST_root->owner);
    for(auto& name:nameSpace->getDeclarationList()){
        auto& item=nameSpace->get(name);
    }
}
