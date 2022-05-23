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
	virtual ptrType GetType() {
		throw std::logic_error("No type provided");
	}

	virtual OperatorType GetOperator(symbol_ptr& node) {
		throw std::logic_error("No operator provided");
	}

	virtual std::string GetID() {
		throw std::logic_error("No ID provided");
	}

    virtual void FillAttributes(AttrContext& context, symbol_ptr& tree_node){
        throw std::logic_error("Method FillAttributes is not implemented");
    }

    static void FillAttributes(ProductionInfo& info, AttrContext& context, symbol_ptr& tree_node){
        auto&attr_info =dynamic_cast<AttrRule&>(info);
        attr_info.FillAttributes(context, tree_node);
    }

    static void TreeNodeFillAttributes(AttrContext& context, symbol_ptr& tree_node){
        auto item= std::dynamic_pointer_cast<AST::NonTerminal>(tree_node);
		if (item == nullptr) {
			return;
		}
        FillAttributes(item->production.getAttrs(), context, tree_node);
    }

    template<class T=AttrRule>
    static T& getAttr(symbol_ptr& node){
        auto item= std::dynamic_pointer_cast<AST::NonTerminal>(node);
        return dynamic_cast<T&>(item->production.getAttrs());
    }
};



#endif //COMPILER_ATTR_RULE_H
