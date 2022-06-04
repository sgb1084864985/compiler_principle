//
// Created by zlz on 22-5-16.
//

#ifndef COMPILER_ATTR_RULE_H
#define COMPILER_ATTR_RULE_H

#include "ProductionInfo.h"
#include "AttrContext.h"
#include <stdexcept>

class NoAttrException:public std::logic_error{
public:
    explicit NoAttrException(const string &arg) : logic_error(arg) {}
};

class AttrRule:public ProductionInfo{
public:
	virtual void FillAttributes (AttrContext& context, symbol_ptr& tree_node){
        throw std::logic_error("Method FillAttributes is not implemented");
    }
};

/**
 * In this attribute rule, we don't need any information about the lhs of the
 * production rule, so we don't calculate them and leave them as default
 */
class AttrRuleDoNothing : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		for (auto& child : tree_node->children) {
            try{
                child->getAttr().FillAttributes(context, child);
            }
            catch (NoAttrException&e){}
		}
	}
};

class AttrRuleError : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->error = true;
	}
};

class AttrRuleNull : public AttrRule {
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
    }
};


#endif //COMPILER_ATTR_RULE_H
