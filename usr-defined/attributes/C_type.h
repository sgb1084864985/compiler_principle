//
// Created by zlz on 22-5-5.
//

#ifndef COMPILER_C_TYPE_H
#define COMPILER_C_TYPE_H

#include "Csymbols.hpp"
#include <memory>
#include <list>

using std::list;

class C_type;
using ptrType=std::shared_ptr<C_type>;
// C Type System
namespace CTS{
    enum StorageSpecifier{
        STATIC=0X1,
        EXTERN=0X2,
        THREAD_LOCAL=0X4,
        AUTO=0X8,
        REGISTER=0X10,
    };

    enum TypeSpecifier{
        VOID,CHAR,SHORT,INT,
        LONG,LONGLONG,FLOAT,
        DOUBLE,BOOL,COMPLEX,
        IMAGINARY,STRUCT,UNION,
        ENUM// not implemented now
    };

    enum TypeQuantifier{
        CONST=0X1,
        RESTRICT=0X2,
        VOLATILE=0X4,
        ATOMIC=0X8
    };

    enum FunctionSpecifier{
        INLINE,NO_RETURN
    };
    class Alignment{};
    class AtomicItem{};

    struct func_item{
        ptrAbstractNameSpace func_namespace;
        // body is empty is not defined
        std::shared_ptr<CSym::function_definition> body;
    };
    using ptr_func = std::shared_ptr<func_item>;

    // union or struct
    struct struct_item{
        std::string name;
        ptrAbstractNameSpace struct_namespace;
    };

    using ptr_struct = std::shared_ptr<struct_item>;

    class DeclarationSpecifiers{
    public:
        CTS::TypeSpecifier typeSpecifier=CTS::INT;
        int storageSpecifier=CTS::AUTO;
        int typeQuantifier=0;
        int funcSpecifier=0;
        bool isSigned= true;

        // if it is struct type
        ptr_struct structItem;

        CTS::Alignment alignment;// not used now
        CTS::AtomicItem atomicItem;// not used now
    };

    class Pointers{
    public:
        vector<int> quantifiers;
        [[nodiscard]] unsigned int size() const{return quantifiers.size();}
    };

    class Parameters{
    public:
        vector<ptrType> param_list;
        bool ellipse;
    };

    using ptrParams=std::shared_ptr<Parameters>;

    class AbstractDeclarator{
    public:
        Pointers pointers;
        // for function type. innerDeclarator is empty if not func
        using ptrDelclarator=std::shared_ptr<AbstractDeclarator>;
        ptrDelclarator innerDeclarator;
        ptrParams params;

        // for array type. Dim=0 if not an array
        int arrayDim{};
        vector<CSym::assignment_expr> arraySizes;
    };
    using ptrDelclarator=std::shared_ptr<AbstractDeclarator>;
}

class C_type{
public:
    CTS::DeclarationSpecifiers declarationSpecifiers;
    CTS::ptrDelclarator declarator;

    bool equals(ptrType& other);
    bool isFunction();
    bool isPointer();
    bool isStruct();
    bool isUnion();
    bool isBasicType();
};


#endif //COMPILER_C_TYPE_H
