#include "compiler.h"

#include "TokenInput.h"


#include "scanner.h"

#include "Token.hpp"

void TokenInput::unget(const symbol_ptr& val) {
    unputCache.push_back(val);
}

symbol_ptr TokenInput::next() { // pop top, return new top
    _next();
    return top();
}

void TokenInput::_next() {
    if(!unputCache.empty()){
        unputCache.pop_back();
    }
    else{
        do{
            SCANNER::nextToken();
        }while (SCANNER::isDELIMITER(SCANNER::getToken()));
        cache=std::make_shared<Token>(SCANNER::getToken(),SCANNER::getTokenString(),SCANNER::getTokenType());
    }
}

symbol_ptr TokenInput::top() {
    if(!unputCache.empty()){
        return unputCache.back();
    }
    return cache;
}

bool TokenInput::hasNext() {
    return !SCANNER::isEOF();
}

TokenInput::TokenInput(){
    SCANNER::startAnalyze();

    while (SCANNER::isDELIMITER(SCANNER::getToken())){
        SCANNER::nextToken();
    }
    cache=std::make_shared<Token>(SCANNER::getToken(),SCANNER::getTokenString(),SCANNER::getTokenType());

}