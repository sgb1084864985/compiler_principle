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
    int constexpr NONE=0;
    enum StorageSpecifier{
        storage_unset,
        STATIC=0X1,
        EXTERN=0X2,
        THREAD_LOCAL=0X4,
        AUTO=0X8,
        REGISTER=0X10,
    };

    enum TypeSpecifier{
        type_unset,
        VOID=1,CHAR,SHORT,INT,
        LONG,LONGLONG,FLOAT,
        DOUBLE,BOOL,COMPLEX,
        IMAGINARY,STRUCT,UNION,

        // not implemented now
        ENUM,
    };

    enum TypeQuantifier{
        CONST=0X1,
        RESTRICT=0X2,
        VOLATILE=0X4,
        ATOMIC=0X8
    };

    enum FunctionSpecifier{
        INLINE=1,NO_RETURN
    };
    class Alignment{};
    class AtomicItem{};

    struct func_item{
        ptrAbstractNameSpace func_namespace;
        // body is empty is not defined
        std::shared_ptr<CSym::compound_statement> body;
    public:
        [[nodiscard]] bool idDefined() const{
            return body!= nullptr;
        }
    };
    using ptr_func = std::shared_ptr<func_item>;

    // union or struct
    struct struct_item{
        std::string name;
        ptrAbstractNameSpace struct_namespace;

        bool operator==(struct_item& other) const{
            return name==other.name && struct_namespace.get()==other.struct_namespace.get();
        }
        bool operator!=(struct_item& other) const{
            return name!=other.name || struct_namespace.get()!=other.struct_namespace.get();
        }
    };

    using ptr_struct = std::shared_ptr<struct_item>;

    class DeclarationSpecifiers{
    public:
        CTS::TypeSpecifier typeSpecifier=CTS::type_unset;
        CTS::StorageSpecifier storageSpecifier=CTS::storage_unset;
        int typeQuantifier=CTS::NONE;
        int funcSpecifier=CTS::NONE;
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
        bool ellipse= false;

        Parameters(vector<ptrType> & list,bool ellipse):param_list(list),ellipse(ellipse){
        }
        Parameters()=default;
        bool operator==(Parameters& other)const;
        bool operator!=(Parameters& other)const{return !(*this==other);}

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
        vector<unsigned int > arraySizes;

        bool operator==(AbstractDeclarator& other)const;
        bool operator!=(AbstractDeclarator& other)const{return !(*this==other);}

    };
    using ptrDelclarator=std::shared_ptr<AbstractDeclarator>;
}

class C_type{
public:

    static ptrType newIncompleteType();
    static ptrType newIncompleteType(bool Signed);
    static ptrType newIncompleteType(CTS::StorageSpecifier specifier);
    static ptrType newConstIncompleteType(int quantifier);
    static ptrType newFuncIncompleteType(int functionSpecifier);

    static ptrType newFuncDeclarator(CTS::ptrParams& params);
    static ptrType newFuncDeclarator(vector<ptrType>& param_list,bool variable_length= false);
    static ptrType newArrayDeclarator(unsigned int dim,vector<unsigned int>& arraySizes);

    static ptrType newMergeType(CTS::DeclarationSpecifiers& part1,CTS::ptrDelclarator& part2);

    // Signed is valid only if type is char,short,int,long,longlong
    static ptrType newBasicType(CTS::TypeSpecifier type,bool Signed= true,CTS::StorageSpecifier storage=CTS::AUTO,int quantifier=CTS::NONE);
    static ptrType newStructType(CTS::ptr_struct& struct_item,CTS::StorageSpecifier storage=CTS::AUTO,int quantifier=CTS::NONE);
    static ptrType newUnionType(CTS::ptr_struct& struct_item,CTS::StorageSpecifier storage=CTS::AUTO,int quantifier=CTS::NONE);

    static ptrType newFuncType(ptrType& retType,
                               vector<ptrType>& param_list,
                               CTS::StorageSpecifier storage=CTS::EXTERN,
                               int functionSpecifier=CTS::NONE,
                               bool variable_length= false);

    static ptrType newFuncType(ptrType& retType,
                               CTS::ptrParams& params,
                               CTS::StorageSpecifier storage=CTS::EXTERN,
                               int functionSpecifier=CTS::NONE);

    static ptrType newArrayType(ptrType& basicType,
                                unsigned int dim,
                                vector<unsigned int>& arraySizes,
                                CTS::StorageSpecifier storage=CTS::AUTO,
                                int quantifier=CTS::NONE
                                );

    // make int* from int, but a new copy. See also addPointer
    ptrType newPointerType(int pointer_quantifier=CTS::NONE);
    ptrType clone();

    // sizeof this type (byte)
    unsigned int size();

    // make int* from int
    void addPointer(int pointer_quantifier=CTS::NONE);
    void toArray(unsigned int new_size);
    void toArray(const vector<int>& new_sizes);

    void setStorageSpecifier(CTS::StorageSpecifier specifier);
    void setTypeSpecifier(CTS::TypeSpecifier specifier);
    void setTypeQuantifier(CTS::TypeSpecifier quantifier);
    void setPointerTypeQuantifier(CTS::TypeSpecifier quantifier,int pointer_level=0);

    // for struct and union types, type1.equals(type2) requires namespaces are same
    bool equals(ptrType& other);
    bool const_equals(ptrType& other);

    bool isFunction(){
        if(!declarator->params){
            return false;
        }
        if(isPointer()){
            return false;
        }
        if(isArray()){
            return false;
        }
        return true;
    };
    bool isPointer(){return declarator->pointers.size()>0;}
    bool isStruct(){return getTypeSpecifier()==CTS::STRUCT;}
    bool isUnion(){return getTypeSpecifier()==CTS::UNION;}
    bool isArray(){return declarator->arrayDim>0;}

    // int,float,...
    bool isBasicType(){
        return !isPointer() && !isFunction() && !isStruct() && !isUnion() &&!isArray();
    }
    bool isSigned(){
        return getDeclarationSpecifiers().isSigned;
    }

    CTS::TypeSpecifier getTypeSpecifier(){
        return getDeclarationSpecifiers().typeSpecifier;
    };
    CTS::StorageSpecifier getStorageSpecifier(){
        return getDeclarationSpecifiers().storageSpecifier;
    }
    int getTypeQuantifier(){return getDeclarationSpecifiers().typeQuantifier;}
    int getFunctionSpecifier(){return getDeclarationSpecifiers().funcSpecifier;}

    int getArrayDim(){return declarator->arrayDim;}
    const vector<unsigned int>& getArraySizes(){return declarator->arraySizes;}

    const vector<int>& getPointerQuantifiers(){return declarator->pointers.quantifiers;}

    ptrType getReturnType();
    CTS::ptrParams getParameterTypes(){return  declarator->params;}

    CTS::DeclarationSpecifiers& getDeclarationSpecifiers(){return declarationSpecifiers;}
    CTS::ptrDelclarator& getDeclarator(){return declarator;}
private:
    CTS::DeclarationSpecifiers declarationSpecifiers;
    CTS::ptrDelclarator declarator;

    friend class C_constant;
};


#endif //COMPILER_C_TYPE_H
