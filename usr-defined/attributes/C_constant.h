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
    dType dt=dType::SIGNED_INTEGER;
    int bytes_per_unit=1; // at least 1
    int length{};

    unsigned char * data{};

    // if error, return empty pointer
    template<class T>
    static ptr_constant newConstant(T* values,int len);
    static ptr_constant fromString(std::string& str,TokenType type) noexcept;
    static ptr_constant toArray(std::vector<ptr_constant>& constants) noexcept;

    C_constant(C_constant&)=delete;
    C_constant& operator=(const C_constant&)=delete;
    C_constant(int bytes,int length,dType dt=dType::SIGNED_INTEGER);
    C_constant()=default;
    ~C_constant(){delete []data;}
};

using ptr_constant=std::shared_ptr<C_constant>;

#endif //COMPILER_C_CONSTANT_H
