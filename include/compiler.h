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
#include "NameSpace.h"

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
class C_type;
class C_constant;
using ptrType=std::shared_ptr<C_type>;
using ptr_constant=std::shared_ptr<C_constant>;
class SymbolValue;

// symbol ptr is the pointer of SymbolValue,
// which is the base class of NonTerminal
// and TokenValue
using symbol_ptr=std::shared_ptr<SymbolValue>;
using symbol_iterator=Iterator<symbol_ptr>;

struct InheritedContext{
    bool isDeclare= false;
    bool isAbstractDeclare= false;
};

// represents one cfg rule.
class Production{
    using handler=function<symbol_ptr (Production& self,symbol_iterator &,Context&)>;

private:
    handler action;
    ProductionInfo* attributes;
    ProductionInfo* gen_code_info{};

public:
    const char* left_hand_side;
    const char* right_hand_side;

    void setAttrs(ProductionInfo& attr){
        attributes=&attr;
    }
    void setGenCodeInfo(ProductionInfo& info){
        gen_code_info=&info;
    }
    ProductionInfo& getAttrs(){
        return *attributes;
    }

    ProductionInfo& getGenCodeInfo(){
        return *gen_code_info;
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
    static Production default_production;
};

enum class UnaryOperatorType {
	kMinus,
	kExclaim
};

enum class OperatorType {
    kEqual,
    kMultiplyEqual,
    kModuleEqual,
    kDivEqual,
    kPlusEqual,
    kMinusEqual,
    kLeftShiftEqual,
    kRightShiftEqual,
    kAndEqual,
    kXorEqual,
    kOrEqual,
    kPlusPlus,
    kMinusMinus,
    kPlus,
    kMinus,
    kMultiply,
    kAnd,
    kOr,
    kTilde,
    kExclaim,
};

class AttrRule;

namespace CTS{
    class Parameters;
    using ptrParams=std::shared_ptr<Parameters>;
}

class SymbolValue{
public:
    [[nodiscard]] int getID() const{
        return id;
    }
    void setID(int i){
        this->id=i;
    }

    InheritedContext inheritedContext;
    ptr_constant constant;
    ptrType type;
	ptrType inherited_type;
    ptrType implicit_cast_type;
    vector<symbol_ptr> children;
    std::string label;
    Production& production=Production::default_production;
    bool error= false;
    ptrAbstractNameSpace owner;

	std::string identifier;
	CTS::ptrParams params;
    bool lValue= false;
	UnaryOperatorType unary_operator{};
    OperatorType binary_operator{};


    virtual void print(std::ostream &out_port){
        out_port << label;
    }

    virtual bool hasError(){
        return error;
    }

    [[nodiscard]] virtual ptrAbstractNameSpace getNameSpace() const{
        return owner;
    }

    [[nodiscard]] AttrRule& getAttr() const;

    SymbolValue()= default;
    SymbolValue(Production &production, std::string label) : production(production), label(std::move(label)) {}
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






#endif