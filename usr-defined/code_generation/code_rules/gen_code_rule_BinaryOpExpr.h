//
// Created by zlz on 22-6-5.
//

#ifndef COMPILER_GEN_CODE_RULE_BINARYOPEXPR_H
#define COMPILER_GEN_CODE_RULE_BINARYOPEXPR_H

// expr -> expr1 op expr2
class gen_code_BinaryExpr:public code_gen_productionInfo{
    Value *genCode(code_gen_Context &context, symbol_ptr &tree_node) override
    {
        auto p = std::dynamic_pointer_cast<CSym::add_expr>(tree_node);

        auto v1 = getRValue(p->children[0], context);
        auto v2 = getRValue(p->children[2], context);

        auto ret = operation(context,tree_node,p->children[0],p->children[1],v1,v2);

        return ret;
    }
    virtual Value* operation
        (code_gen_Context&context,symbol_ptr&tree_node,symbol_ptr&op1,symbol_ptr&op2,Value*v1,Value*v2)=0;
};

#endif //COMPILER_GEN_CODE_RULE_BINARYOPEXPR_H
