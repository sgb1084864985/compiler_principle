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
#include <utility>
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
        static constexpr int NO_ALLOC=-1;
        ptrType type;

        // empty if no initializer
        ptr_constant initializer;

        // empty if it is not a function
        ptr_func func;

        // empty if extern
        // else it is the alloc order in current namespace
        int alloc_order=NO_ALLOC;

        //        dType dt=dType::SIGNED_INTEGER;
        //        unsigned char dTypeSize{}; // use byte, eg. 1,2,4,8

        name_item(ptrType& type,int alloc_order,ptr_constant initializer={}):type(type),alloc_order(alloc_order),initializer(std::move(initializer)){}
        name_item(ptrType& type,ptr_func& f):type(type),func(f){}

        bool hasInitValue(){return ~!initializer;}
        bool hasFuncDefinition(){return type->isFunction() && ~!func;};
        void setFuncDefinition(ptr_func& ptrFunc){ this->func=ptrFunc;}
        [[nodiscard]] bool getAllocOrder() const{return alloc_order;}
        [[nodiscard]] ptrType getType() const{return type;}
    };

    using ptr_name=std::shared_ptr<name_item>;

public:
    // this list would follow the declaration order
    const vector<string>& getDeclarationList(){return declaration_list;};

    ptr_name get(string& name); // if not found, goto parent name_table
    // can only change local name_table
    void insert(string& name,ptr_name& val);
    void remove(string& name);

    explicit CNameSpace(symbol_ptr& tree_node, ptrNamespace parent={});

private:
    // follows the order of declaration
    vector<string> declaration_list;

    // corresponding ast tree
    symbol_ptr tree_node;

    std::unordered_map<std::string ,ptr_name> name_table;

    // empty if it is root name space(that is, global namespace)
    ptrNamespace parentNamespace;

//    std::list<ptrCNamespace> subNamespaces;
};

using ptrCNamespace = std::shared_ptr<CNameSpace>;
using ptr_name=std::shared_ptr<CNameSpace::name_item>;

#endif //COMPILER_CNAMESPACE_H
