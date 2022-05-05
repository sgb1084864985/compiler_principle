//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_CNAMESPACE_H
#define COMPILER_CNAMESPACE_H

#include "C_type.h"
#include "Csymbols.hpp"
#include "C_constant.h"
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <unordered_map>

using std::string ;

class CNameSpace {
public:

    enum StorageProperty{
        STATIC_AUTO=0x1, // static: 1, auto:0
        EXTERN=0x2,
        REGISTER=0x4,
        Thread_Local=0x8,
    };

    using ptrNamespace = std::shared_ptr<CNameSpace>;

    struct func_item{
        ptrNamespace func_namespace;
        C_type ret_type;
        vector<C_type> arg_types;
        // body is empty is not defined
        std::shared_ptr<CSym::function_definition> body;
    };
    using ptr_func = std::shared_ptr<func_item>;

    struct name_item{
        C_type t;
        dType dt=dType::SIGNED_INTEGER;
        unsigned char dTypeSize{}; // use byte, eg. 1,2,4,8
        unsigned char storage_property{};
        unsigned char atomic{};

        unsigned char isConstant{};
        unsigned char isFunc{};
        ptr_func func; // empty if not function
    };

    using ptr_name=std::shared_ptr<name_item>;

public:
    ptr_name get(string& name); // if not found, goto parent name_table
    // can only change local name_table
    void insert(string& name,ptr_name& val);
    void remove(string& name);

private:
    std::unordered_map<std::string ,ptr_name > name_table;
    ptrNamespace parentNamespace;// empty if it is root name space(that is, global namespace)
//    std::list<ptrNamespace> subNamespaces;
};
using ptrNamespace = std::shared_ptr<CNameSpace>;
using ptr_func = std::shared_ptr<CNameSpace::func_item>;
using ptr_name=std::shared_ptr<CNameSpace::name_item>;


#endif //COMPILER_CNAMESPACE_H
