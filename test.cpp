//
// Created by zlz on 22-4-26.
//
#include <iostream>
#include <memory>

class Base{
public:
    virtual void f()=0;


};

namespace Name{
    template<class T>
    void f_impl(){}

    template<> void f_impl<int>(){
        std::cout<<"int !"<<std::endl;
    }
}

template <class T>
class Derive:public Base{
    void f() override{
        Name::f_impl<T>();
        good();
    }
    void good(){std::cout<<"good"<<std::endl;}
};

//template<>
//class Derive<int>{
//    void good(){
//        std::cout<<"special int good"<<std::endl;
//    }
//};

int main(){
    auto p= std::make_shared<Derive<int>>();
    std::shared_ptr<Base> pp=p;
    pp->f();
}