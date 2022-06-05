//
// Created by zlz on 22-5-5.
//

#include "C_constant.h"

ptr_constant C_constant::getBoolConstant(bool boolean) {
    return std::make_shared<ConstantSingleElement<bool>>(boolean);
}

ptr_constant C_constant::newArray(vector<ptr_constant> &constants) noexcept {
    return {};
}

ptr_constant C_constant::newStruct(vector<ptr_constant> &constants) noexcept {
    return {};
}

using std::string;
string fromRawString(const string& str){
    string ret;
    for(int i=1;i<str.size()-1;i++){
        char c=str[i];
        if(c=='\\'){
            i++;
            switch (str[i]) {
                case 'n':ret.push_back('\n');
                    break;
                case 't':ret.push_back('\t');
                    break;
                case '\\':ret.push_back('\\');
                    break;
                case '\'':ret.push_back('\'');
                    break;
                case '\"':ret.push_back('\"');
                    break;
                case 'r':ret.push_back('\t');
                    break;
                case 'f':ret.push_back('\f');
                    break;
                case 'v':ret.push_back('\v');
                    break;
                case 'a':ret.push_back('\a');
                    break;
                case 'b':ret.push_back('\b');
                    break;
                case '?':ret.push_back('\?');
                    break;
                default:
                    throw std::logic_error("invalid escape");
            }
        }
        else{
            ret.push_back(c);
        }
    }
    return ret;
}

ptr_constant C_constant::fromString(std::string &str, TokenType type) noexcept {
    ptr_constant ret;
    switch (type) {
        case TokenType::INTEGER:
            ret=C_constant::newConstant(atoi(str.c_str()));
            break;
        case TokenType::FLOAT:
            ret=C_constant::newConstant(atof(str.c_str()));
            break;
        case TokenType::STRING:
            ret= std::make_shared<ConstantString>(fromRawString(str));
        default:
            break;
    }
    return ret;
}

ptr_constant C_constant::newAdd(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_add(op2);
}

ptr_constant C_constant::newMul(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_mul(op2);
}

ptr_constant C_constant::newSub(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_sub(op2);
}

ptr_constant C_constant::newMinus(ptr_constant &op1) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_minus();
}

ptr_constant C_constant::newDiv(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_div(op2);
}

ptr_constant C_constant::newMod(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_mod(op2);
}

ptr_constant C_constant::newEQ(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_eq(op2);
}

ptr_constant C_constant::newNEQ(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_neq(op2);
}

ptr_constant C_constant::newLE(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_le(op2);
}

ptr_constant C_constant::newGE(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_ge(op2);
}

ptr_constant C_constant::newGT(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_gt(op2);
}

ptr_constant C_constant::newLT(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_lt(op2);
}

ptr_constant C_constant::newNOT(ptr_constant &op1) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_not();
}

ptr_constant C_constant::newLOGIC_OR(ptr_constant &op1, ptr_constant &op2){
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_logic_or(op2);
}
ptr_constant C_constant::newLOGIC_AND(ptr_constant &op1, ptr_constant &op2) {
    auto p=std::dynamic_pointer_cast<ConstantArithmetic>(op1);
    if(!p){
        throw std::logic_error("arithmetic operation not in supported for the type !");
    }
    return p->_logic_and(op2);
}