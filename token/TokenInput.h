//
// Created by zlz on 2022/3/16.
//

#ifndef COMPILER_TOKENINPUT_H
#define COMPILER_TOKENINPUT_H

#include "compiler.h"
class TokenInput :public Iterator<SymbolValue>{
public:
    void unput(SymbolValue* val);
    SymbolValue& next() override;
    bool hasNext() override;
};

#endif //COMPILER_TOKENINPUT_H
