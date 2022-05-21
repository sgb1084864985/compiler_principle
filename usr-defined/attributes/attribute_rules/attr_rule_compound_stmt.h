//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_COMPOUND_STMT_H
#define COMPILER_ATTR_RULE_COMPOUND_STMT_H

#include "attr_rule.hpp"

class AttrRuleCompound : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::compound_statement>(tree_node);
		p->owner = context.currentNameSpace;
		auto new_namespace = std::make_shared<CNameSpace>(tree_node, context.currentNameSpace);
		auto cur_namespace = context.currentNameSpace;
		context.currentNameSpace = new_namespace;
		TreeNodeFillAttributes(context, p->children[1]);
		context.currentNameSpace = cur_namespace;
	}
};

#endif //COMPILER_ATTR_RULE_COMPOUND_STMT_H
