//
// Created by zlz on 22-4-29.
//

#ifndef COMPILER_C_RULE_ATTR_H
#define COMPILER_C_RULE_ATTR_H

#include "ProductionInfo.h"
#include <vector>
using std::vector;
class C_RuleAttributesPool{
public:
    static std::unique_ptr<ProductionInfo> ruleAttrTable[];
};

#endif //COMPILER_C_RULE_ATTR_H
