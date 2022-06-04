//
// Created by lzy on 22-5-15.
//

#ifndef COMPILER_GEN_CODE_ASSIGN_HPP
#define COMPILER_GEN_CODE_ASSIGN_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

//assignment_expr->unary_expr assignment_operator assignment_expr
class gen_code_assign : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::assignment_expr>(tree_node);

        auto assignVal = tree_node_genCode(p->children[2], context);
        if(p->children[2]->lValue){
            assignVal=context.builder->CreateLoad(assignVal);
        }
        auto id = tree_node_genCode(p->children[0], context);
        
        //only handle the "="
        context.builder->CreateStore(assignVal, id);
        return assignVal;
    }
};

#endif 
