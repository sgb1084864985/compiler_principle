//
// Created by zlz on 22-5-16.
//

#ifndef COMPILER_ATTRCONTEXT_H
#define COMPILER_ATTRCONTEXT_H

#include "GlobalContext.h"
#include "CNameSpace.h"

class AttrContext:Context {
public:
    GlobalContext& global;
    ptrCNamespace currentNameSpace;

    explicit AttrContext(GlobalContext& global):global(global){}
};


#endif //COMPILER_ATTRCONTEXT_H
