//
// Created by zlz on 22-5-20.
//

#ifndef COMPILER_ATTR_RULE_EXPR_H
#define COMPILER_ATTR_RULE_EXPR_H

#include "attr_rule.hpp"

class AttrRuleExprDoNothing : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto child = tree_node->children[0];
		child->getAttr().FillAttributes(context, child);
		tree_node->constant = child->constant;
		tree_node->type = child->type;
	}
};

//assignment_expr->unary_expr assignment_operator assignment_expr
class AttrRuleAssignExprAssign : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		for (auto& child : tree_node->children) {
			child->getAttr().FillAttributes(context, child);
		}
		// TODO: add type system
		auto unary_expr = tree_node->children[0];
		auto assign_expr = tree_node->children[2];
		auto name = context.currentNameSpace->get(unary_expr->identifier);
		if (!name) {
			tree_node->error = true;
			context.global.error_out << "Use undeclared identifier!";
		} else {
			if (!name->type->equals(assign_expr->type)) {
				tree_node->error = true;
				context.global.error_out << "Illegal assignment";
			}
		}
		tree_node->constant = assign_expr->constant;
		tree_node->type = assign_expr->type;
	}
};

class AttrRuleOpExpr : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto op1 = tree_node->children[0];
		auto op2 = tree_node->children[2];

		op1->getAttr().FillAttributes(context, op1);
		op2->getAttr().FillAttributes(context, op2);

		if (op1->constant != nullptr && op2->constant != nullptr) {
			SetConstant(op1->constant, op2->constant, tree_node);
		}
		CheckType(op1->type, op2->type, context, tree_node);
	}

protected:
	virtual void
	CheckType(ptrType type1, ptrType type2, AttrContext &context,
			  symbol_ptr &tree_node) = 0;
	virtual void SetConstant(ptr_constant &const1, ptr_constant &const2,
							 symbol_ptr &tree_node) = 0;
};

class AttrRuleLogicExpr : public AttrRuleOpExpr {
	void CheckType(ptrType type1, ptrType type2, AttrContext &context,
				   symbol_ptr &tree_node) override {
		if (type1->getTypeSpecifier() != CTS::BOOL || type2->getTypeSpecifier() != CTS::BOOL) {
			tree_node->error = true;
			context.global.error_out << "Illegal operand type in logical expression";
		}
	}
	void SetConstant(ptr_constant &const1, ptr_constant &const2, symbol_ptr &tree_node) override = 0;
};

//logic_or_expr->logic_or_expr || logic_and_expr
class AttrRuleLogicOrExpr : public AttrRuleLogicExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		bool constant = const1->getValue<bool>() || const2->getValue<bool>();
		tree_node->constant = C_constant::newConstant(constant);
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
	void CheckType(ptrType type1, ptrType type2, AttrContext &context,
				   symbol_ptr &tree_node) override {
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
	void CheckType(ptrType type1, ptrType type2, AttrContext &context,
				   symbol_ptr &tree_node) override {
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
		tree_node->constant = C_constant::newEQ(const1, const2);
	}
};

class AttrRuleNotEqExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newNEQ(const1, const2);
	}
};

class AttrRuleLessThanExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newLT(const1, const2);
	}
};

class AttrRuleGreaterThanExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newGT(const1, const2);
	}
};

class AttrRuleLessEqualExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newLE(const1, const2);
	}
};

class AttrRuleGreaterEqualExpr : public AttrRuleRelationExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newGE(const1, const2);
	}
};

class AttrRuleUnaryOperator : public  AttrRule {
public:
	AttrRuleUnaryOperator(const OperatorType& type) : m_op_type(type) {}

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
