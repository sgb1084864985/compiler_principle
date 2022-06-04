//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_COMPOUND_STMT_H
#define COMPILER_ATTR_RULE_COMPOUND_STMT_H

#include "attr_rule.hpp"

//compound_statement->{ }
//compound_statement->{ block_item_list }
class AttrRuleCompound : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto old_namespace = context.currentNameSpace;
		context.currentNameSpace = std::make_shared<CNameSpace>(tree_node, context.currentNameSpace);
        tree_node->owner = context.currentNameSpace;
        if(tree_node->children.size()==3){
            tree_node->children[1]->getAttr().FillAttributes(context, tree_node->children[1]);
        }
		context.currentNameSpace = old_namespace;
	}
};

#endif //COMPILER_ATTR_RULE_COMPOUND_STMT_H
