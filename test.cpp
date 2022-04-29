//
// Created by zlz on 22-4-26.
//
#include <iostream>
#include <memory>
#include "compiler.h"
class A{
    virtual void f(){}
};

class B:public A{

};
class C:public A{};

int main(){

    while (true){
        char c;
        std::cin>>c;
        if(std::cin.eof()) break;
        std::cout<<c;
    }
    return 0;
}