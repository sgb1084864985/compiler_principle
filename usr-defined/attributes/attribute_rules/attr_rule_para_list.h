//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_PARA_LIST_H
#define COMPILER_ATTR_RULE_PARA_LIST_H

#include "attr_rule.hpp"

class AttrRuleParamList : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override = 0;

	vector<ptrType> GetTypeList() {
		return m_type_list;
	}
private:
	vector<ptrType> m_type_list;
};

//parameter_list->parameter_declaration
class AttrRuleParamListSingleDecl : public  AttrRuleParamList {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::parameter_list>(tree_node);
		p->owner = context.currentNameSpace;

	}
};

//parameter_type_list->parameter_list , ...
//parameter_type_list->parameter_list
class AttrRuleParamTypeList : public AttrRule {
public:
	AttrRuleParamTypeList(bool is_variable) : m_is_variable(is_variable) {}

	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::parameter_type_list>(tree_node);
		p->owner = context.currentNameSpace;
		auto& attr = getAttr<AttrRuleParamList>(p->children[0]);
		attr.FillAttributes(context, p->children[0]);
		m_type_list = attr.GetTypeList();
	}

	vector<ptrType> GetTypeList() {
		return m_type_list;
	}

	bool IsVaraible() {
		return m_is_variable;
	}

protected:
	vector<ptrType> m_type_list;
	bool m_is_variable;
};

#endif //COMPILER_ATTR_RULE_PARA_LIST_H
