//
// Created by hansljy on 22-5-23.
//

#ifndef COMPILER_ATTR_RULE_PARAMS_H
#define COMPILER_ATTR_RULE_PARAMS_H

#include "attr_rule.hpp"

//parameter_type_list->parameter_list
//parameter_type_list->parameter_list , ...
class AttrRuleParamTypeList : public AttrRule {
public:
	AttrRuleParamTypeList(bool variable_length) : m_variable_length(variable_length) {}
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto param_list = tree_node->children[0];
		tree_node->params = param_list->params;
		tree_node->variable_param_length = m_variable_length;
	}
protected:
	bool m_variable_length = false;
};

#endif //COMPILER_ATTR_RULE_PARAMS_H
