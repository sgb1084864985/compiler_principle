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
        tree_node->lValue=child->lValue;
		tree_node->identifier = child->identifier;
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

		if (!unary_expr->lValue) {
			tree_node->error = true;
			context.global.error_out << "not a lvalue in the left side of assignment";
		} else {
			if (!unary_expr->type->equals(assign_expr->type)) {
				tree_node->error = true;
				context.global.error_out << "Illegal assignment";
			}
		}
		tree_node->constant = assign_expr->constant;
		tree_node->type = assign_expr->type;
	}
};

class AttrRuleOperator:public AttrRule{
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner=context.currentNameSpace;
        tree_node->binary_operator=m_op_t;
    }
    explicit AttrRuleOperator(OperatorType op_t):m_op_t(op_t){

    }
    OperatorType getOperator(){return m_op_t;}
private:
    OperatorType m_op_t;
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
        if(op1->implicit_cast_type){
            tree_node->type=op1->implicit_cast_type;
        }
        else{
            tree_node->type=op1->type;
        }
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
		bool constant = C_constant::getValue<bool>(const1) || C_constant::getValue<bool>(const2);
		tree_node->constant = C_constant::newConstant(constant);
	}
};

class AttrRuleLogicAndExpr : public AttrRuleLogicExpr {
public:
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::expr>(tree_node);
		bool constant = C_constant::getValue<bool>(const1) && C_constant::getValue<bool>(const2);
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
		tree_node->constant = C_constant::newAdd(const1, const2);
	}
};

class AttrRuleMinusExpr : public AttrRuleArithExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newSub(const1, const2);
	}
};

class AttrRuleMultExpr : public AttrRuleArithExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newMul(const1, const2);
	}
};

class AttrRuleDivExpr : public AttrRuleArithExpr {
	void SetConstant(ptr_constant &const1, ptr_constant &const2,
					 symbol_ptr &tree_node) override {
		tree_node->constant = C_constant::newDiv(const1, const2);
	}
};

class AttrRuleRemExpr : public AttrRuleArithExpr {
    void SetConstant(ptr_constant &const1, ptr_constant &const2,
                     symbol_ptr &tree_node) override {
        tree_node->constant = C_constant::newMod(const1, const2);
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
	explicit AttrRuleUnaryOperator(const UnaryOperatorType& type) : m_op_type(type) {}

	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		tree_node->unary_operator = m_op_type;
	}

protected:
	UnaryOperatorType m_op_type;
};

//unary_expr->unary_operator cast_expr
class AttrRuleUnaryExpr : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto cast_expr = tree_node->children[1];
		cast_expr->getAttr().FillAttributes(context, cast_expr);
		auto unary_op = tree_node->children[0];
		unary_op->getAttr().FillAttributes(context, unary_op);
		if (cast_expr->constant) {
			switch (unary_op->unary_operator) {
				case UnaryOperatorType::kMinus:
					tree_node->constant = C_constant::newMinus(cast_expr->constant);
					break;
				case UnaryOperatorType::kExclaim:
					tree_node->constant = C_constant::newNOT(cast_expr->constant);
					break;
				default:
					tree_node->error = true;
					context.global.error_out << "Unsupported unary operator";
			}
		}
		tree_node->type = cast_expr->type;
		tree_node->identifier = cast_expr->identifier;
	}
};

class AttrRulePostfixExpr : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {

	}
};

template<TokenType type>
class AttrRuleConstant : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		switch (type) {
			case TokenType::INTEGER:
				tree_node->type = C_type::newBasicType(CTS::INT);
				break;
			case TokenType::FLOAT:
				tree_node->type = C_type::newBasicType(CTS::FLOAT);
				break;
			case TokenType::STRING:
                tree_node->type=C_type::newBasicType(CTS::CHAR, true,CTS::AUTO,CTS::CONST)->newPointerType();
                break;
            default:
				tree_node->error = true;
				context.global.error_out << "Unsupported constant type";
		}
		string value = std::dynamic_pointer_cast<TerminalValue>(tree_node->children[0])->getText();
		tree_node->constant = C_constant::fromString(value, type);
	}
};

//primary_expr->( expr )
class AttrRulePrimaryExprParens : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto expr = tree_node->children[1];
		expr->getAttr().FillAttributes(context, expr);
		tree_node->constant = expr->constant;
		tree_node->type = expr->type;
        tree_node->lValue=expr->lValue;
	}
};

//primary_expr->id // id is identifier, like abc
class AttrRulePrimaryExprId : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
        tree_node->lValue= true;
		auto id = std::dynamic_pointer_cast<TerminalValue>(tree_node->children[0]);
		tree_node->identifier = id->getText();
		auto name_item = context.currentNameSpace->get(id->getText());
		if (!name_item) {
			tree_node->error = true;
			context.global.error_out << "Use of undeclared identifier";
		} else {
			tree_node->type = name_item->getType();
		}
	}
};

//primary_expr->constant
class AttrRulePrimaryExprConstant : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto constant = tree_node->children[0];
		constant->getAttr().FillAttributes(context, constant);
		tree_node->constant = constant->constant;
		tree_node->type = constant->type;
	}
};


//postfix_expr->postfix_expr ( )
class AttrRulePostfixExprFuncApp0:public AttrRule{
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto func = tree_node->children[0];
        func->getAttr().FillAttributes(context, func);
        if(func->type->isFunction()){
            if(!func->type->getParameterTypes()->param_list.empty()){
                tree_node->error= true;
                context.global.error_out<< "too less args" <<std::endl;
            }
        }
        else{
            tree_node->error= true;
            context.global.error_out<< "object not callable" <<std::endl;
        }
        tree_node->type=func->type->getReturnType();
    }
};


//postfix_expr->postfix_expr ( argument_expression_list )
class AttrRulePostfixExprFuncApp1:public AttrRule{
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto func = tree_node->children[0];
        func->getAttr().FillAttributes(context, func);
        tree_node->params= std::make_shared<CTS::Parameters>();
        if(func->type->isFunction()){
            visitArgs(tree_node->params->param_list,context,tree_node->children[2]);
            auto func_param_types=func->type->getParameterTypes();
            if(!func_param_types->ellipse && func_param_types->param_list.size()!=tree_node->params->param_list.size()){
                tree_node->error= true;
                context.global.error_out<< "arg numbers not match" <<std::endl;
                return;
            }
            for(int i=0;i<func_param_types->param_list.size();i++){
                if(!tree_node->params->param_list[i]->equals(func_param_types->param_list[i])){
                    tree_node->error= true;
                    context.global.error_out<<"arg types not match"<<std::endl;
                    return;
                }
            }
        }
        else{
            tree_node->error= true;
            context.global.error_out<< "object not callable" <<std::endl;
        }
        tree_node->type=func->type->getReturnType();
    }
    void visitArgs(vector<ptrType>& args,AttrContext &context, symbol_ptr &tree_node){
        tree_node->owner=context.currentNameSpace;
        if(tree_node->children.size()==1){
            auto expr=tree_node->children[0];
            expr->getAttr().FillAttributes(context,expr);
            args.push_back(expr->type);
        }
        else if(tree_node->children.size()==3){
            visitArgs(args,context,tree_node->children[0]);
            auto expr=tree_node->children[2];
            expr->getAttr().FillAttributes(context,expr);
            args.push_back(expr->type);
        }
    }
};

//postfix_expr->postfix_expr [ expr ]
class AttrRulePostfixExprArray : public AttrRule {
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto array = tree_node->children[0];
        array->getAttr().FillAttributes(context, array);
        if(!array->type->isArray() && !array->type->isPointer()){
            tree_node->error= true;
            context.global.error_out<<"Not an array or pointer, can not use operator []"<<std::endl;
            return;
        }

        auto index=tree_node->children[2];
        index->getAttr().FillAttributes(context,index);

        if(!index->type->isIntegerType()){
            tree_node->error= true;
            context.global.error_out<<"value in [] is not a integer"<<std::endl;
            return;
        }
        tree_node->type=array->type->getArrayElementType();
        tree_node->lValue= true;
    }
};

#endif //COMPILER_ATTR_RULE_EXPR_H
