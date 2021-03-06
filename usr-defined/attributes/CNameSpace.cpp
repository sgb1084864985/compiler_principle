//
// Created by zlz on 22-5-5.
//

#include "CNameSpace.h"

#include <utility>

// if not found, return an empty pointer
CNameSpace::ptr_name CNameSpace::get(const string &name) {
    try{
        auto ret=name_table.at(name);
        return ret;
    }
    catch (std::out_of_range& ex){
        if(!parentNamespace){
            return {};// empty
        }
        else{
            return parentNamespace->get(name);
        }
    };
}

// if key has exists, overwrite it
void CNameSpace::insert(string& name, CNameSpace::ptr_name &val,bool alloc) {
    name_table[name]=val;
    if(alloc){
        val->alloc_order=allocated_number++;
    }
    declaration_list.push_back(name);
}

void CNameSpace::remove(string &name) {
    name_table.erase(name);
}

CNameSpace::CNameSpace(symbol_ptr &tree_node, CNameSpace::ptrNamespace parent)
        :tree_node(tree_node),parentNamespace(std::move(parent)) {

}

ptr_name CNameSpace::getLocal(const string &name) {
    try{
        auto ret=name_table.at(name);
        return ret;
    }
    catch (std::out_of_range& ex){
        return {};
    };
}
