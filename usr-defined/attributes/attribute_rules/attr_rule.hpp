//
// Created by zlz on 22-5-16.
//

#ifndef COMPILER_ATTR_RULE_EXPR_H
#define COMPILER_ATTR_RULE_EXPR_H

#include "ProductionInfo.h"
#include "AttrContext.h"

class AttrRule:public ProductionInfo{
public:
    virtual void fillAttributes(AttrContext& context, symbol_ptr& tree_node)=0;

    static void fillAttributes(ProductionInfo& info,AttrContext& context,symbol_ptr& tree_node){
        auto&attr_info =dynamic_cast<AttrRule&>(info);
        return attr_info.fillAttributes(context,tree_node);
    }

    static void tree_node_fillAttributes(AttrContext& context, symbol_ptr& tree_node){
        auto item= std::dynamic_pointer_cast<AST::NonTerminal>(tree_node);
        return fillAttributes(item->production.getAttrs(),context,tree_node);
    }
};

#endif //COMPILER_ATTR_RULE_EXPR_H
