// compiler.hpp
#ifndef _COMPILER_H_
#define _COMPILER_H_
#include <functional>
#include <utility>
#include <vector>
#include <string>
#include <memory>

#ifdef DEBUG
#define DEBUG_TEST(x) do{x}while(0);
#else
#define DEBUG_TEST(x)
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
    int getID() const{
        return id;
    }
    void setID(int i){
        this->id=i;
    }

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
    virtual const std::string& getText()=0;
};

using symbol_ptr=std::shared_ptr<SymbolValue>;
using symbol_iterator=Iterator<symbol_ptr>;
using handler=function<symbol_ptr (symbol_iterator &,Context&)>;

class Production{
private:
    handler action;
public:
    const char* left_hand_side;
    const char* right_hand_side;
    symbol_ptr operator()(symbol_iterator &it,Context&con){
        return action(it,con);
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