//
// Created by zlz on 2022/3/15.
//
#include <iostream>
#include "MyParser.hpp"
#include "Productions.h"
#include "compiler.h"
#include "TokenInput.h"
#include "symbols.hpp"

using namespace std;
int main(){
    cout<<"This is main file"<<endl;
    Productions p;
    MyParser parser(p.getProductions());
    Context c;
    TokenInput input;
    symbol_ptr result=parser.parse(input,c);
    auto output= dynamic_pointer_cast<OperandInt>(result);
    cout<<output->getValue()<<endl;
    return 0;
}