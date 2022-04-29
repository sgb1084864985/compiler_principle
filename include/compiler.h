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

class Context{
};

class SymbolValue{
public:
    [[nodiscard]] int getID() const{
        return id;
    }
    void setID(int i){
        this->id=i;
    }
    virtual void print(std::ostream &out_port)=0;
private:
    int id=-1;

};

class TerminalValue:public SymbolValue{
public:
    // contains keywords like "if","int"
    // operators: like "<=","<<","->","."
    // "id" ([_a-zA-Z][_0-9a-zA-Z]*)
    // "number"
    // "float"
    virtual const char* getType()=0;

    // like "i","j","1.0","if"
    virtual const char * getText()=0;

    void print(std::ostream &out_port) override{
        out_port<<getText();
    }
};

using symbol_ptr=std::shared_ptr<SymbolValue>;
using symbol_iterator=Iterator<symbol_ptr>;

class Production{
    using handler=function<symbol_ptr (Production& self,symbol_iterator &,Context&)>;

private:
    handler action;
public:
    const char* left_hand_side;
    const char* right_hand_side;
    symbol_ptr operator()(symbol_iterator &it,Context&con){
        return action(*this,it,con);
    }

    Production(
            const char*left_hand_side,
            const char*right_hand_side,
            handler action)
            :left_hand_side(left_hand_side),
            right_hand_side(right_hand_side),
            action(std::move(action)){
    }
};


// class Production{
//     public:
//     virtual const char* getLeftHandSide()=0;// eg. "exp"
//     virtual const char* getRightHandSide()=0;// eg. "exp + term", must split by space
//     virtual SymbolValue action(Iterator<SymbolValue>& args,Context& context)=0;
//     // eg.
//     // args = [ exp, +, term ]
//     // you need to return exp(exp+term)
//     // if neccessary, add them to context (into member namespaces?)
// };

//class EmptyValue: public SymbolValue{
//    int id;
//public:
//    EmptyValue(int id):id(id){}
//    int getID(){return id;}
//};

#endif