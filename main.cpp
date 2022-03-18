//
// Created by zlz on 2022/3/15.
//
#include <iostream>
#include "MyParser.hpp"
#include "Productions.h"

using namespace std;
int main(){
    cout<<"This is main file"<<endl;
    Productions p;
    MyParser parser(p.getProductions());
    return 0;
}