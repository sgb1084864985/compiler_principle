//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_JUMPEXPR_HPP
#define COMPILER_GEN_CODE_JUMPEXPR_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"


// jump_statement->goto id ;
// jump_statement->continue ;
// jump_statement->break ;
// jump_statement->return ;
// jump_statement->return expr ;

// jump_statement->return ;
class gen_code_jumpexpr1 : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        return context.builder->CreateRetVoid();
    }
};

// jump_statement->return expr ;
class gen_code_jumpexpr2: public code_gen_productionInfo
{
    Value* genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::jump_statement>(tree_node); 
        auto retV = tree_node_genCode(p->children[1], context);
        return context.builder->CreateRet(retV);
    }
}

#endif
