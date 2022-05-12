//
// Created by zlz on 22-5-12.
//

#ifndef COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
#define COMPILER_GEN_CODE_RULE_ADDEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

class gen_code_rule_addExpr:public code_gen_productionInfo{
    Value * genCode(code_gen_Context &context, symbol_ptr &tree_node) override{
        auto p= std::dynamic_pointer_cast<CSym::add_expr>(tree_node);
        if(p->constant){
            return genCodeForConstant(p->constant,context,tree_node);
        }
        auto v1= tree_node_genCode(p->children[0],context);
        auto v2= tree_node_genCode(p->children[1],context);
        return context.builder->CreateAdd(v1,v2,"add");
    }
};

#endif //COMPILER_GEN_CODE_RULE_ADDEXPR_HPP