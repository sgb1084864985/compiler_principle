//
// Created by zlz on 22-5-12.
//

#ifndef COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
#define COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
#include "attr_rule.hpp"
#include "Csymbols.hpp"
#include "C_constant.h"

// add_expr -> add_expr + mul_expr
class AttrRule_addExpr1:public AttrRule{
    void fillAttributes(AttrContext &context, symbol_ptr &tree_node) override{
        auto p= std::dynamic_pointer_cast<CSym::add_expr>(tree_node);
        auto op1=std::dynamic_pointer_cast<CSym::add_expr>(p->children[0]);
        auto op2=std::dynamic_pointer_cast<CSym::mul_expr>(p->children[1]);

        // set namespace
        p->owner=context.currentNameSpace;
        
        // visit children
        tree_node_fillAttributes(context,p->children[0]);
        tree_node_fillAttributes(context,p->children[1]);
        
        // check type
        if(op1->type->equals(op2->type)){
            // calculate constant
            if(op1->constant && op2->constant){
                // assume it is int
                if(op1->type->isBasicType()){
                    switch (op1->type->getTypeSpecifier()) {
                        case CTS::BOOL:
                        case CTS::CHAR:
                        case CTS::SHORT:
                        case CTS::INT:
                        case CTS::LONG:
                        case CTS::LONGLONG:
                            if(op1->type->isSigned()){
                                p->constant=C_constant::newAdd<int,int>(op1->constant,op2->constant);
                            }
                            else{
                                p->constant=C_constant::newAdd<unsigned int,unsigned int >(op1->constant,op2->constant);
                            }
                        case CTS::DOUBLE:
                            p->constant=C_constant::newAdd<double,double>(op1->constant,op2->constant);
                        case CTS::FLOAT:
                        default:
                            break;
                    }
                }
            }
        }
        else{
            // continue to parent node
            context.global.error_out<<"error"<<std::endl;
            p->error= true;
            return;
        }
    }
};

#endif //COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
