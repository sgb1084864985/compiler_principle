//
// Created by zlz on 22-4-25.
//

#ifndef COMPILER_TOKENACTIONS_H
#define COMPILER_TOKENACTIONS_H


#include <utility>

#include "compiler.h"
#include "Scanner2.h"

class TokenContext{

};

class TokenAction{
public:
    int id;
    std::string name;
    std::string regx;

    using func = function<symbol_ptr (TokenAction& self,const char* text, Scanner2&scan, TokenContext& con)>;

    func action;

public:
    TokenAction(std::string name,std::string regx,func action,int id=0):
    name(std::move(name)),regx(std::move(regx)),action(std::move(action)),id(id){}

    symbol_ptr operator()(const char* text, Scanner2&scan, TokenContext& con){
        return action(*this,text,scan,con);
    }

    void setID(int i){
        this->id=i;
    }
};

// interface
class TokenActions{
public:
    virtual vector<TokenAction>& getTokenActions()=0;
    virtual void printTokens()=0;
};

#endif //COMPILER_TOKENACTIONS_H
