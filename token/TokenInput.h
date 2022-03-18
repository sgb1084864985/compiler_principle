//
// Created by zlz on 2022/3/16.
//

#ifndef COMPILER_TOKENINPUT_H
#define COMPILER_TOKENINPUT_H

#include "compiler.h"
#include "Token.hpp"
#include <vector>
#include <stdexcept>
class TokenInput :public Iterator<symbol_ptr>{
public:
    void unget(const symbol_ptr& val);
    symbol_ptr next() override;
    symbol_ptr top();
    bool hasNext() override;
    TokenInput();

private:
    std::vector<symbol_ptr> unputCache;
    symbol_ptr cache;

private:
    void _next();

    void checkNullptr(SymbolValue* ptr){
#ifdef DEBUG
        if(ptr==nullptr){
            throw std::logic_error("Symbol value should not be null!")
        }
#endif
    }
};

#endif //COMPILER_TOKENINPUT_H
