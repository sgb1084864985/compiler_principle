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
#include "CSymbolTable.h"
#include "codeGenerator.h"

// FP type arithmetic
// implicit cast
// error catch
// initializer
// ++, --

using namespace std;
int main(){
    cout<<"Compiling C file..."<<endl;
    MyParser parser(CProductions::getAndAdd());
    Context c;

    CTokenTable table;
    Scanner2 scanner2(cin>>std::noskipws,table.getTokenTable());
    CTokenActions actions;
    TokenContext tokenContext;

    TokenInput input(actions,scanner2,tokenContext);
    symbol_ptr result=parser.parse(input,c);

    fstream file("out.dot",ios::out);
    AST::AST_Printer printer(file);
    printer.print(result);
    file.close();

    GlobalContext context(cout,"main.ll");
    try{
        auto Stable=CSymbolTable::genSymbolTable(result,context);
        codeGenerator::genCode(Stable,result,context);
        cout<<"Compile success"<<endl;
    }
    catch (logic_error&e){
        cout<<e.what()<<endl;
    }
    catch(exception&e){
        cout<<"unknown error"<<endl;
        cout<<e.what()<<endl;
    }

    return 0;
}
