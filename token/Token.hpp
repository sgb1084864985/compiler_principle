#ifndef _TOKEN_H_
#define _TOKEN_H_
#include "compiler.h"

class Token:public TerminalValue{
    std::string text;
    const char* type;
public:
    Token(int id,std::string text,const char* type):
            text(std::move(text)),type(type){
        setID(id);
    }

    const std::string& getText() override{
        return text;
    }

    const char* getType() override{
        return type;
    }

private:
};

#endif