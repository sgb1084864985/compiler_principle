//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_TYPE_SPEC_H
#define COMPILER_ATTR_RULE_TYPE_SPEC_H

#include "attr_rule.hpp"


template <CTS::TypeSpecifier type>
class AttrRuleTypeSpec : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		tree_node->type = C_type::newBasicType(type);
	}
};

#endif //COMPILER_ATTR_RULE_TYPE_SPEC_H
