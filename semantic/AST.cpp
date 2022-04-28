//
// Created by zlz on 22-4-27.
//

#include "AST.h"
namespace AST{
    bool leafOrNotLeaf(symbol_ptr& src,leafPtr& l,nLeafPtr& nl){
        nl= std::dynamic_pointer_cast<NonTerminal>(src);
        if(nl){
            return false;
        }

        l= std::dynamic_pointer_cast<TerminalValue>(src);
        return true;
    }
}


