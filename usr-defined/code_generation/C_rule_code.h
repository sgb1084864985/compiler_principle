//
// Created by zlz on 22-5-7.
//

#ifndef COMPILER_C_RULE_CODE_H
#define COMPILER_C_RULE_CODE_H

#include "ProductionInfo.h"
#include <vector>
using std::vector;

class C_rule_code {
public:
    static std::unique_ptr<ProductionInfo> ruleCodeTable[];
};


#endif //COMPILER_C_RULE_CODE_H
