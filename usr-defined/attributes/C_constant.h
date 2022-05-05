//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_C_CONSTANT_H
#define COMPILER_C_CONSTANT_H
#include <memory>
enum class dType {
    UNSIGNED_INTEGER,SIGNED_INTEGER,FLOAT,STRUCT
};

// C_constant stores an array(length>=1),
// or a single value (length=1)
class C_constant {
public:
    dType dt=dType::SIGNED_INTEGER;
    int least_bytes_per_unit=1; // at least 1
    int length{};
    unsigned char* data{};
};

using ptr_constant=std::shared_ptr<C_constant>;

#endif //COMPILER_C_CONSTANT_H
