//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_DECL_H
#define COMPILER_ATTR_RULE_DECL_H

#include "attr_rule.hpp"
#include "attr_rule_para_list.h"
#include <stdexcept>

class AttrRuleDirectDecl : public AttrRule {
public:
	virtual void FillAttributes(AttrContext& context, symbol_ptr& tree_node, ptrType& type) const = 0;
};

//direct_declarator->id
class AttrRuleDirectDeclSingleId : public AttrRuleDirectDecl {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node, ptrType &type) const override {
		auto p = std::dynamic_pointer_cast<CSym::direct_declarator>(tree_node);
		p->owner = context.currentNameSpace;
		auto child = std::dynamic_pointer_cast<TerminalValue>(p->children[0]);
		auto id = child->getText();
		auto val = std::make_shared<CNameSpace::name_item>(type);
		context.currentNameSpace->insert(id, val);
	}
};

//direct_declarator->direct_declarator ( )
class AttrRuleDirectDeclFuncWithoutPara : public AttrRuleDirectDecl {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node, ptrType &type) const override {
		auto p = std::dynamic_pointer_cast<CSym::direct_declarator>(tree_node);
		p->owner = context.currentNameSpace;
		vector<ptrType> params;
		auto new_type = C_type::newFuncType(type, params);
		auto& attr = getAttr<AttrRuleDirectDecl>(p->children[0]);
		attr.FillAttributes(context, tree_node, new_type);
	}
};

//direct_declarator->direct_declarator ( parameter_type_list )
class AttrRuleDirectDeclFuncWithPara : public AttrRuleDirectDecl {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node, ptrType &type) const override {
		auto p = std::dynamic_pointer_cast<CSym::direct_declarator>(tree_node);
		p->owner = context.currentNameSpace;
		auto attr2 = getAttr<AttrRuleParamTypeList>(p->children[2]);
		attr2.FillAttributes(context, p->children[2]);
		auto list = attr2.GetTypeList();
		auto is_variable = attr2.IsVaraible();
		auto new_type = C_type::newFuncType(type, list, CTS::EXTERN, CTS::NONE, is_variable);
		auto& attr0 = getAttr<AttrRuleDirectDecl>(p->children[0]);
		attr0.FillAttributes(context, tree_node, new_type);
	}
};

class AttrRuleDecl : public AttrRule {
public:
	virtual void FillAttributes(AttrContext& context, symbol_ptr& tree_node, ptrType& type) const = 0;
};

//declarator->direct_declarator
class AttrRuleDeclDirectDecl : public AttrRuleDecl {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node, ptrType &type) const override {
		auto p = std::dynamic_pointer_cast<CSym::declarator>(tree_node);
		p->owner = context.currentNameSpace;
		auto& attr = getAttr<AttrRuleDirectDecl>(p->children[0]);
		attr.FillAttributes(context, p->children[0], type);
	}
};

//init_declarator->declarator
class AttrRuleInitDecl : public AttrRule {
public:
	virtual void FillAttributes(AttrContext& context, symbol_ptr& tree_node, ptrType& type) const {
		auto p = std::dynamic_pointer_cast<CSym::init_declarator_list>(tree_node);
		p->owner = context.currentNameSpace;
		auto& attr = getAttr<AttrRuleDecl>(p->children[0]);
		attr.FillAttributes(context, p->children[0], type);
	}
};

//init_declarator_list->init_declarator
class AttrRuleInitList : public AttrRule {
public:
	virtual void FillAttributes(AttrContext& context, symbol_ptr& tree_node, ptrType& type) const {
		auto p = std::dynamic_pointer_cast<CSym::init_declarator_list>(tree_node);
		p->owner = context.currentNameSpace;
		auto attr = getAttr<AttrRuleInitDecl>(p->children[0]);
		attr.FillAttributes(context, p->children[0], type);
	}
};

//declaration->declaration_specifiers init_declarator_list ;
class AttrRuleDeclaration : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::declaration>(tree_node);
		p->owner = context.currentNameSpace;
		TreeNodeFillAttributes(context, p->children[0]);
		auto attr1 = getAttr(p->children[0]);
		auto type = attr1.GetType();

		auto& attr2 = getAttr<AttrRuleInitList>(p->children[1]);
		attr2.FillAttributes(context, p->children[1], type);
	}
};

//declaration_specifiers->type_specifier
class AttrRuleDeclSpec : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		auto p = std::dynamic_pointer_cast<CSym::declaration_specifiers>(tree_node);
		p->owner = context.currentNameSpace;
		TreeNodeFillAttributes(context, p->children[0]);
		auto attr0 = getAttr(p->children[0]);
		m_type = attr0.GetType();
	}

	ptrType GetType() override {
		return m_type;
	}

protected:
	ptrType m_type;
};

#endif //COMPILER_ATTR_RULE_DECL_H
