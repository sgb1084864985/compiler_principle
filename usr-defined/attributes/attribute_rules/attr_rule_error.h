//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_ERROR_H
#define COMPILER_ATTR_RULE_ERROR_H

#include "attr_rule.hpp"
#include <stdexcept>

class AttrRuleError : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		throw std::logic_error("Wrong grammar");
	}
};

#endif //COMPILER_ATTR_RULE_ERROR_H
