//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_C_CONSTANT_H
#define COMPILER_C_CONSTANT_H

enum class dType {
    UNSIGNED_INTEGER,SIGNED_INTEGER,FLOAT
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



#endif //COMPILER_C_CONSTANT_H
