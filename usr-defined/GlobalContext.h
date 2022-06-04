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
    std::string file_out;
    bool error= false;
    explicit GlobalContext(std::ostream&out);
    [[nodiscard]] bool hasError()const{return error;}
    GlobalContext(std::ostream&out,std::string  file_out);
};


#endif //COMPILER_GLOBALCONTEXT_H
