//
// Created by zlz on 22-5-23.
//

#include "attr_rule.hpp"


AttrRule &SymbolValue::getAttr() const {
    return static_cast<AttrRule&>(production.getAttrs());
}
