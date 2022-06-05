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
	explicit AttrRuleParamTypeList(bool variable_length) : m_variable_length(variable_length) {}
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto param_list = tree_node->children[0];
        tree_node->params= std::make_shared<CTS::Parameters>();
        param_list->params=tree_node->params;
        param_list->inheritedContext=tree_node->inheritedContext;
        param_list->getAttr().FillAttributes(context,param_list);
		tree_node->params->ellipse = m_variable_length;
	}
protected:
	bool m_variable_length = false;
};

//parameter_list->parameter_declaration
class AttrRuleParamListSingleDecl : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto decl = tree_node->children[0];
        decl->inheritedContext=tree_node->inheritedContext;
        decl->getAttr().FillAttributes(context, decl);
		tree_node->params->param_list.push_back(decl->type);
	}
};

//parameter_list->parameter_list , parameter_declaration
class AttrRuleParamListMultiDecl : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto list = tree_node->children[0];
        list->params=tree_node->params;
        auto decl = tree_node->children[2];
        decl->inheritedContext=tree_node->inheritedContext;
        list->inheritedContext=tree_node->inheritedContext;
        list->getAttr().FillAttributes(context, list);
		decl->getAttr().FillAttributes(context, decl);
		tree_node->params->param_list.push_back(decl->type);
	}
};

//parameter_declaration->declaration_specifiers declarator
class AttrRuleParameterDecl : public  AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto decl_spec = tree_node->children[0];
		auto decl = tree_node->children[1];
        decl->inheritedContext=tree_node->inheritedContext;
		decl_spec->getAttr().FillAttributes(context, decl_spec);
		auto type = decl_spec->type;
		decl->inherited_type = type;
		decl->getAttr().FillAttributes(context, decl);
		tree_node->type = decl->type;
	}
};

#endif //COMPILER_ATTR_RULE_PARAMS_H
