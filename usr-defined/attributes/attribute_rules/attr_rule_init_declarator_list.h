//
// Created by zlz on 22-5-20.
//

#ifndef COMPILER_ATTR_RULE_INIT_DECLARATOR_LIST_H
#define COMPILER_ATTR_RULE_INIT_DECLARATOR_LIST_H

#include "attr_rule.hpp"

class declaration_system :public AttrRule{
public:
    virtual void visit(ptrType &type, symbol_ptr &node, AttrContext &context)=0;
    virtual const char* getID(){
        throw std::logic_error("getID not implemented");
    }
};


//init_declarator_list->init_declarator
//init_declarator_list->init_declarator_list , init_declarator
class attr_rule_init_declarator_list : public declaration_system{
public:
    // add variable to namespace
    // check initializer expression
    void visit(ptrType& type,symbol_ptr& node,AttrContext&context)override{
        auto p= std::dynamic_pointer_cast<CSym::init_declarator_list>(node);
        p->owner=context.currentNameSpace;

        for(int i=0;i<p->children.size();i+=2/* skip ',' */){
            auto& child_rule= getAttr<declaration_system>(p->children[i]);
            child_rule.visit(type,p->children[i],context);
        }

    }
};

//init_declarator->declarator
class init_declarator1 : public declaration_system{
public:
    // add variable to namespace
    // check initializer expression
    void visit(ptrType& type,symbol_ptr& node,AttrContext&context) override{
        auto p= std::dynamic_pointer_cast<CSym::init_declarator_list>(node);
        p->owner=context.currentNameSpace;

        auto& child_rule= getAttr<declaration_system>(p->children[0]);
        child_rule.visit(type,node,context);

        auto child_type=child_rule.GetType(p->children[0]);
        auto merged_type=C_type::newMergeType(type->getDeclarationSpecifiers(),child_type->getDeclarator());

        ptr_name name= std::make_shared<CNameSpace::name_item>(merged_type);
        context.currentNameSpace->insert(child_rule.getID(), name);
    }
};

//declarator->direct_declarator
class declarator1 : public declaration_system{
public:
    // add variable to namespace
    // check initializer expression
    void visit(ptrType& type,symbol_ptr& node,AttrContext&context) override{
        auto p= std::dynamic_pointer_cast<CSym::init_declarator_list>(node);
        p->owner=context.currentNameSpace;

        auto& child_rule= getAttr<declaration_system>(p->children[0]);
        child_rule.visit(type,node,context);

        m_type=child_rule.GetType(p->children[0]);
        id=child_rule.getID();
    }

    ptrType GetType(symbol_ptr &node)override{
        return m_type;
    }
    const char * getID()override{
        if(!id) throw std::logic_error("id null");
        return id;
    }

private:
    ptrType m_type;
    const char* id= nullptr;
};

//direct_declarator->id
class direct_declarator1 : public declaration_system{
public:
    // add variable to namespace
    // check initializer expression
    void visit(ptrType& type,symbol_ptr& node,AttrContext&context) override{
        auto p= std::dynamic_pointer_cast<CSym::init_declarator_list>(node);
        p->owner=context.currentNameSpace;

        auto child= std::dynamic_pointer_cast<TerminalValue>(p->children[0]);
        id=child->getText();
    }

    ptrType GetType(symbol_ptr &node)override{
        return C_type::newIncompleteType();
    }

    const char * getID()override{
        if(!id) throw std::logic_error("id null");
        return id;
    }
private:
    const char* id= nullptr;
};

#endif //COMPILER_ATTR_RULE_INIT_DECLARATOR_LIST_H
