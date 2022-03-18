#ifndef _TOKEN_H_
#define _TOKEN_H_
#include "compiler.h"

class Token:public TerminalValue{
    const std::string text;
    const char* type;
public:
    Token(int id,const char* text,const char* type):
            text(text),type(type){
        setID(id);
    }

    const char* getText() override{
        return text.c_str();
    }

    const char* getType() override{
        return type;
    }

private:
};

#endif