#include "compiler.h"
#include "Productions.h"
#include <vector>
#include <iostream>
#include <memory>

using std::vector;

vector<Production> &Productions::getProductions(){
    productions.emplace_back("exp","exp addop term",[](symbol_iterator &,Context&){
        std::cout<<":exp addop term"<<std::endl;
        return std::make_shared<SymbolValue>();
    });

    productions.emplace_back("exp","term",[](symbol_iterator&it,Context&con){
        std::cout<<":term"<<std::endl;
        return std::make_shared<SymbolValue>();

    });

    productions.emplace_back("term","term mulop factor",[](symbol_iterator&it,Context&con){
        std::cout<<":term mulop factor"<<std::endl;
        return std::make_shared<SymbolValue>();

    });

    productions.emplace_back("term","factor",[](symbol_iterator&it,Context&con){
        std::cout<<":factor"<<std::endl;
        return std::make_shared<SymbolValue>();
    });

    productions.emplace_back("factor","integer",[](symbol_iterator&it,Context&con){
        std::cout<<":integer"<<std::endl;
        return std::make_shared<SymbolValue>();
    });

    productions.emplace_back("factor","( exp )",[](symbol_iterator&it,Context&con){
        std::cout<<"(exp)"<<std::endl;
        return std::make_shared<SymbolValue>();
    });

    productions.emplace_back("addop","+",[](symbol_iterator&it,Context&con){
        std::cout<<"+"<<std::endl;
        return std::make_shared<SymbolValue>();
    });

    productions.emplace_back("addop","-",[](symbol_iterator&it,Context&con){
        std::cout<<"-"<<std::endl;
        return std::make_shared<SymbolValue>();
    });

    productions.emplace_back("mulop","*",[](symbol_iterator&it,Context&con){
        std::cout<<"*"<<std::endl;
        return std::make_shared<SymbolValue>();
    });

    productions.emplace_back("mulop","/",[](symbol_iterator&it,Context&con){
        std::cout<<"/"<<std::endl;
        return std::make_shared<SymbolValue>();

    });

    return productions;
}