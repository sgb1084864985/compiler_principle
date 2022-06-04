//
// Created by zlz on 22-5-23.
//

#include "attr_rule.hpp"


AttrRule &SymbolValue::getAttr() const {
    if(&production==&Production::default_production){
        throw NoAttrException("No attr rule because this node is a terminal");
    }
    return static_cast<AttrRule&>(production.getAttrs());
}
