//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_SELECTION_STMT_H
#define COMPILER_ATTR_RULE_SELECTION_STMT_H

#include "attr_rule.hpp"

//selection_statement->if ( expr ) statement
class AttrRuleStmt : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::selection_statement>(tree_node);
		TreeNodeFillAttributes(context, p->children[2]);
		auto new_namespace = std::make_shared<CNameSpace>(tree_node, context.currentNameSpace);
		auto cur_namespace = context.currentNameSpace;
//		TreeNodeFillAttributes(context, )
	}
};

#endif //COMPILER_ATTR_RULE_SELECTION_STMT_H
