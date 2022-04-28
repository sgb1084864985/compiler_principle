//
// Created by zlz on 2022/3/15.
//
#include <iostream>
#include <fstream>
#include "MyParser.hpp"
#include "compiler.h"
#include "TokenInput.h"
#include "Csymbols.hpp"
#include "Scanner2.h"

#include "AST.h"

#include "CProductions.h"
#include "CTokenTable.h"
#include "CTokenActions.h"

using namespace std;
int main(){
    cout<<"This is main file"<<endl;
    MyParser parser(CProductions::getProductions());
    Context c;

    CTokenTable table;
    Scanner2 scanner2(cin,table.getTokenTable());
    CTokenActions actions;
    TokenContext tokenContext;

    TokenInput input(actions,scanner2,tokenContext);
    symbol_ptr result=parser.parse(input,c);

    fstream file("out.dot",ios::out);
    AST::AST_Printer printer(file);
    printer.print(result);
    file.close();
    return 0;
}
