#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include "compiler.h"
#include "AST.h"
#include <memory>
#include <utility>

// C non-terminal symbols
namespace CSym {
    using AST::NonTerminal;
    using primary_expr = NonTerminal;
    using postfix_expr = NonTerminal;
    using type_name=NonTerminal;
    using type_specifier=NonTerminal;
    using type_qualifier=NonTerminal;
    using specifier_qualifier_list=NonTerminal;
    using abstract_declarator=NonTerminal;
    using type_qualifier_list=NonTerminal;
    using pointer=NonTerminal;
    using direct_abstract_declarator=NonTerminal;
    using assignment_expr=NonTerminal;
    using parameter_type_list=NonTerminal;
    using conditional_expr=NonTerminal;
    using unary_expr=NonTerminal;
    using assignment_operator=NonTerminal;
    using parameter_list=NonTerminal;
    using parameter_declaration=NonTerminal;
    using declaration_specifiers=NonTerminal;
    using declarator=NonTerminal;
    using declaration_specifiers =NonTerminal;
    using init_list=NonTerminal;
    using expr=NonTerminal;
    using argument_expr_list=NonTerminal;
    using cast_expr=NonTerminal;
    using multicative_expr=NonTerminal;
    using additive_expr=NonTerminal;
    using shift_expr=NonTerminal;
    using relational_expr=NonTerminal;
    using equality_expr=NonTerminal;
    using and_expr=NonTerminal;
    using exclusive_or_expr=NonTerminal;
    using inclusive_or_expr=NonTerminal;
    using logical_and_expr=NonTerminal;
    using logical_or_expr=NonTerminal;


//    enum enumSymbol{
//        PrimaryExpr
//    };
//    const char* labels[]={"primary_expr"};

    // you can replace T with NonTerminal's subclass
//    template<enumSymbol sym,class T=NonTerminal>
//    class Node : public T {
//        explicit Node(Production &production) : T(production, labels[sym]) {}
//    };

}
//------------------------------------------------------
// old value
//------------------------------------------------------
class Operand:public SymbolValue{

};

using operand_ptr=std::shared_ptr<Operand>;
using Op2=function<operand_ptr(operand_ptr,operand_ptr)>;

class BinaryOperator:public SymbolValue{
    Op2 op;
public:
    explicit BinaryOperator(Op2 op):op(std::move(op)){}
    operand_ptr operator()(operand_ptr x1,operand_ptr x2){
        return op(std::move(x1),std::move(x2));
    }
};

class OperandInt:public Operand{
    int val;
public:
    explicit OperandInt(int i):val(i){}
    int getValue()const{return val;}
};

#endif