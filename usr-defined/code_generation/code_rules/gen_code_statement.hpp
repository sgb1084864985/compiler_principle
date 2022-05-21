//
// Created by lzy on 22-5-18.
//

#ifndef COMPILER_GEN_CODE_STATEMENT_HPP
#define COMPILER_GEN_CODE_STATEMENT_HPP
#include "code_gen_productionInfo.h"
#include "Csymbols.hpp"

// statement->labeled_statement
// statement->compound_statement
// statement->expression_statement
// statement->selection_statement
// statement->iteration_statement
// statement->jump_statement

class gen_code_statement : public code_gen_productionInfo
{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::statement>(tree_node);
        auto transform = tree_node_genCode(p->children[0], context);
        return transform;
    }
};

#endif
