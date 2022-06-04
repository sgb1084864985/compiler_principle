//
// Created by hansljy on 22-5-21.
//

#ifndef COMPILER_ATTR_RULE_FUNC_H
#define COMPILER_ATTR_RULE_FUNC_H

#include "attr_rule.hpp"

//function_definition->declaration_specifiers declarator compound_statement
class AttrRuleFunc : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
		tree_node->owner = context.currentNameSpace;
		auto decl_spec = tree_node->children[0];
		auto decl = tree_node->children[1];
		auto compound = tree_node->children[2];
		decl_spec->getAttr().FillAttributes(context, decl_spec);
		auto type = decl_spec->type;
		decl->inherited_type = type;
		auto old_namespace = context.currentNameSpace;
		context.currentNameSpace = std::make_shared<CNameSpace>(tree_node, context.currentNameSpace);
        decl->getAttr().FillAttributes(context, decl);
        compound->getAttr().FillAttributes(context, compound);
        auto func_item=context.currentNameSpace->get(decl->identifier);
//        context.currentNameSpace->remove(decl->identifier);
        if(func_item->func->idDefined()){
            tree_node->error = true;
            context.global.error_out << "function redefined!";
            return;
        }
        func_item->func->func_namespace=compound->owner;
        func_item->func->body=compound;
		context.currentNameSpace = old_namespace;
        // it must be global
        context.currentNameSpace->insert(decl->identifier,func_item, false);
	}

protected:
	ptrType m_type;
};

#endif //COMPILER_ATTR_RULE_FUNC_H
