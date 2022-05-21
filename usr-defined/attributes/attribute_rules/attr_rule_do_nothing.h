//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_DO_NOTHING_H
#define COMPILER_ATTR_RULE_DO_NOTHING_H

#include "attr_rule.hpp"

class AttrRuleDoNothing : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::NonTerminal>(tree_node);
		p->owner = context.currentNameSpace;
		for (auto child : p->children) {
			TreeNodeFillAttributes(context, child);
		}
	}
};

#endif //COMPILER_ATTR_RULE_DO_NOTHING_H
