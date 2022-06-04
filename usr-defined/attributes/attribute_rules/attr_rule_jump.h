//
// Created by zlz on 22-6-2.
//

#ifndef COMPILER_ATTR_RULE_JUMP_H
#define COMPILER_ATTR_RULE_JUMP_H
#include "attr_rule.hpp"

//jump_statement->return expr ;
class AttrRuleReturn : public AttrRule {
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto expr = tree_node->children[1];
        expr->getAttr().FillAttributes(context,expr);
    }

protected:
    ptrType m_type;
};
#endif //COMPILER_ATTR_RULE_JUMP_H
