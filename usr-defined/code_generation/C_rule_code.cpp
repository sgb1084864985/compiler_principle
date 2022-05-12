//
// Created by zlz on 22-5-7.
//

#include "C_rule_code.h"
#include "gen_code_rule_addExpr.hpp"
using std::unique_ptr;
using std::make_unique;
unique_ptr<ProductionInfo> C_rule_code::ruleCodeTable[]={
    //translation_unit->external_declaration
    make_unique<ProductionInfo>(),
    //translation_unit->translation_unit external_declaration
    make_unique<ProductionInfo>(),
    //external_declaration->function_definition
    make_unique<ProductionInfo>(),
    //external_declaration->declaration
    make_unique<ProductionInfo>(),
    //function_definition->declaration_specifiers declarator declaration_list compound_statement
    make_unique<ProductionInfo>(),
    //function_definition->declaration_specifiers declarator compound_statement
    make_unique<ProductionInfo>(),
    //statement->labeled_statement
    make_unique<ProductionInfo>(),
    //statement->compound_statement
    make_unique<ProductionInfo>(),
    //statement->expression_statement
    make_unique<ProductionInfo>(),
    //statement->selection_statement
    make_unique<ProductionInfo>(),
    //statement->iteration_statement
    make_unique<ProductionInfo>(),
    //statement->jump_statement
    make_unique<ProductionInfo>(),
    //labeled_statement->id : statement
    make_unique<ProductionInfo>(),
    //labeled_statement->case constant_expr : statement
    make_unique<ProductionInfo>(),
    //labeled_statement->default : statement
    make_unique<ProductionInfo>(),
    //compound_statement->{ }
    make_unique<ProductionInfo>(),
    //compound_statement->{ block_item_list }
    make_unique<ProductionInfo>(),
    //block_item_list->block_item
    make_unique<ProductionInfo>(),
    //block_item_list->block_item_list block_item
    make_unique<ProductionInfo>(),
    //block_item->declaration
    make_unique<ProductionInfo>(),
    //block_item->statement
    make_unique<ProductionInfo>(),
    //expression_statement->;
    make_unique<ProductionInfo>(),
    //expression_statement->C_expr ;
    make_unique<ProductionInfo>(),
    //selection_statement->if ( C_expr ) statement else statement
    make_unique<ProductionInfo>(),
    //selection_statement->if ( C_expr ) statement
    make_unique<ProductionInfo>(),
    //selection_statement->switch ( C_expr ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->while ( C_expr ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->do statement while ( C_expr )
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( expression_statement expression_statement ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( expression_statement expression_statement C_expr ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( declaration expression_statement ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( declaration expression_statement C_expr ) statement
    make_unique<ProductionInfo>(),
    //jump_statement->goto id ;
    make_unique<ProductionInfo>(),
    //jump_statement->continue ;
    make_unique<ProductionInfo>(),
    //jump_statement->break ;
    make_unique<ProductionInfo>(),
    //jump_statement->return ;
    make_unique<ProductionInfo>(),
    //jump_statement->return C_expr ;
    make_unique<ProductionInfo>(),
    //declaration_list->declaration
    make_unique<ProductionInfo>(),
    //declaration_list->declaration_list declaration
    make_unique<ProductionInfo>(),
    //declaration->declaration_specifiers ;
    make_unique<ProductionInfo>(),
    //declaration->declaration_specifiers init_declarator_list ;
    make_unique<ProductionInfo>(),
    //declaration->static_assert_declaration
    make_unique<ProductionInfo>(),
    //declaration_specifiers->storage_class_specifier
    make_unique<ProductionInfo>(),
    //declaration_specifiers->storage_class_specifier declaration_specifiers
    make_unique<ProductionInfo>(),
    //declaration_specifiers->type_specifier
    make_unique<ProductionInfo>(),
    //declaration_specifiers->type_specifier declaration_specifiers
    make_unique<ProductionInfo>(),
    //declaration_specifiers->type_qualifier
    make_unique<ProductionInfo>(),
    //declaration_specifiers->function_specifier
    make_unique<ProductionInfo>(),
    //declaration_specifiers->alignment_specifier
    make_unique<ProductionInfo>(),
    //declaration_specifiers->type_qualifier declaration_specifiers
    make_unique<ProductionInfo>(),
    //declaration_specifiers->function_specifier declaration_specifiers
    make_unique<ProductionInfo>(),
    //declaration_specifiers->alignment_specifier declaration_specifiers
    make_unique<ProductionInfo>(),
    //init_declarator_list->init_declarator
    make_unique<ProductionInfo>(),
    //init_declarator_list->init_declarator_list , init_declarator
    make_unique<ProductionInfo>(),
    //init_declarator->declarator
    make_unique<ProductionInfo>(),
    //init_declarator->declarator = initializer
    make_unique<ProductionInfo>(),
    //storage_class_specifier->typedef
    make_unique<ProductionInfo>(),
    //storage_class_specifier->extern
    make_unique<ProductionInfo>(),
    //storage_class_specifier->static
    make_unique<ProductionInfo>(),
    //storage_class_specifier->_Thread_local
    make_unique<ProductionInfo>(),
    //storage_class_specifier->auto
    make_unique<ProductionInfo>(),
    //storage_class_specifier->register
    make_unique<ProductionInfo>(),
    //type_specifier->void
    make_unique<ProductionInfo>(),
    //type_specifier->char
    make_unique<ProductionInfo>(),
    //type_specifier->short
    make_unique<ProductionInfo>(),
    //type_specifier->int
    make_unique<ProductionInfo>(),
    //type_specifier->long
    make_unique<ProductionInfo>(),
    //type_specifier->float
    make_unique<ProductionInfo>(),
    //type_specifier->double
    make_unique<ProductionInfo>(),
    //type_specifier->signed
    make_unique<ProductionInfo>(),
    //type_specifier->unsigned
    make_unique<ProductionInfo>(),
    //type_specifier->_Bool
    make_unique<ProductionInfo>(),
    //type_specifier->_Complex
    make_unique<ProductionInfo>(),
    //type_specifier->_Imaginary
    make_unique<ProductionInfo>(),
    //type_specifier->atomic_type_specifier
    make_unique<ProductionInfo>(),
    //type_specifier->struct_or_union_specifier
    make_unique<ProductionInfo>(),
    //type_specifier->enum_specifier
    make_unique<ProductionInfo>(),
    //type_specifier->typedef_name
    make_unique<ProductionInfo>(),
    //struct_or_union_specifier->struct_or_union { struct_declaration_list }
    make_unique<ProductionInfo>(),
    //struct_or_union_specifier->struct_or_union id { struct_declaration_list }
    make_unique<ProductionInfo>(),
    //struct_or_union_specifier->struct_or_union id
    make_unique<ProductionInfo>(),
    //struct_or_union->struct
    make_unique<ProductionInfo>(),
    //struct_or_union->union
    make_unique<ProductionInfo>(),
    //struct_declaration_list->struct_declaration
    make_unique<ProductionInfo>(),
    //struct_declaration_list->struct_declaration_list struct_declaration
    make_unique<ProductionInfo>(),
    //struct_declaration->specifier_qualifier_list ;
    make_unique<ProductionInfo>(),
    //struct_declaration->specifier_qualifier_list struct_declarator_list ;
    make_unique<ProductionInfo>(),
    //struct_declaration->static_assert_declaration
    make_unique<ProductionInfo>(),
    //specifier_qualifier_list->type_specifier
    make_unique<ProductionInfo>(),
    //specifier_qualifier_list->type_qualifier
    make_unique<ProductionInfo>(),
    //specifier_qualifier_list->type_specifier specifier_qualifier_list
    make_unique<ProductionInfo>(),
    //specifier_qualifier_list->type_qualifier specifier_qualifier_list
    make_unique<ProductionInfo>(),
    //struct_declarator_list->struct_declarator
    make_unique<ProductionInfo>(),
    //struct_declarator_list->struct_declarator_list , struct_declarator
    make_unique<ProductionInfo>(),
    //struct_declarator->: constant_expr
    make_unique<ProductionInfo>(),
    //struct_declarator->declarator : constant_expr
    make_unique<ProductionInfo>(),
    //struct_declarator->declarator
    make_unique<ProductionInfo>(),
    //enum_specifier->enum { enumerator_list }
    make_unique<ProductionInfo>(),
    //enum_specifier->enum { enumerator_list , }
    make_unique<ProductionInfo>(),
    //enum_specifier->enum id { enumerator_list }
    make_unique<ProductionInfo>(),
    //enum_specifier->enum id { enumerator_list , }
    make_unique<ProductionInfo>(),
    //enum_specifier->enum id
    make_unique<ProductionInfo>(),
    //enumerator_list->enumerator
    make_unique<ProductionInfo>(),
    //enumerator_list->enumerator_list , enumerator
    make_unique<ProductionInfo>(),
    //enumerator->id = constant_expr
    make_unique<ProductionInfo>(),
    //enumerator->id
    make_unique<ProductionInfo>(),
    //atomic_type_specifier->_Atomic ( type_name )
    make_unique<ProductionInfo>(),
    //type_qualifier->const
    make_unique<ProductionInfo>(),
    //type_qualifier->restrict
    make_unique<ProductionInfo>(),
    //type_qualifier->volatile
    make_unique<ProductionInfo>(),
    //type_qualifier->_Atomic
    make_unique<ProductionInfo>(),
    //function_specifier->inline
    make_unique<ProductionInfo>(),
    //function_specifier->_Noreturn
    make_unique<ProductionInfo>(),
    //alignment_specifier->_Alignas ( type_name )
    make_unique<ProductionInfo>(),
    //alignment_specifier->_Alignas ( constant_expr )
    make_unique<ProductionInfo>(),
    //declarator->pointer direct_declarator
    make_unique<ProductionInfo>(),
    //declarator->direct_declarator
    make_unique<ProductionInfo>(),
    //direct_declarator->id
    make_unique<ProductionInfo>(),
    //direct_declarator->( declarator )
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ * ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ static type_qualifier_list assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ static assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ type_qualifier_list * ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ type_qualifier_list static assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ type_qualifier_list assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator [ type_qualifier_list ]
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator ( )
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator ( parameter_type_list )
    make_unique<ProductionInfo>(),
    //direct_declarator->direct_declarator ( identifier_list )
    make_unique<ProductionInfo>(),
    //pointer->*
    make_unique<ProductionInfo>(),
    //pointer->* pointer
    make_unique<ProductionInfo>(),
    //pointer->* type_qualifier_list
    make_unique<ProductionInfo>(),
    //pointer->* type_qualifier_list pointer
    make_unique<ProductionInfo>(),
    //type_qualifier_list->type_qualifier
    make_unique<ProductionInfo>(),
    //type_qualifier_list->type_qualifier_list type_qualifier
    make_unique<ProductionInfo>(),
    //parameter_type_list->parameter_list
    make_unique<ProductionInfo>(),
    //parameter_type_list->parameter_list , ...
    make_unique<ProductionInfo>(),
    //parameter_list->parameter_declaration
    make_unique<ProductionInfo>(),
    //parameter_list->parameter_list , parameter_declaration
    make_unique<ProductionInfo>(),
    //parameter_declaration->declaration_specifiers declarator
    make_unique<ProductionInfo>(),
    //parameter_declaration->declaration_specifiers abstract_declarator
    make_unique<ProductionInfo>(),
    //parameter_declaration->declaration_specifiers
    make_unique<ProductionInfo>(),
    //identifier_list->id
    make_unique<ProductionInfo>(),
    //identifier_list->identifier_list , id
    make_unique<ProductionInfo>(),
    //type_name->specifier_qualifier_list abstract_declarator
    make_unique<ProductionInfo>(),
    //type_name->specifier_qualifier_list
    make_unique<ProductionInfo>(),
    //abstract_declarator->pointer direct_abstract_declarator
    make_unique<ProductionInfo>(),
    //abstract_declarator->pointer
    make_unique<ProductionInfo>(),
    //abstract_declarator->direct_abstract_declarator
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->( abstract_declarator )
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[  ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[ * ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[ static type_qualifier_list assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[ static assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[ type_qualifier_list assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[ type_qualifier_list static assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[ type_qualifier_list ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->[ assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [  ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [ * ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [ static type_qualifier_list assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [ static assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list static assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator [ assignment_expr ]
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->(  )
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->( parameter_type_list )
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator (  )
    make_unique<ProductionInfo>(),
    //direct_abstract_declarator->direct_abstract_declarator ( parameter_type_list )
    make_unique<ProductionInfo>(),
    //initializer->{ initializer_list }
    make_unique<ProductionInfo>(),
    //initializer->{ initializer_list , }
    make_unique<ProductionInfo>(),
    //initializer->assignment_expr
    make_unique<ProductionInfo>(),
    //initializer_list->designation initializer
    make_unique<ProductionInfo>(),
    //initializer_list->initializer
    make_unique<ProductionInfo>(),
    //initializer_list->initializer_list , designation initializer
    make_unique<ProductionInfo>(),
    //initializer_list->initializer_list , initializer
    make_unique<ProductionInfo>(),
    //designation->designator_list =
    make_unique<ProductionInfo>(),
    //designator_list->designator
    make_unique<ProductionInfo>(),
    //designator_list->designator_list designator
    make_unique<ProductionInfo>(),
    //designator->. id
    make_unique<ProductionInfo>(),
    //designator->[ constant_expr ]
    make_unique<ProductionInfo>(),
    //static_assert_declaration->_Static_assert ( constant_expr , str )
    make_unique<ProductionInfo>(),
    //C_expr->assignment_expr
    make_unique<ProductionInfo>(),
    //C_expr->C_expr , assignment_expr
    make_unique<ProductionInfo>(),
    //constant_expr->conditional_expr
    make_unique<ProductionInfo>(),
    //assignment_expr->conditional_expr
    make_unique<ProductionInfo>(),
    //assignment_expr->unary_expr assignment_operator assignment_expr
    make_unique<ProductionInfo>(),
    //assignment_operator->=
    make_unique<ProductionInfo>(),
    //assignment_operator->*=
    make_unique<ProductionInfo>(),
    //assignment_operator->/=
    make_unique<ProductionInfo>(),
    //assignment_operator->%=
    make_unique<ProductionInfo>(),
    //assignment_operator->+=
    make_unique<ProductionInfo>(),
    //assignment_operator->-=
    make_unique<ProductionInfo>(),
    //assignment_operator-><<=
    make_unique<ProductionInfo>(),
    //assignment_operator->>>=
    make_unique<ProductionInfo>(),
    //assignment_operator->&=
    make_unique<ProductionInfo>(),
    //assignment_operator->^=
    make_unique<ProductionInfo>(),
    //assignment_operator->|=
    make_unique<ProductionInfo>(),
    //conditional_expr->logic_or_expr
    make_unique<ProductionInfo>(),
    //conditional_expr->logic_or_expr ? C_expr : conditional_expr
    make_unique<ProductionInfo>(),
    //logic_or_expr->logic_and_expr
    make_unique<ProductionInfo>(),
    //logic_or_expr->logic_or_expr || logic_and_expr
    make_unique<ProductionInfo>(),
    //logic_and_expr->or_expr
    make_unique<ProductionInfo>(),
    //logic_and_expr->logic_and_expr && or_expr
    make_unique<ProductionInfo>(),
    //or_expr->xor_expr
    make_unique<ProductionInfo>(),
    //or_expr->or_expr | xor_expr
    make_unique<ProductionInfo>(),
    //xor_expr->and_expr
    make_unique<ProductionInfo>(),
    //xor_expr->xor_expr ^ and_expr
    make_unique<ProductionInfo>(),
    //and_expr->eq_expr
    make_unique<ProductionInfo>(),
    //and_expr->and_expr & eq_expr
    make_unique<ProductionInfo>(),
    //eq_expr->relational_expr
    make_unique<ProductionInfo>(),
    //eq_expr->eq_expr == relational_expr
    make_unique<ProductionInfo>(),
    //eq_expr->eq_expr != relational_expr
    make_unique<ProductionInfo>(),
    //relational_expr->shift_expr
    make_unique<ProductionInfo>(),
    //relational_expr->relational_expr < shift_expr
    make_unique<ProductionInfo>(),
    //relational_expr->relational_expr > shift_expr
    make_unique<ProductionInfo>(),
    //relational_expr->relational_expr <= shift_expr
    make_unique<ProductionInfo>(),
    //relational_expr->relational_expr >= shift_expr
    make_unique<ProductionInfo>(),
    //shift_expr->add_expr
    make_unique<ProductionInfo>(),
    //shift_expr->shift_expr << add_expr
    make_unique<ProductionInfo>(),
    //shift_expr->shift_expr >> add_expr
    make_unique<ProductionInfo>(),
    //add_expr->mul_expr
    make_unique<ProductionInfo>(),
    //add_expr->add_expr + mul_expr
    make_unique<ProductionInfo>(),
    //add_expr->add_expr - mul_expr
    make_unique<ProductionInfo>(),
    //mul_expr->unary_expr
    make_unique<ProductionInfo>(),
    //mul_expr->mul_expr * unary_expr
    make_unique<ProductionInfo>(),
    //mul_expr->mul_expr / unary_expr
    make_unique<ProductionInfo>(),
    //mul_expr->mul_expr % unary_expr
    make_unique<ProductionInfo>(),
    //cast_expr->unary_expr
    make_unique<ProductionInfo>(),
    //cast_expr->( type_name ) cast_expr
    make_unique<ProductionInfo>(),
    //unary_expr->postfix_expr
    make_unique<ProductionInfo>(),
    //unary_expr->unary_operator cast_expr
    make_unique<ProductionInfo>(),
    //unary_expr->++ unary_expr
    make_unique<ProductionInfo>(),
    //unary_expr->-- unary_expr
    make_unique<ProductionInfo>(),
    //unary_expr->sizeof unary_expr
    make_unique<ProductionInfo>(),
    //unary_expr->sizeof ( type_name )
    make_unique<ProductionInfo>(),
    //unary_expr->_Alignof ( type_name )
    make_unique<ProductionInfo>(),
    //unary_operator->&
    make_unique<ProductionInfo>(),
    //unary_operator->*
    make_unique<ProductionInfo>(),
    //unary_operator->+
    make_unique<ProductionInfo>(),
    //unary_operator->-
    make_unique<ProductionInfo>(),
    //unary_operator->~
    make_unique<ProductionInfo>(),
    //unary_operator->!
    make_unique<ProductionInfo>(),
    //argument_expression_list->assignment_expr
    make_unique<ProductionInfo>(),
    //argument_expression_list->argument_expression_list , assignment_expr
    make_unique<ProductionInfo>(),
    //postfix_expr->primary_expr
    make_unique<ProductionInfo>(),
    //postfix_expr->postfix_expr ( )
    make_unique<ProductionInfo>(),
    //postfix_expr->postfix_expr . id
    make_unique<ProductionInfo>(),
    //postfix_expr->postfix_expr -> id
    make_unique<ProductionInfo>(),
    //postfix_expr->postfix_expr ++
    make_unique<ProductionInfo>(),
    //postfix_expr->postfix_expr --
    make_unique<ProductionInfo>(),
    //postfix_expr->postfix_expr [ C_expr ]
    make_unique<ProductionInfo>(),
    //postfix_expr->postfix_expr ( argument_expression_list )
    make_unique<ProductionInfo>(),
    //postfix_expr->( type_name ) { initializer_list }
    make_unique<ProductionInfo>(),
    //postfix_expr->( type_name ) { initializer_list , }
    make_unique<ProductionInfo>(),
    //String->str // str is just a token, like "hello"
    make_unique<ProductionInfo>(),
    //String->__func__
    make_unique<ProductionInfo>(),
    //generic_selection->_Generic ( assignment_expr , generic_assoc_list )
    make_unique<ProductionInfo>(),
    //generic_assoc_list->generic_association
    make_unique<ProductionInfo>(),
    //generic_assoc_list->generic_assoc_list , generic_association
    make_unique<ProductionInfo>(),
    //generic_association->type_name : assignment_expr
    make_unique<ProductionInfo>(),
    //generic_association->default : assignment_expr
    make_unique<ProductionInfo>(),
    //constant->integer
    make_unique<ProductionInfo>(),
    //constant->Float // Float is a token, like 3.14
    make_unique<ProductionInfo>(),
    //constant->enumerate_constant
    make_unique<ProductionInfo>(),
    //primary_expr->( C_expr )
    make_unique<ProductionInfo>(),
    //primary_expr->id // id is identifier, like abc
    make_unique<ProductionInfo>(),
    //primary_expr->constant
    make_unique<ProductionInfo>(),
    //primary_expr->String // String is not a token
    make_unique<ProductionInfo>(),
    //primary_expr->generic_selection
    make_unique<ProductionInfo>(),
};
