#include "compiler.h"
#include "Productions.h"
#include "symbols.hpp"
#include <vector>
#include <iostream>
#include <memory>

using std::vector;

vector<Production> &Productions::getProductions(){
    productions.emplace_back("exp","exp addop term",[](symbol_iterator &it,Context&con){
        auto x1= std::dynamic_pointer_cast<Operand>(it.next());
        auto op= std::dynamic_pointer_cast<BinaryOperator>(it.next());
        auto x2= std::dynamic_pointer_cast<Operand>(it.next());
        return op->operator()(x1,x2);
    });

    productions.emplace_back("exp","term",[](symbol_iterator&it,Context&con){
        return it.next();
    });

    productions.emplace_back("term","term mulop factor",[](symbol_iterator&it,Context&con){
        auto x1= std::dynamic_pointer_cast<Operand>(it.next());
        auto op= std::dynamic_pointer_cast<BinaryOperator>(it.next());
        auto x2= std::dynamic_pointer_cast<Operand>(it.next());
        return op->operator()(x1,x2);
    });

    productions.emplace_back("term","factor",[](symbol_iterator&it,Context&con){
        return it.next();
    });

    productions.emplace_back("factor","integer",[](symbol_iterator&it,Context&con){
        auto symbol= std::dynamic_pointer_cast<TerminalValue>(it.next());
        auto ret= std::make_shared<OperandInt>(atoi((const char *) symbol->getText()));
        return ret;
    });

    productions.emplace_back("factor","( exp )",[](symbol_iterator&it,Context&con){
        it.next();
        return it.next();
    });

    productions.emplace_back("addop","+",[](symbol_iterator&it,Context&con){
        return std::make_shared<BinaryOperator>([](const operand_ptr& x1,const operand_ptr& x2){
            auto a1= std::dynamic_pointer_cast<OperandInt>(x1);
            auto a2= std::dynamic_pointer_cast<OperandInt>(x2);
            return std::make_shared<OperandInt>(a1->getValue()+a2->getValue());
        });
    });

    productions.emplace_back("addop","-",[](symbol_iterator&it,Context&con){
        return std::make_shared<BinaryOperator>([](const operand_ptr& x1,const operand_ptr& x2){
            auto a1= std::dynamic_pointer_cast<OperandInt>(x1);
            auto a2= std::dynamic_pointer_cast<OperandInt>(x2);
            return std::make_shared<OperandInt>(a1->getValue()-a2->getValue());
        });
    });

    productions.emplace_back("mulop","*",[](symbol_iterator&it,Context&con){
        return std::make_shared<BinaryOperator>([](const operand_ptr& x1,const operand_ptr& x2){
            auto a1= std::dynamic_pointer_cast<OperandInt>(x1);
            auto a2= std::dynamic_pointer_cast<OperandInt>(x2);
            return std::make_shared<OperandInt>(a1->getValue()*a2->getValue());
        });
    });

    productions.emplace_back("mulop","/",[](symbol_iterator&it,Context&con){
        return std::make_shared<BinaryOperator>([](const operand_ptr& x1,const operand_ptr& x2){
            auto a1= std::dynamic_pointer_cast<OperandInt>(x1);
            auto a2= std::dynamic_pointer_cast<OperandInt>(x2);
            return std::make_shared<OperandInt>(a1->getValue()/a2->getValue());
        });
    });

    return productions;
}