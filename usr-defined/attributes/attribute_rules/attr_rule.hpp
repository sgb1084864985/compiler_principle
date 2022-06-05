//
// Created by zlz on 22-5-16.
//

#ifndef COMPILER_ATTR_RULE_H
#define COMPILER_ATTR_RULE_H

#include "ProductionInfo.h"
#include "AttrContext.h"
#include <stdexcept>

class AttrException:public std::logic_error{
public:
    explicit AttrException(const string &arg) : logic_error(arg) {}
};
class NoAttrException:public std::logic_error{
public:
    explicit NoAttrException(const string &arg) : logic_error(arg) {}
};

class AttrRule:public ProductionInfo{
public:
	virtual void FillAttributes (AttrContext& context, symbol_ptr& tree_node){
        std::cout<<"In production:"<<std::endl;
        std::cout<<tree_node->production.left_hand_side<<" -> "<<tree_node->production.right_hand_side<<std::endl;
        throw std::logic_error("Method FillAttributes is not implemented");
    }
    static void emitError(AttrContext&context,symbol_ptr& tree_node,const string& error){
        context.global.error= true;
        tree_node->error= true;
        context.global.error_out<<error<<std::endl;
        throw AttrException(error);
    }
    static void CheckType_(symbol_ptr &op1, symbol_ptr &op2, AttrContext &context,
                           symbol_ptr &tree_node) {
        if(op1->type->equals(op2->type)) return;
        if(C_type::implicitlyConvertable(op1->type,op2->type)){
            if(C_type::StrongerThan(*op1->type,*op2->type)){
                op2->implicit_cast_type=op1->type;
            }
            else{
                op1->implicit_cast_type=op2->type;
            }
        }
        else{
            emitError(context,tree_node,"Type Conversion Failed");
        }
    }
};

/**
 * In this attribute rule, we don't need any information about the lhs of the
 * production rule, so we don't calculate them and leave them as default
 */
class AttrRuleDoNothing : public AttrRule {
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        try{
            tree_node->owner = context.currentNameSpace;
            for (auto& child : tree_node->children) {
                try{
                    child->inheritedContext=tree_node->inheritedContext;
                    child->getAttr().FillAttributes(context, child);
                }
                catch (NoAttrException&e){}
            }
        }
        catch (AttrException&e){
            tree_node->error= true;
            if(throw_except){
                throw e;
            }
        }
	}
public:
    AttrRuleDoNothing()=default;
    explicit AttrRuleDoNothing(bool throw_except):throw_except(throw_except){}
private:
    bool throw_except= true;
};

class AttrRuleSetDeclare : public AttrRule {
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        tree_node->owner = context.currentNameSpace;
        for (auto& child : tree_node->children) {
            try{
                child->inheritedContext=tree_node->inheritedContext;
                child->inheritedContext.isDeclare= true;
                child->getAttr().FillAttributes(context, child);
            }
            catch (NoAttrException&e){}
        }
    }
};

class AttrRuleError : public AttrRule {
public:
	void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
        emitError(context,tree_node,"Error Syntax");
	}
};

class AttrRuleNull : public AttrRule {
public:
    void FillAttributes(AttrContext &context, symbol_ptr &tree_node) override {
    }
};

#endif //COMPILER_ATTR_RULE_H
