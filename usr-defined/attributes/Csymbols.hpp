#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include "compiler.h"
#include "AST.h"
#include "C_expr.hpp"
#include <memory>
#include <utility>

// C non-terminal symbols
namespace CSym {
    using AST::NonTerminal;
    using primary_expr = C_expr;
    using postfix_expr = C_expr;
    using String=NonTerminal;
    using constant=NonTerminal;
    using generic_selection=NonTerminal;
    using generic_assoc_list=NonTerminal;
    using generic_association=NonTerminal;
    using argument_expression_list=C_expr;
    using assignment_expr=C_expr;
    using conditional_expr=C_expr;
    using unary_expr=C_expr;
    using assignment_operator=NonTerminal;
    using expr=C_expr;
    using cast_expr=C_expr;
    using mul_expr=C_expr;
    using add_expr=C_expr;
    using shift_expr=C_expr;
    using relational_expr=C_expr;
    using equality_expr=C_expr;
    using and_expr=C_expr;
    using exclusive_or_expr=C_expr;
    using inclusive_or_expr=C_expr;
    using logical_and_expr=C_expr;
    using logical_or_expr=C_expr;
    using unary_operator=NonTerminal;
    using constant_expr=C_expr;
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
    using or_expr=inclusive_or_expr;

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


#endif