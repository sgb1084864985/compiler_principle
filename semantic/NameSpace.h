//
// Created by zlz on 22-5-7.
//

#ifndef COMPILER_NAMESPACE_H
#define COMPILER_NAMESPACE_H

#include <memory>
// should be implemented
class NameSpace {
    virtual void describe(){}
};

using ptrAbstractNameSpace=std::shared_ptr<NameSpace>;
#endif //COMPILER_NAMESPACE_H
