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
    using String=NonTerminal;
    using generic_selection=NonTerminal;
    using generic_assoc_list=NonTerminal;
    using generic_association=NonTerminal;
    using argument_expression_list=NonTerminal;
    using assignment_expr=NonTerminal;
    using conditional_expr=NonTerminal;
    using unary_expr=NonTerminal;
    using assignment_operator=NonTerminal;
    using expr=NonTerminal;
    using cast_expr=NonTerminal;
    using mul_expr=NonTerminal;
    using add_expr=NonTerminal;
    using shift_expr=NonTerminal;
    using relational_expr=NonTerminal;
    using equality_expr=NonTerminal;
    using and_expr=NonTerminal;
    using exclusive_or_expr=NonTerminal;
    using inclusive_or_expr=NonTerminal;
    using logical_and_expr=NonTerminal;
    using logical_or_expr=NonTerminal;
    using unary_operator=NonTerminal;
    using constant_expr=NonTerminal;
    using declaration=NonTerminal;
    using declaration_specifiers=NonTerminal;
    using init_declarator_list=NonTerminal;
    using init_declarator=NonTerminal;
    using storage_class_specifier=NonTerminal;
    using type_specifier =NonTerminal;
    using struct_or_union_specifier=NonTerminal;
    using struct_or_union=NonTerminal;
    using struct_declaration_list=NonTerminal;
    using struct_declaration=NonTerminal;
    using specifier_qualifier_list=NonTerminal;
    using struct_declarator_list=NonTerminal;
    using struct_declarator=NonTerminal;
    using enum_specifier=NonTerminal;
    using enumerator_list=NonTerminal;
    using enumerator=NonTerminal;
    using atomic_type_specifier=NonTerminal;
    using type_qualifier=NonTerminal;
    using function_specifier=NonTerminal;
    using alignment_specifier=NonTerminal;
    using declarator=NonTerminal;
    using direct_declarator=NonTerminal;
    using pointer=NonTerminal;
    using type_qualifier_list=NonTerminal;
    using parameter_type_list=NonTerminal;
    using parameter_list=NonTerminal;
    using parameter_declaration=NonTerminal;
    using identifier_list=NonTerminal;
    using type_name=NonTerminal;
    using abstract_declarator=NonTerminal;
    using direct_abstract_declarator=NonTerminal;
    using initializer=NonTerminal;
    using initializer_list=NonTerminal;
    using designation=NonTerminal;
    using designator_list=NonTerminal;
    using designator=NonTerminal;
    using static_assert_declaration=NonTerminal;
    using statement=NonTerminal;
    using labeled_statement=NonTerminal;
    using compound_statement=NonTerminal;
    using block_item_list=NonTerminal;
    using block_item=NonTerminal;
    using expression_statement=NonTerminal;
    using selection_statement=NonTerminal;
    using iteration_statement=NonTerminal;
    using jump_statement=NonTerminal;
    using translation_unit=NonTerminal;
    using external_declaration=NonTerminal;
    using function_definition=NonTerminal;
    using declaration_list=NonTerminal;


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