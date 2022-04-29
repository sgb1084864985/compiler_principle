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

    void handle_dot_escape(std::ostream& out,symbol_ptr&root){
        std::stringstream buf;
        root->print(buf);
        for(char c:buf.str()){
            switch (c) {
                case '\"': out<<R"(\")";
                    break;
                case '\n': out<<R"(\n)";
                    break;
                default: out<<c;
                    break;
            }
        }
    }

    void AST_Printer::_print(unsigned int ord, symbol_ptr&root){
        nLeafPtr nl;
        leafPtr l;

        out<<"\tn"<<ord<<"[label=\"";
        handle_dot_escape(out,root);
        out<<"\"]"<<std::endl;

        if(leafOrNotLeaf(root,l,nl)){
            return;
        }

        unsigned int old_cnt=cnt;
        cnt+=nl->children.size();
        out<<"\tn"<<ord<<"--{ ";
        for(unsigned int i=old_cnt;i<cnt;i++){
            out<<"n"<<i<<" ";
        }
        out<<"}"<<std::endl;

        for(auto&item:nl->children){
            _print(old_cnt++,item);
        }
    }
}


