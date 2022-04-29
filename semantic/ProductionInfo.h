//
// Created by zlz on 22-4-29.
//

#ifndef COMPILER_PRODUCTION_INFORMATION_H
#define COMPILER_PRODUCTION_INFORMATION_H
#include <memory>
// Interface ProductionInfo:
// Describe the attributes and functions of some productions.
// All subclasses should have defined no-arg constructors.
class ProductionInfo{
public:
    static std::unique_ptr<ProductionInfo> default_info;
    // no use but to make the class virtual.
    virtual void describe(){}
};

#endif //COMPILER_PRODUCTION_INFORMATION_H
