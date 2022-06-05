//
// Created by hansljy on 22-5-23.
//

#ifndef COMPILER_ATTR_RULE_WHILE_H
#define COMPILER_ATTR_RULE_WHILE_H

#include "attr_rule.hpp"

// this is the same as AttrRuleSelection
//iteration_statement->while ( expr ) statement
class AttrRuleWhile : public  AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto expr = tree_node->children[2];
		expr->getAttr().FillAttributes(context, expr);
		if (expr->type->getTypeSpecifier() != CTS::BOOL && ( !expr->implicit_cast_type || expr->implicit_cast_type->getTypeSpecifier() != CTS::BOOL)) {
            emitError(context,tree_node,"Condition in While statement cannot be converted to bool");
        }
		auto stmt1 = tree_node->children[4];
		stmt1->getAttr().FillAttributes(context, stmt1);
	}
};

#endif //COMPILER_ATTR_RULE_WHILE_H
