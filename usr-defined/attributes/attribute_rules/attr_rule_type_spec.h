//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_TYPE_SPEC_H
#define COMPILER_ATTR_RULE_TYPE_SPEC_H

#include "attr_rule.hpp"

class AttrRuleTypeSpec : public AttrRule {
public:
	AttrRuleTypeSpec(CTS::TypeSpecifier&& type) {
		m_type = C_type::newBasicType(type);
	}
	AttrRuleTypeSpec(CTS::TypeSpecifier&& type, bool is_unsigned) {
		m_type = C_type::newBasicType(type, is_unsigned);
	}
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {}
	ptrType GetType() override {
		return m_type;
	}
protected:
	ptrType m_type;
};

#endif //COMPILER_ATTR_RULE_TYPE_SPEC_H
