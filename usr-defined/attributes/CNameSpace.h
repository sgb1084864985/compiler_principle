//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CNAMESPACE_H
#define COMPILER_CNAMESPACE_H

#include "C_type.h"
#include "Csymbols.hpp"
#include "C_constant.h"
#include "NameSpace.h"
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <unordered_map>

using std::string;
using CTS::ptr_func;
using CTS::ptr_struct;
using CTS::func_item;
using CTS::struct_item;

class CNameSpace: public NameSpace{
public:
    using ptrNamespace = std::shared_ptr<CNameSpace>;

    struct name_item{
        ptrType type;
//        dType dt=dType::SIGNED_INTEGER;
//        unsigned char dTypeSize{}; // use byte, eg. 1,2,4,8

        unsigned char isConstant{};
        unsigned char isFunc{};
        union {
            ptr_func func; // empty if not function
            ptr_constant constant; // empty if not constant;
        };
    };

    using ptr_name=std::shared_ptr<name_item>;

public:
    const vector<string>& getDeclarationList(){return declaration_list;};
    ptr_name get(string& name); // if not found, goto parent name_table
    // can only change local name_table
    void insert(string& name,ptr_name& val);
    void remove(string& name);

    explicit CNameSpace(symbol_ptr& tree_node, ptrNamespace parent={});
private:
    // follow the order of declaration
    vector<string > declaration_list;

    // corresponding ast tree
    symbol_ptr tree_node;

    std::unordered_map<std::string ,ptr_name > name_table;

    // empty if it is root name space(that is, global namespace)
    ptrNamespace parentNamespace;

//    std::list<ptrCNamespace> subNamespaces;
};

using ptrCNamespace = std::shared_ptr<CNameSpace>;
using ptr_name=std::shared_ptr<CNameSpace::name_item>;

#endif //COMPILER_CNAMESPACE_H
