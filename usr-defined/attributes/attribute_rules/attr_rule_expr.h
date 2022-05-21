//
// Created by zlz on 22-5-20.
//

#ifndef COMPILER_ATTR_RULE_EXPR_H
#define COMPILER_ATTR_RULE_EXPR_H

#include "attr_rule.hpp"

//expr->assignment_expr
class AttrRuleExpr : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		p->owner = context.currentNameSpace;
		TreeNodeFillAttributes(context, p->children[0]);
		auto child = std::dynamic_pointer_cast<CSym::expr>(p->children[0]);
		p->constant = child->constant;
		m_type = p->type = child->type;
		p->implicit_cast_type = child->implicit_cast_type;
	}

	ptrType GetType() override {
		return m_type;
	}

protected:
	ptrType m_type;
};

//assignment_expr->unary_expr assignment_operator assignment_expr
class AttrRuleAssignExprAssign : public AttrRuleExpr {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {

	}
};

class AttrRuleOpExpr : public AttrRuleExpr {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		p->owner = context.currentNameSpace;

		TreeNodeFillAttributes(context, p->children[0]);
		TreeNodeFillAttributes(context, p->children[2]);

		auto child1 = std::dynamic_pointer_cast<CSym::C_expr>(p->children[0]);
		auto child2 = std::dynamic_pointer_cast<CSym::C_expr>(p->children[2]);
		auto attr1 = getAttr(p->children[0]);
		auto attr2 = getAttr(p->children[2]);

		if (child1->constant != nullptr && child2->constant != nullptr) {
			SetConstant(child1->constant, child2->constant, tree_node);
		}
		CheckType(attr1.GetType(), attr2.GetType(), tree_node);
	}

protected:
	virtual void
	CheckType(ptrType type1, ptrType type2, symbol_ptr &tree_node) = 0;
	virtual void SetConstant(ptr_constant &const1, ptr_constant &const2,
							 symbol_ptr &tree_node) = 0;
};

class AttrRuleLogicExpr : public AttrRuleOpExpr {
	void CheckType(ptrType type1, ptrType type2, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		if (type1->getTypeSpecifier() != CTS::BOOL || type2->getTypeSpecifier() != CTS::BOOL) {
			p->error = true;
		}
	}
	void SetConstant(ptr_constant &const1, ptr_constant &const2, symbol_ptr &tree_node) override = 0;
};

//logic_or_expr->logic_or_expr || logic_and_expr
class AttrRuleLogicOrExpr : public AttrRuleLogicExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		bool constant = const1->getValue<bool>() || const2->getValue<bool>();
		p->constant = C_constant::newConstant(constant);
	}
};

class AttrRuleLogicAndExpr : public AttrRuleLogicExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		bool constant = const1->getValue<bool>() && const2->getValue<bool>();
		p->constant = C_constant::newConstant(constant);
	}
};

class AttrRuleArithExpr : public AttrRuleOpExpr {
	void CheckType(ptrType type1, ptrType type2, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		if (!type1->equals(type2)) {
			p->error = true;
		}
	}
};

class AttrRuleAddExpr : public AttrRuleArithExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		bool constant = const1->getValue<bool>() + const2->getValue<bool>();
		p->constant = C_constant::newConstant(constant);
	}
};

class AttrRuleMinusExpr : public AttrRuleArithExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		bool constant = const1->getValue<bool>() - const2->getValue<bool>();
		p->constant = C_constant::newConstant(constant);
	}
};

class AttrRuleMultExpr : public AttrRuleArithExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		bool constant = const1->getValue<bool>() * const2->getValue<bool>();
		p->constant = C_constant::newConstant(constant);
	}
};

class AttrRuleDivExpr : public AttrRuleArithExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		bool constant = const1->getValue<bool>() / const2->getValue<bool>();
		p->constant = C_constant::newConstant(constant);
	}
};



class AttrRuleRelationExpr : public AttrRuleOpExpr {
public:
	void CheckType(ptrType type1, ptrType type2, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		if (!type1->equals(type2)) {
			p->error = true;
		}
	}

	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override = 0;
};

class AttrRuleEqExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		// TODO
	}
};

class AttrRuleNotEqExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {

	}
};

class AttrRuleLessThanExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {

	}
};

class AttrRuleGreaterThanExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {

	}
};

class AttrRuleLessEqualExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {

	}
};

class AttrRuleGreaterEqual : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {

	}
};

class AttrRuleUnaryOperator : public  AttrRule {
public:
	AttrRuleUnaryOperator(const OperatorType& type) : m_op_type(type) {}

	OperatorType GetOperator(symbol_ptr &node) override {
		return m_op_type;
	}

protected:
	OperatorType m_op_type;
};

class AttrRuleUnaryExpr : public AttrRuleExpr {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::unary_expr>(tree_node);
		p->owner = context.currentNameSpace;

		TreeNodeFillAttributes(context, p->children[0]);
		TreeNodeFillAttributes(context, p->children[1]);

		auto attr1 = getAttr(p->children[0]);
		auto attr2 = getAttr(p->children[1]);

		switch (attr1.GetOperator(p->children[0])) {
			case OperatorType::kMinus:
				// TODO
				break;
			case OperatorType::kExclaim:
				// TODO
				break;
			default:
				throw std::logic_error("Unsupported unary expression");
		}
	}
};


#endif //COMPILER_ATTR_RULE_EXPR_H
