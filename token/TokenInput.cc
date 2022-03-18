#include "compiler.h"

#include "TokenInput.h"

#include <utility>

#include "scanner.h"

class Token:public TerminalValue{
    int id;
    std::string text;
    const char* type;
public:
    Token(int id,std::string text,const char* type):
    id(id),text(std::move(text)),type(type){}

    int getID() override{
        return id;
    }
    const std::string& getText() override{
        return text;
    }

    const char* getType() override{
        return type;
    }

private:
};

void TokenInput::unput(SymbolValue *val) {
    unputCache.push_back(val);
}

SymbolValue& TokenInput::next() {
    static Token cache(0,"", nullptr);

    if(!unputCache.empty()){
        SymbolValue* ret=unputCache.back();
        unputCache.pop_back();
        return *ret;
    }

    cache=Token(SCANNER::getToken(),SCANNER::getTokenString(),SCANNER::getTokenType());
    do{
        SCANNER::nextToken();
        if(SCANNER::isEOF()){
            break;
        }
    }while (SCANNER::isWhite());
    return cache;
}

bool TokenInput::hasNext() {
    return !SCANNER::isEOF();
}

TokenInput::TokenInput() {
    SCANNER::startAnalyze();
    while (SCANNER::isWhite()){
        SCANNER::nextToken();
        if(SCANNER::isEOF()){
            break;
        }
    }
}