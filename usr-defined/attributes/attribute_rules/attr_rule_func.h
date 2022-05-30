//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_FUNC_H
#define COMPILER_ATTR_RULE_FUNC_H

#include "attr_rule.hpp"

//function_definition->declaration_specifiers declarator compound_statement
class AttrRuleFunc : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto decl_spec = tree_node->children[0];
		auto decl = tree_node->children[1];
		auto compound = tree_node->children[2];
		decl_spec->getAttr().FillAttributes(context, decl_spec);
		auto type = decl_spec->type;
		decl->inherited_type = type;
		decl->getAttr().FillAttributes(context, decl);
		auto old_namespace = context.currentNameSpace;
		context.currentNameSpace = std::make_shared<CNameSpace>(tree_node, context.currentNameSpace);
		compound->getAttr().FillAttributes(context, compound);
		context.currentNameSpace = old_namespace;
	}

protected:
	ptrType m_type;
};

#endif //COMPILER_ATTR_RULE_FUNC_H
