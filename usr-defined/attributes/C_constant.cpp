//
// Created by zlz on 22-5-5.
//

#include "C_constant.h"
#include <cstring>

// @param dt: only accept SIGNED INTEGER,FLOAT,STRING, INTEGER may be converted to UNSIGNED INTEGER
ptr_constant C_constant::fromString(std::string &str, TokenType type)noexcept {
    ::ptr_constant ret;
    switch (type) {
        case TokenType::INTEGER:
            ret= std::make_shared<C_constant>(4,1,dType::SIGNED_INTEGER);
            *(int*)ret->data= atoi(str.c_str());
            break;
        case TokenType::FLOAT:
            ret= std::make_shared<C_constant>(8,1,dType::FLOAT);
            *(double *)ret->data= atof(str.c_str());
            break;
        case TokenType::STRING:
            ret= std::make_shared<C_constant>(1,str.length()+1,dType::FLOAT);
            memcpy(ret->data,str.c_str(),str.length());
            ret->data[str.length()]='\0';
            break;
        default:
            break;
    }
    return ret;
}


C_constant::C_constant(int bytes, int length, dType dt):bytes_per_unit(bytes),length(length),dt(dt),data(new unsigned char [bytes*length]){
}

