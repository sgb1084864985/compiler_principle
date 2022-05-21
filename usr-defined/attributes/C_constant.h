//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_C_CONSTANT_H
#define COMPILER_C_CONSTANT_H
#include <memory>
#include <vector>

// if is a pointer(including function pointer, dType should be UNSIGNED_INTEGER)
enum class dType {
    UNSIGNED_INTEGER,SIGNED_INTEGER,FLOAT,STRUCT
};

enum class TokenType{
    INTEGER,FLOAT,STRING
};

// C_constant stores an array(length>=1),
// or a single value (length=1)
class C_constant {
    using ptr_constant=std::shared_ptr<C_constant>;
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
    template<class T> T getValue();

    template<class T>
    static ptr_constant newConstant(T values);

    template<class T>
    static ptr_constant newZero();

    template<class T>
    static ptr_constant newOne();

    template<class T1,class T2>
    static ptr_constant newAdd(ptr_constant& op1,ptr_constant& op2);

    template<class T1,class T2>
    static ptr_constant newMul(ptr_constant& op1,ptr_constant& op2);

    template<class T1,class T2>
    static ptr_constant newSub(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newMinus(ptr_constant& op1);

    template<class T1,class T2>
    static ptr_constant newDiv(ptr_constant& op1,ptr_constant& op2);

    template<class T1,class T2>
    static ptr_constant newMod(ptr_constant& op1,ptr_constant& op2);

    template<class T1,class T2>
    static ptr_constant newLOGIC_OR(ptr_constant& op1,ptr_constant& op2);

    template<class T1,class T2>
    static ptr_constant newLOGIC_AND(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newLOGIC_NOT(ptr_constant& op1);

    template<class T>
    static ptr_constant newEQ(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newNEQ(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newLE(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newLT(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newGE(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newGT(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newSELECT(ptr_constant& condition,ptr_constant& val1,ptr_constant& val2);

    template<class T1,class T2>
    static ptr_constant newOR(ptr_constant& op1,ptr_constant& op2);

    template<class T1,class T2>
    static ptr_constant newAND(ptr_constant& op1,ptr_constant& op2);

    template<class T>
    static ptr_constant newNOT(ptr_constant& op1);

    template<class T1,class T2>
    static ptr_constant newLEFT_SHIFT(ptr_constant& op1,ptr_constant& op2);

    template<class T1,class T2>
    static ptr_constant newRIGHT_SHIFT(ptr_constant& op1,ptr_constant& op2);

    virtual void describe(){}
//    dType dt=dType::SIGNED_INTEGER;
//    int bytes_per_unit=8; // at least 1
//    int length{};
//
//    unsigned char * data{};

};



using ptr_constant=std::shared_ptr<C_constant>;

#endif //COMPILER_C_CONSTANT_H
