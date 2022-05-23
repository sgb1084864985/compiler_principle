//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_DECL_H
#define COMPILER_ATTR_RULE_DECL_H

#include "attr_rule.hpp"
#include <stdexcept>

//direct_declarator->id
class AttrRuleDirectDeclSingleId : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto id = std::dynamic_pointer_cast<TerminalValue>(tree_node->children[0]);
		std::string identifier = id->getText();
		auto name_item = std::make_shared<CNameSpace::name_item>(tree_node->inherited_type);
		auto exist = context.currentNameSpace->get(identifier);
		if (!exist) {
			context.currentNameSpace->insert(identifier, name_item);
		} else {
			tree_node->error = true;
			context.global.error_out << "Identifier redefined!";
		}
	}
};

//direct_declarator->direct_declarator ( )
class AttrRuleDirectDeclFuncWithoutPara : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		vector<ptrType> params;
		auto new_type = C_type::newFuncType(tree_node->inherited_type, params);
		auto direct_decl = tree_node->children[0];
		direct_decl->inherited_type = new_type;
		direct_decl->getAttr().FillAttributes(context, direct_decl);
	}
};

//direct_declarator->direct_declarator ( parameter_type_list )
class AttrRuleDirectDeclFuncWithPara : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto param_list = tree_node->children[2];
		param_list->getAttr().FillAttributes(context, param_list);
		auto params = param_list->params;
		auto new_type = C_type::newFuncType(tree_node->inherited_type, params);
		auto direct_decl = tree_node->children[0];
		direct_decl->inherited_type = new_type;
		direct_decl->getAttr().FillAttributes(context, direct_decl);
	}
};

//declarator->direct_declarator
class AttrRuleDeclDirectDecl : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto direct_decl = tree_node->children[0];
		direct_decl->inherited_type = tree_node->inherited_type;
		direct_decl->getAttr().FillAttributes(context, direct_decl);
		tree_node->type = direct_decl->type;
	}
};

//init_declarator->declarator
class AttrRuleInitDecl : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto decl = tree_node->children[0];
		decl->inherited_type = tree_node->inherited_type;
		decl->getAttr().FillAttributes(context, decl);
	}
};

//init_declarator_list->init_declarator
class AttrRuleInitList : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto init_decl = tree_node->children[0];
		init_decl->inherited_type = tree_node->inherited_type;
		init_decl->getAttr().FillAttributes(context, init_decl);
	}
};

//declaration->declaration_specifiers init_declarator_list ;
class AttrRuleDeclaration : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto decl_spec = tree_node->children[0];
		decl_spec->getAttr().FillAttributes(context, decl_spec);

		auto init_decl_list = tree_node->children[1];
		init_decl_list->inherited_type = decl_spec->type;
		init_decl_list->getAttr().FillAttributes(context, init_decl_list);
	}
};

//declaration_specifiers->type_specifier
class AttrRuleDeclSpec : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto type_spec = tree_node->children[0];
		type_spec->getAttr().FillAttributes(context, type_spec);
		tree_node->type = type_spec->type;
	}
};

#endif //COMPILER_ATTR_RULE_DECL_H
