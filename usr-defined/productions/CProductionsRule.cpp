//
// Created by zlz on 22-5-12.
//

#include "CProductions.h"
#include "C_rule_code.h"
#include "C_rule_attr.h"

void CProductions::addRules() {
    for(int i=0;i<productions.size();i++){
        productions[i].setAttrs(*C_RuleAttributesPool::ruleAttrTable[i]);
        productions[i].setGenCodeInfo(*C_rule_code::ruleCodeTable[i]);
    }
}

