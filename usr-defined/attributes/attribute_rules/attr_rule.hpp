//
// Created by zlz on 22-5-16.
//

#ifndef COMPILER_ATTR_RULE_EXPR_H
#define COMPILER_ATTR_RULE_EXPR_H

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
	virtual ptrType GetType(symbol_ptr& node) {
		throw std::logic_error("No type provided");
	}

	virtual OperatorType GetOperator(symbol_ptr& node) {
		throw std::logic_error("No operator provided");
	}

    virtual void fillAttributes(AttrContext& context, symbol_ptr& tree_node)=0;

    static void fillAttributes(ProductionInfo& info,AttrContext& context,symbol_ptr& tree_node){
        auto&attr_info =dynamic_cast<AttrRule&>(info);
        return attr_info.fillAttributes(context,tree_node);
    }

    static void tree_node_fillAttributes(AttrContext& context, symbol_ptr& tree_node){
        auto item= std::dynamic_pointer_cast<AST::NonTerminal>(tree_node);
        return fillAttributes(item->production.getAttrs(),context,tree_node);
    }
};

#endif //COMPILER_ATTR_RULE_EXPR_H
