//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_COMPOUND_STMT_H
#define COMPILER_ATTR_RULE_COMPOUND_STMT_H

#include "attr_rule.hpp"

class AttrRuleCompound : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto old_namespace = context.currentNameSpace;
		context.currentNameSpace = std::make_shared<CNameSpace>(tree_node, context.currentNameSpace);
		tree_node->getAttr().FillAttributes(context, tree_node->children[1]);
		context.currentNameSpace = old_namespace;
	}
};

#endif //COMPILER_ATTR_RULE_COMPOUND_STMT_H
