//
// Created by zlz on 22-5-7.
//

#ifndef COMPILER_GLOBALCONTEXT_H
#define COMPILER_GLOBALCONTEXT_H

#include "compiler.h"
#include <ostream>

class GlobalContext: Context{
public:
    std::ostream &error_out;
    explicit GlobalContext(std::ostream&out);
};


#endif //COMPILER_GLOBALCONTEXT_H