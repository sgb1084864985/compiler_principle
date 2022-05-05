// compiler.hpp
#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <functional>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <cassert>
#include "ProductionInfo.h"

#ifdef DEBUG
#define DEBUG_TEST(x) do{x}while(0);
#define ASSERT(x) do{assert(x);}while(0);
#else
#define DEBUG_TEST(x)
#define ASSERT(x)
#endif

using std::vector;
using std::function;

template<class T>
class Iterator{
public:
    virtual T next()=0;
    virtual bool hasNext()=0;
};

//////////////////////////////
// Class: Context
// is a tag interface.
// records the global information during compilation.
// should be implemented.
//////////////////////////////
class Context{
public:
    // no use but to make the class virtual.
    virtual void describe(){}
};

//////////////////////////////
// represent symbols in CFG.
// should only have two subclasses: non-terminal terminal
//////////////////////////////
class SymbolValue{
public:
    [[nodiscard]] int getID() const{
        return id;
    }
    void setID(int i){
        this->id=i;
    }
    virtual void print(std::ostream &out_port)=0;
    virtual bool hasError(){return false;}
private:
    int id=-1;

};

//////////////////////////////
// represent terminals in CFG
//////////////////////////////
class TerminalValue:public SymbolValue{
public:
    ////example/////
    // "identifier"
    // "number"
    // "Float"
    ////////////////
    virtual const char* getType()=0;

    ////////////example/////////////
    // like "i","j","1.0","if"
    ////////////////////////////////
    virtual const char * getText()=0;

    void print(std::ostream &out_port) override{
        out_port<<getText();
    }
};

using symbol_ptr=std::shared_ptr<SymbolValue>;
using symbol_iterator=Iterator<symbol_ptr>;


// represents one cfg rule.
class Production{
    using handler=function<symbol_ptr (Production& self,symbol_iterator &,Context&)>;

private:
    handler action;
    ProductionInfo* attributes;
public:
    const char* left_hand_side;
    const char* right_hand_side;

    void setAttrs(ProductionInfo& attr){
        attributes=&attr;
    }
    const ProductionInfo& getAttrs(){
        return *attributes;
    }

    symbol_ptr operator()(symbol_iterator &it,Context&con){
        return action(*this,it,con);
    }

    Production(
            const char*left_hand_side,
            const char*right_hand_side,
            handler action,
            ProductionInfo& attr=*ProductionInfo::default_info)
            :left_hand_side(left_hand_side),
            right_hand_side(right_hand_side),
            action(std::move(action)),
            attributes(&attr){
    }
};


#endif