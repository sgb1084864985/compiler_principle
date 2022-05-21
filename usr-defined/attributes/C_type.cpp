//
// Created by zlz on 22-5-5.
//

#include "C_type.h"

ptrType C_type::newIncompleteType() {
    return std::make_shared<C_type>();
}

ptrType C_type::newIncompleteType(bool Signed) {
    auto ptr=std::make_shared<C_type>();
    ptr->getDeclarationSpecifiers().isSigned=Signed;
    return ptr;
}

ptrType C_type::newIncompleteType(CTS::StorageSpecifier specifier) {
    auto ptr=std::make_shared<C_type>();
    ptr->getDeclarationSpecifiers().storageSpecifier=specifier;
    return ptr;
}

ptrType C_type::newConstIncompleteType(int quantifier) {
    auto ptr=std::make_shared<C_type>();
    ptr->getDeclarationSpecifiers().typeQuantifier=quantifier;
    return ptr;
}

ptrType C_type::newFuncIncompleteType(int functionSpecifier) {
    auto ptr=std::make_shared<C_type>();
    ptr->getDeclarationSpecifiers().funcSpecifier=functionSpecifier;
    return ptr;
}

ptrType C_type::newFuncDeclarator(CTS::ptrParams &params) {
    auto ptr=std::make_shared<C_type>();
    auto declarator= std::make_shared<CTS::AbstractDeclarator>();
    declarator->params=params;
    ptr->declarator=declarator;
    return ptr;
}

ptrType C_type::newArrayDeclarator(unsigned int dim, vector<unsigned int> &arraySizes) {
    auto ptr=std::make_shared<C_type>();
    auto declarator= std::make_shared<CTS::AbstractDeclarator>();
    declarator->arrayDim=static_cast<int>(dim);
    declarator->arraySizes=arraySizes;
    ptr->declarator=declarator;
    return ptr;
}

ptrType C_type::newFuncDeclarator(vector<ptrType> &param_list, bool variable_length) {
    auto ptr=std::make_shared<C_type>();
    auto declarator= std::make_shared<CTS::AbstractDeclarator>();
    auto params= std::make_shared<CTS::Parameters>(param_list,variable_length);
    declarator->params=params;
    ptr->declarator=declarator;
    return ptr;
}

ptrType C_type::newMergeType(CTS::DeclarationSpecifiers &part1, CTS::ptrDelclarator &part2) {
    auto ptr=std::make_shared<C_type>();
    ptr->declarationSpecifiers=part1;
    ptr->declarator=part2;
    return ptr;
}

ptrType C_type::newBasicType(CTS::TypeSpecifier type, bool Signed, CTS::StorageSpecifier storage, int quantifier) {
    return {};
}

ptrType C_type::newStructType(CTS::ptr_struct &struct_item, CTS::StorageSpecifier storage, int quantifier) {
    return {};
}

ptrType C_type::newUnionType(CTS::ptr_struct &struct_item, CTS::StorageSpecifier storage, int quantifier) {
    return {};
}

ptrType
C_type::newFuncType(ptrType &retType, vector<ptrType> &param_list, CTS::StorageSpecifier storage, int functionSpecifier,
                    bool variable_length) {
    return {};
}

ptrType
C_type::newFuncType(ptrType &retType, CTS::ptrParams &params, CTS::StorageSpecifier storage, int functionSpecifier) {
    return {};
}

ptrType C_type::newArrayType(ptrType &basicType, unsigned int dim, vector<unsigned int> &arraySizes,
                             CTS::StorageSpecifier storage, int quantifier) {
    return {};
}

// TODO:
ptrType C_type::newPointerType(int pointer_quantifier) {
    return {};
}

// TODO:
ptrType C_type::clone() {
    return {};
}

unsigned int C_type::size() {
    if(declarator->pointers.size()>0){
        return sizeof(void *);
    }
    if(declarator->params){
        return sizeof(void *);
    }
    unsigned int basic_size=0;
    switch (getDeclarationSpecifiers().typeSpecifier) {
        case CTS::INT:basic_size=sizeof(int);
            break;
        case CTS::FLOAT:basic_size=sizeof(float );
            break;
        case CTS::DOUBLE:basic_size=sizeof(double );
            break;
        case CTS::LONG:basic_size=sizeof(long);
            break;
        case CTS::CHAR:basic_size=sizeof(char );
            break;
        case CTS::SHORT:basic_size=sizeof(short );
            break;
        case CTS::LONGLONG:basic_size=sizeof(long long);
            break;
        default:
            throw std::logic_error("invalid type do not have size");
    }
    if(declarator->arrayDim==0){return basic_size;}
    unsigned int array_size=basic_size;
    for(auto len : declarator->arraySizes){
        array_size*=len;
    }
    return array_size;
}

// TODO:
void C_type::addPointer(int pointer_quantifier) {

}

// TODO:
void C_type::setStorageSpecifier(CTS::StorageSpecifier specifier) {

}

// TODO:
void C_type::setTypeSpecifier(CTS::TypeSpecifier specifier) {

}

// TODO:
void C_type::setTypeQuantifier(CTS::TypeSpecifier quantifier) {

}

// TODO:
void C_type::setPointerTypeQuantifier(CTS::TypeSpecifier quantifier, int pointer_level) {

}

bool C_type::equals(ptrType &other) {
    auto& specifier1=getDeclarationSpecifiers();
    auto& specifier2=other->getDeclarationSpecifiers();
    auto& declarator1=getDeclarator();
    auto& declarator2=other->getDeclarator();

    if(specifier1.typeSpecifier!=specifier2.typeSpecifier){
        return false;
    }
    if(!specifier1.structItem && specifier2.structItem || specifier1.structItem && !specifier2.structItem){
        return false;
    }
    if(specifier1.structItem && specifier2.structItem && *specifier1.structItem!=*specifier2.structItem){
        return false;
    }

    if(declarator1 &&!declarator2 || declarator2&&!declarator1){
        return false;
    }

    if(!declarator1 && !declarator2){
        return true;
    }

    return *declarator1==*declarator2;
}

bool C_type::const_equals(ptrType &other) {
    return false;
}

// TODO:
ptrType C_type::getReturnType() {
    return newBasicType(getTypeSpecifier(),isSigned(),getStorageSpecifier(),getTypeQuantifier());
}

bool CTS::Parameters::operator==(CTS::Parameters &other)const{
    if(ellipse!=other.ellipse)return false;
    if(param_list.size()!=other.param_list.size()){
        return false;
    }
    for(int i=0;i<param_list.size();i++){
        if(!param_list[i]->equals(other.param_list[i])){
            return false;
        }
    }
    return true;
}

// TODO:
bool CTS::AbstractDeclarator::operator==(CTS::AbstractDeclarator &other) const {
    auto declarator1=this;
    auto declarator2=&other;

    if(declarator1->pointers.size()!=declarator2->pointers.size()){
        return false;
    }

    if(declarator1->arrayDim!=declarator2->arrayDim){
        return false;
    }

    if(declarator1->arraySizes!=declarator2->arraySizes){
        return false;
    }

    if(!declarator1->params && declarator2->params || declarator1->params && !declarator2->params){
        return false;
    }

    if(declarator1->params && declarator2->params && *(declarator1->params) == *(declarator2->params)){
        return false;
    }

    // inner function pointer

    return true;
}
