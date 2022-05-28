//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_C_CONSTANT_H
#define COMPILER_C_CONSTANT_H
#include <memory>
#include <vector>
#include "C_type.h"

// if is a pointer(including function pointer, dType should be UNSIGNED_INTEGER)
enum class dType {
    UNSIGNED_INTEGER,SIGNED_INTEGER,FLOAT,STRUCT
};

enum class TokenType{
    INTEGER,FLOAT,STRING
};

//class C_type;
//using ptrType=std::shared_ptr<C_type>;

class C_constant;
using ptr_constant=std::shared_ptr<C_constant>;

// C_constant stores an array(length>=1),
// or a single value (length=1)
class C_constant {
public:
    static ptr_constant newArray(std::vector<ptr_constant>& constants) noexcept;

    static ptr_constant newStruct(std::vector<ptr_constant>& constants) noexcept;

    static ptr_constant fromString(std::string& str,TokenType type) noexcept;

    // for create function, if error occurred, return empty pointer constant

    static ptr_constant newNullValue();
    static ptr_constant newPtrValue(void*ptr);
    static ptr_constant newPtrAdd(ptr_constant& ptr,unsigned unit_size);
    static ptr_constant newPtrSub(ptr_constant& ptr,unsigned unit_size);

    // for functions below, class T allows only basic type or their pointer
    template<class T> static T getValue(ptr_constant& src);

    template<class T>
    static ptr_constant newConstant(T values);

    template<class T>
    static ptr_constant newZero();

    template<class T>
    static ptr_constant newOne();

    static ptr_constant newAdd(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newMul(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newSub(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newMinus(ptr_constant& op1);

    static ptr_constant newDiv(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newMod(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newLOGIC_OR(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newLOGIC_AND(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newLOGIC_NOT(ptr_constant& op1);

    static ptr_constant newEQ(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newNEQ(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newLE(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newLT(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newGE(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newGT(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newSELECT(ptr_constant& condition,ptr_constant& val1,ptr_constant& val2);

    static ptr_constant newOR(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newAND(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newNOT(ptr_constant& op1);

    static ptr_constant newComplement(ptr_constant& op1);

    static ptr_constant newLEFT_SHIFT(ptr_constant& op1,ptr_constant& op2);

    static ptr_constant newRIGHT_SHIFT(ptr_constant& op1,ptr_constant& op2);

    virtual ptrType getType()=0;

    static ptr_constant getBoolConstant(bool boolean);

};

namespace C_CONST{
    template<class T>
    static inline ptrType getType(){
        return C_type::newBasicType(CTS::VOID);
    }
    template<>ptrType getType<int>(){
        return C_type::newBasicType(CTS::INT);
    }
    template<>ptrType getType<float>(){
        return C_type::newBasicType(CTS::FLOAT);
    }
    template<>ptrType getType<double>(){
        return C_type::newBasicType(CTS::DOUBLE);
    }
    template<>ptrType getType<short>(){
        return C_type::newBasicType(CTS::SHORT);
    }
    template<>ptrType getType<char>(){
        return C_type::newBasicType(CTS::CHAR);
    }
    template<>ptrType getType<long>(){
        return C_type::newBasicType(CTS::LONG);
    }
    template<>ptrType getType<long long >(){
        return C_type::newBasicType(CTS::LONGLONG);
    }
    template<class T>
    static inline T mod(T op1,T op2){
        throw std::logic_error("mod operation not supported!");
    }
    template<> int mod<int>(int op1,int op2){
        return op1%op2;
    }
}

class ConstantArithmetic:public C_constant{
public:
    virtual ptr_constant _add(ptr_constant& other)=0;
    virtual ptr_constant _sub(ptr_constant& other)=0;
    virtual ptr_constant _minus()=0;
    virtual ptr_constant _mul(ptr_constant& other)=0;
    virtual ptr_constant _div(ptr_constant& other)=0;
    virtual ptr_constant _mod(ptr_constant& other)=0;
    virtual ptr_constant _eq(ptr_constant& other)=0;
    virtual ptr_constant _neq(ptr_constant& other)=0;
    virtual ptr_constant _le(ptr_constant& other)=0;
    virtual ptr_constant _lt(ptr_constant& other)=0;
    virtual ptr_constant _ge(ptr_constant& other)=0;
    virtual ptr_constant _gt(ptr_constant& other)=0;
    virtual ptr_constant _not()=0;
};

template<class T>
class ConstantSingleElement:public ConstantArithmetic{
public:
    explicit ConstantSingleElement(T val):m_data(val){}
    T getData(){
        return m_data;
    }
    ptr_constant _add(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return std::make_shared<ConstantSingleElement<T>>(m_data+p_other->m_data);
    }
    ptr_constant _sub(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return std::make_shared<ConstantSingleElement<T>>(m_data-p_other->m_data);
    }
    ptr_constant _minus() override {
        return std::make_shared<ConstantSingleElement<T>>(-m_data);
    }
    ptr_constant _mul(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return std::make_shared<ConstantSingleElement<T>>(m_data*p_other->m_data);
    }
    ptr_constant _div(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return std::make_shared<ConstantSingleElement<T>>(m_data/p_other->m_data);
    }
    ptr_constant _mod(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return std::make_shared<ConstantSingleElement<T>>(C_CONST::mod(m_data,p_other->m_data));
    }
    ptr_constant _eq(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return getBoolConstant(m_data==p_other->m_data);
    }
    ptr_constant _neq(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return getBoolConstant(m_data!=p_other->m_data);
    }
    ptr_constant _le(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return getBoolConstant(m_data<p_other->m_data);
    }
    ptr_constant _lt(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return getBoolConstant(m_data<=p_other->m_data);
    }
    ptr_constant _ge(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return getBoolConstant(m_data>=p_other->m_data);
    }
    ptr_constant _gt(ptr_constant &other) override {
        auto p_other=std::dynamic_pointer_cast<ConstantSingleElement<T>>(other);
        if(!p_other){
            throw std::logic_error("constant operation not in same type !");
        }
        return getBoolConstant(m_data>p_other->m_data);
    }
    ptr_constant _not() override {
        return getBoolConstant(!m_data);
    }
    ptrType getType() override{
        return C_CONST::getType<T>();
    }
private:
    T m_data;
};

template<class T>
T C_constant::getValue(ptr_constant& src) {
    auto p=std::dynamic_pointer_cast<ConstantSingleElement<T>>(src);
    if(!p){
        throw std::logic_error("can not get this type value!");
    }
    return p->getData();
}

template<class T>
ptr_constant C_constant::newConstant(T values) {
    return std::make_shared<ConstantSingleElement<T>>(values);
}




#endif //COMPILER_C_CONSTANT_H
