//
// Created by zlz on 2022/3/15.
//
#include <iostream>
#include "MyParser.hpp"
#include "Productions.h"
#include "compiler.h"
#include "TokenInput.h"

using namespace std;
int main(){
    cout<<"This is main file"<<endl;
    Productions p;
    MyParser parser(p.getProductions());
    Context c;
    TokenInput input;
    parser.parse(input,c);
    return 0;
}