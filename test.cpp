//
// Created by zlz on 22-4-26.
//
#include <iostream>
#include <memory>

class A{
    virtual void f(){}
};

class B:public A{

};
class C:public A{};

int main(){
    auto c= std::make_shared<B>();
    std::shared_ptr<A> a=c;
    std::shared_ptr<B> b= std::dynamic_pointer_cast<B>(a);
    std::shared_ptr<C> e= std::dynamic_pointer_cast<C>(a);
    std::cout<<b.use_count()<<std::endl;
    if(e){
        std::cout<<e.use_count()<<std::endl;
    }
    return 0;
}