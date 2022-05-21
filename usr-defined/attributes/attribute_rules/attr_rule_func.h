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
		auto p = std::dynamic_pointer_cast<CSym::function_definition>(tree_node);
		TreeNodeFillAttributes(context, p->children[0]);
		auto attr1 = getAttr(p->children[0]);

		auto new_namespace = std::make_shared<CNameSpace>(tree_node, context.currentNameSpace);
		auto cur_namespace = context.currentNameSpace;
		context.currentNameSpace = new_namespace;

		TreeNodeFillAttributes(context, p->children[1]);
		TreeNodeFillAttributes(context, p->children[2]);
		auto attr2 = getAttr(p->children[1]);
		auto attr3 = getAttr(p->children[2]);

		m_type = C_type::newMergeType(attr1.GetType()->getDeclarationSpecifiers(), attr2.GetType()->getDeclarator());

		auto ptr_func = std::make_shared<func_item>();
		ptr_func->body = p;
		ptr_func->func_namespace = cur_namespace;
		auto ptr_val = std::make_shared<CNameSpace::name_item>(m_type, ptr_func);
		cur_namespace->insert(attr1.GetID(), ptr_val, false);
		context.currentNameSpace = cur_namespace;
	}

	ptrType GetType() override {
		return m_type;
	}

protected:
	ptrType m_type;
};

#endif //COMPILER_ATTR_RULE_FUNC_H
