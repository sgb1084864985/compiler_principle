#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include "compiler.h"
#include <memory>
#include <utility>


class Operand:public SymbolValue{

};

using operand_ptr=std::shared_ptr<Operand>;
using Op2=function<operand_ptr(operand_ptr,operand_ptr)>;

class BinaryOperator:public SymbolValue{
    Op2 op;
public:
    explicit BinaryOperator(Op2 op):op(std::move(op)){}
    operand_ptr operator()(operand_ptr x1,operand_ptr x2){
        return op(std::move(x1),std::move(x2));
    }
};

class OperandInt:public Operand{
    int val;
public:
    explicit OperandInt(int i):val(i){}
    int getValue()const{return val;}
};

#endif