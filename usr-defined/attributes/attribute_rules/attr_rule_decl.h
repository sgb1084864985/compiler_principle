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
        tree_node->type=tree_node->inherited_type;

        if(tree_node->inheritedContext.isAbstractDeclare){ return;}
		auto id = std::dynamic_pointer_cast<TerminalValue>(tree_node->children[0]);
		std::string identifier = id->getText();
        tree_node->identifier=identifier;
		auto name_item = std::make_shared<CNameSpace::name_item>(tree_node->inherited_type);

        ptr_name exist;
        if(name_item->type->isFunction()){
            exist=context.currentNameSpace->get(identifier);
        }
        else{
            exist=context.currentNameSpace->getLocal(identifier);
        }

		if (!exist) {
            if(name_item->type->isFunction()){
                name_item->func= std::make_shared<func_item>();
                context.currentNameSpace->insert(identifier, name_item, false);
            }
            else{
                if(context.inGlobal()){
                    name_item->type->setStorageSpecifier(CTS::STATIC);
                }
                context.currentNameSpace->insert(identifier, name_item);
            }

		} else {
            if(!exist->isDeclaration()){
                emitError(context,tree_node,"Identifier redefined!");
            }
            if(!exist->type->equals(name_item->type)){
                emitError(context,tree_node,"Redeclaration of different type");
            }
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
        direct_decl->inheritedContext=tree_node->inheritedContext;
		direct_decl->getAttr().FillAttributes(context, direct_decl);
        tree_node->identifier=direct_decl->identifier;
	}
};

//direct_declarator->direct_declarator ( parameter_type_list )
class AttrRuleDirectDeclFuncWithPara : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto param_list = tree_node->children[2];
        param_list->inheritedContext=tree_node->inheritedContext;
        if(param_list->inheritedContext.isDeclare){
            param_list->inheritedContext.isAbstractDeclare= true;
        }
		param_list->getAttr().FillAttributes(context, param_list);
		auto params = param_list->params;
		auto new_type = C_type::newFuncType(tree_node->inherited_type, params);
		auto direct_decl = tree_node->children[0];
		direct_decl->inherited_type = new_type;
		direct_decl->getAttr().FillAttributes(context, direct_decl);
        tree_node->identifier=direct_decl->identifier;
	}
};

//direct_declarator->direct_declarator [ assignment_expr ]
class AttrRuleDirectDeclArray1 : public AttrRule {
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto expr = tree_node->children[2];
        expr->getAttr().FillAttributes(context, expr);
        if(!expr->constant){
            emitError(context,tree_node,"Array size must be constant!");
            return;
        }
        unsigned size=expr->constant->getUnsigned();
        tree_node->inherited_type->toArray(size);
        auto new_type=tree_node->inherited_type;
        auto direct_decl = tree_node->children[0];
        direct_decl->inherited_type = new_type;
        direct_decl->inheritedContext=tree_node->inheritedContext;
        direct_decl->getAttr().FillAttributes(context, direct_decl);
        tree_node->identifier=direct_decl->identifier;
    }
};


//declarator->direct_declarator
class AttrRuleDeclDirectDecl : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto direct_decl = tree_node->children[0];
		direct_decl->inherited_type = tree_node->inherited_type;
        direct_decl->inheritedContext=tree_node->inheritedContext;
		direct_decl->getAttr().FillAttributes(context, direct_decl);
		tree_node->type = direct_decl->type;
        tree_node->identifier=direct_decl->identifier;
	}
};

//declarator->pointer direct_declarator
class AttrRuleDeclDirectDeclPointer : public AttrRule {
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto pointer=tree_node->children[0];
        pointer->inherited_type=tree_node->inherited_type;
        pointer->getAttr().FillAttributes(context,pointer);

        auto direct_decl = tree_node->children[1];
        direct_decl->inherited_type = pointer->type;
        direct_decl->inheritedContext=tree_node->inheritedContext;
        direct_decl->getAttr().FillAttributes(context, direct_decl);

        tree_node->type = direct_decl->type;
        tree_node->identifier=direct_decl->identifier;
    }
};

//init_declarator->declarator
class AttrRuleInitDecl : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto decl = tree_node->children[0];
		decl->inherited_type = tree_node->inherited_type->clone();
        decl->inheritedContext=tree_node->inheritedContext;
		decl->getAttr().FillAttributes(context, decl);
        tree_node->identifier=decl->identifier;
	}
};

//init_declarator_list->init_declarator
class AttrRuleInitList : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto init_decl = tree_node->children[0];
		init_decl->inherited_type = tree_node->inherited_type;
        init_decl->inheritedContext=tree_node->inheritedContext;
		init_decl->getAttr().FillAttributes(context, init_decl);
	}
};

//init_declarator_list->init_declarator_list , init_declarator
class AttrRuleInitListMulti : public AttrRule {
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto list_head=tree_node->children[0];
        list_head->inherited_type=tree_node->inherited_type;
        list_head->inheritedContext=tree_node->inheritedContext;
        list_head->getAttr().FillAttributes(context,list_head);

        auto init_decl = tree_node->children[2];
        init_decl->inherited_type = tree_node->inherited_type;
        init_decl->inheritedContext=init_decl->inheritedContext;
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
        init_decl_list->inheritedContext=tree_node->inheritedContext;
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

//pointer->*
class AttrRulePointer1:public AttrRule{
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto t=(tree_node->type=tree_node->inherited_type);
        t->getDeclarator()->pointers.quantifiers.push_back(CTS::NONE);
    }
};

//pointer->* pointer
class AttrRulePointer2:public AttrRule{
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        auto t=(tree_node->type=tree_node->inherited_type);
        t->getDeclarator()->pointers.quantifiers.push_back(CTS::NONE);
        auto next_pointer=tree_node->children[0];
        next_pointer->inherited_type=t;
        next_pointer->getAttr().FillAttributes(context,next_pointer);
    }
};

#endif //COMPILER_ATTR_RULE_DECL_H
