//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_C_TYPE_H
#define COMPILER_C_TYPE_H

#include "Csymbols.hpp"
#include <memory>
class C_type {
    // may be not a good definition, so you can modify it.
    std::shared_ptr<CSym::type_name> type_name;
public:
    bool equals(C_type& other);
    std::string toString();
};


#endif //COMPILER_C_TYPE_H
