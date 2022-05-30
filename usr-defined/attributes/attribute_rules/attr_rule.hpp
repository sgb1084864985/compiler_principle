//
// Created by zlz on 22-5-16.
//

#ifndef COMPILER_ATTR_RULE_H
#define COMPILER_ATTR_RULE_H

#include "ProductionInfo.h"
#include "AttrContext.h"
#include <stdexcept>

enum class OperatorType {
	kEqual,
	kMultiplyEqual,
	kModuleEqual,
	kPlusEqual,
	kMinusEqual,
	kLeftShiftEqual,
	kRightShiftEqual,
	kAndEqual,
	kXorEqual,
	kOrEqual,
	kPlusPlus,
	kMinusMinus,
	kPlus,
	kMinus,
	kMultiply,
	kAnd,
	kOr,
	kTilde,
	kExclaim,
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
			child->getAttr().FillAttributes(context, child);
		}
	}
};

class AttrRuleError : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->error = true;
	}
};



#endif //COMPILER_ATTR_RULE_H
