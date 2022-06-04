//
// Created by zlz on 22-5-7.
//

#include "C_rule_code.h"
#include "gen_code_rule_addExpr.hpp"
#include "gen_code_postfix.hpp"
#include "gen_code_primary.h"
#include "gen_code_compstmt1.hpp"
#include "gen_code_compstmt2.hpp"
#include "gen_code_exdel.hpp"
#include "gen_code_block1.hpp"
#include "gen_code_block2.hpp"
#include "gen_code_blocklist1.hpp"
#include "gen_code_blocklist2.hpp"
#include "gen_code_if_statement.hpp"
#include "gen_code_loop_statement.hpp"
#include "gen_code_jumpexpr.hpp"
#include "gen_code_add2mul.hpp"
#include "gen_code_and2eq.hpp"
#include "gen_code_assign.hpp"
#include "gen_code_assign2cond.hpp"
#include "gen_code_castexp2unary.hpp"
#include "gen_code_cond2logicOr.hpp"
#include "gen_code_eq2rel.hpp"
#include "gen_code_expr2assign1.hpp"
#include "gen_code_expr2assign2.hpp"
#include "gen_code_exprstmt1.hpp"
#include "gen_code_exprstmt2.hpp"
#include "gen_code_logic_or2and.hpp"
#include "gen_code_logicand2or.hpp"
#include "gen_code_mul2unary.hpp"
#include "gen_code_or2xor.hpp"
#include "gen_code_rel2sh.hpp"
#include "gen_code_rule_andExpr.hpp"
#include "gen_code_rule_divExpr.hpp"
#include "gen_code_rule_eqExpr.hpp"
#include "gen_code_rule_gt.hpp"
#include "gen_code_rule_gte.hpp"
#include "gen_code_rule_lteExpr.hpp"
#include "gen_code_rule_ltExpr.hpp"
#include "gen_code_rule_mulExpr.hpp"
#include "gen_code_rule_neqExpr.hpp"
#include "gen_code_rule_orExpr.hpp"
#include "gen_code_rule_remExpr.hpp"
#include "gen_code_rule_shlExpr.hpp"
#include "gen_code_rule_subExpr.hpp"
#include "gen_code_rule_xorExpr.hpp"
#include "gen_code_sh2add.hpp"
#include "gen_code_unary2postfix.hpp"
#include "gen_code_unaryexp.hpp"
//#include "gen_code_unaryOp.hpp"
#include "gen_code_xor2and.hpp"

using std::unique_ptr;
using std::make_unique;
unique_ptr<ProductionInfo> C_rule_code::ruleCodeTable[]={
        //translation_unit->external_declaration
        make_unique<code_gen_productionInfo>(),
        //translation_unit->translation_unit external_declaration
        make_unique<code_gen_productionInfo>(),
        //external_declaration->function_definition
        make_unique<gen_code_extern_unit1>(),
        //external_declaration->declaration
        make_unique<gen_code_extern_unit2>(),
        //function_definition->declaration_specifiers declarator declaration_list compound_statement
        make_unique<code_gen_productionInfo>(),
        //function_definition->declaration_specifiers declarator compound_statement
        make_unique<code_gen_productionInfo>(),
        //statement->labeled_statement
        make_unique<code_genInChild>(),
        //statement->compound_statement
        make_unique<code_genInChild>(),
        //statement->expression_statement
        make_unique<code_genInChild>(),
        //statement->selection_statement
        make_unique<code_genInChild>(),
        //statement->iteration_statement
        make_unique<code_genInChild>(),
        //statement->jump_statement
        make_unique<code_genInChild>(),
        //labeled_statement->id : statement
        make_unique<code_gen_productionInfo>(),
        //labeled_statement->case constant_expr : statement
        make_unique<code_gen_productionInfo>(),
        //labeled_statement->default : statement
        make_unique<code_gen_productionInfo>(),
        //compound_statement->{ }
        make_unique<gen_code_compstmt1>(),
        //compound_statement->{ block_item_list }
        make_unique<gen_code_compstmt2>(),
        //block_item_list->block_item
        make_unique<gen_code_blocklist1>(),
        //block_item_list->block_item_list block_item
        make_unique<gen_code_blocklist2>(),
        //block_item->declaration
        make_unique<code_genNull>(),
        //block_item->statement
        make_unique<code_genInChild>(),
        //expression_statement->;
        make_unique<code_genNull>(),
        //expression_statement->expr ;
        make_unique<code_genInChild>(),
        //selection_statement->if ( expr ) statement else statement
        make_unique<gen_code_rule_if1>(),
        //selection_statement->if ( expr ) statement
        make_unique<gen_code_rule_if2>(),
        //selection_statement->switch ( expr ) statement
        make_unique<code_gen_productionInfo>(),
        //iteration_statement->while ( expr ) statement
        make_unique<gen_code_rule_while1>(),
        //iteration_statement->do statement while ( expr )
        make_unique<gen_code_rule_while2>(),
        //iteration_statement->for ( expression_statement expression_statement ) statement
        make_unique<code_gen_productionInfo>(),
        //iteration_statement->for ( expression_statement expression_statement expr ) statement
        make_unique<code_gen_productionInfo>(),
        //iteration_statement->for ( declaration expression_statement ) statement
        make_unique<code_gen_productionInfo>(),
        //iteration_statement->for ( declaration expression_statement expr ) statement
        make_unique<code_gen_productionInfo>(),
        //jump_statement->goto id ;
        make_unique<code_gen_productionInfo>(),
        //jump_statement->continue ;
        make_unique<code_gen_productionInfo>(),
        //jump_statement->break ;
        make_unique<code_gen_productionInfo>(),
        //jump_statement->return ;
        make_unique<gen_code_jumpexpr1>(),
        //jump_statement->return expr ;
        make_unique<gen_code_jumpexpr2>(),
        //declaration_list->declaration
        make_unique<code_gen_productionInfo>(),
        //declaration_list->declaration_list declaration
        make_unique<code_gen_productionInfo>(),
        //declaration->declaration_specifiers ;
        make_unique<code_gen_productionInfo>(),
        //declaration->declaration_specifiers init_declarator_list ;
        make_unique<code_gen_productionInfo>(),
        //declaration->static_assert_declaration
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->storage_class_specifier
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->storage_class_specifier declaration_specifiers
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->type_specifier
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->type_specifier declaration_specifiers
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->type_qualifier
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->function_specifier
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->alignment_specifier
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->type_qualifier declaration_specifiers
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->function_specifier declaration_specifiers
        make_unique<code_gen_productionInfo>(),
        //declaration_specifiers->alignment_specifier declaration_specifiers
        make_unique<code_gen_productionInfo>(),
        //init_declarator_list->init_declarator
        make_unique<code_gen_productionInfo>(),
        //init_declarator_list->init_declarator_list , init_declarator
        make_unique<code_gen_productionInfo>(),
        //init_declarator->declarator
        make_unique<code_gen_productionInfo>(),
        //init_declarator->declarator = initializer
        make_unique<code_gen_productionInfo>(),
        //storage_class_specifier->typedef
        make_unique<code_gen_productionInfo>(),
        //storage_class_specifier->extern
        make_unique<code_gen_productionInfo>(),
        //storage_class_specifier->static
        make_unique<code_gen_productionInfo>(),
        //storage_class_specifier->_Thread_local
        make_unique<code_gen_productionInfo>(),
        //storage_class_specifier->auto
        make_unique<code_gen_productionInfo>(),
        //storage_class_specifier->register
        make_unique<code_gen_productionInfo>(),
        //type_specifier->void
        make_unique<code_gen_productionInfo>(),
        //type_specifier->char
        make_unique<code_gen_productionInfo>(),
        //type_specifier->short
        make_unique<code_gen_productionInfo>(),
        //type_specifier->int
        make_unique<code_gen_productionInfo>(),
        //type_specifier->long
        make_unique<code_gen_productionInfo>(),
        //type_specifier->float
        make_unique<code_gen_productionInfo>(),
        //type_specifier->double
        make_unique<code_gen_productionInfo>(),
        //type_specifier->signed
        make_unique<code_gen_productionInfo>(),
        //type_specifier->unsigned
        make_unique<code_gen_productionInfo>(),
        //type_specifier->_Bool
        make_unique<code_gen_productionInfo>(),
        //type_specifier->_Complex
        make_unique<code_gen_productionInfo>(),
        //type_specifier->_Imaginary
        make_unique<code_gen_productionInfo>(),
        //type_specifier->atomic_type_specifier
        make_unique<code_gen_productionInfo>(),
        //type_specifier->struct_or_union_specifier
        make_unique<code_gen_productionInfo>(),
        //type_specifier->enum_specifier
        make_unique<code_gen_productionInfo>(),
        //type_specifier->typedef_name
        make_unique<code_gen_productionInfo>(),
        //struct_or_union_specifier->struct_or_union { struct_declaration_list }
        make_unique<code_gen_productionInfo>(),
        //struct_or_union_specifier->struct_or_union id { struct_declaration_list }
        make_unique<code_gen_productionInfo>(),
        //struct_or_union_specifier->struct_or_union id
        make_unique<code_gen_productionInfo>(),
        //struct_or_union->struct
        make_unique<code_gen_productionInfo>(),
        //struct_or_union->union
        make_unique<code_gen_productionInfo>(),
        //struct_declaration_list->struct_declaration
        make_unique<code_gen_productionInfo>(),
        //struct_declaration_list->struct_declaration_list struct_declaration
        make_unique<code_gen_productionInfo>(),
        //struct_declaration->specifier_qualifier_list ;
        make_unique<code_gen_productionInfo>(),
        //struct_declaration->specifier_qualifier_list struct_declarator_list ;
        make_unique<code_gen_productionInfo>(),
        //struct_declaration->static_assert_declaration
        make_unique<code_gen_productionInfo>(),
        //specifier_qualifier_list->type_specifier
        make_unique<code_gen_productionInfo>(),
        //specifier_qualifier_list->type_qualifier
        make_unique<code_gen_productionInfo>(),
        //specifier_qualifier_list->type_specifier specifier_qualifier_list
        make_unique<code_gen_productionInfo>(),
        //specifier_qualifier_list->type_qualifier specifier_qualifier_list
        make_unique<code_gen_productionInfo>(),
        //struct_declarator_list->struct_declarator
        make_unique<code_gen_productionInfo>(),
        //struct_declarator_list->struct_declarator_list , struct_declarator
        make_unique<code_gen_productionInfo>(),
        //struct_declarator->: constant_expr
        make_unique<code_gen_productionInfo>(),
        //struct_declarator->declarator : constant_expr
        make_unique<code_gen_productionInfo>(),
        //struct_declarator->declarator
        make_unique<code_gen_productionInfo>(),
        //enum_specifier->enum { enumerator_list }
        make_unique<code_gen_productionInfo>(),
        //enum_specifier->enum { enumerator_list , }
        make_unique<code_gen_productionInfo>(),
        //enum_specifier->enum id { enumerator_list }
        make_unique<code_gen_productionInfo>(),
        //enum_specifier->enum id { enumerator_list , }
        make_unique<code_gen_productionInfo>(),
        //enum_specifier->enum id
        make_unique<code_gen_productionInfo>(),
        //enumerator_list->enumerator
        make_unique<code_gen_productionInfo>(),
        //enumerator_list->enumerator_list , enumerator
        make_unique<code_gen_productionInfo>(),
        //enumerator->id = constant_expr
        make_unique<code_gen_productionInfo>(),
        //enumerator->id
        make_unique<code_gen_productionInfo>(),
        //atomic_type_specifier->_Atomic ( type_name )
        make_unique<code_gen_productionInfo>(),
        //type_qualifier->const
        make_unique<code_gen_productionInfo>(),
        //type_qualifier->restrict
        make_unique<code_gen_productionInfo>(),
        //type_qualifier->volatile
        make_unique<code_gen_productionInfo>(),
        //type_qualifier->_Atomic
        make_unique<code_gen_productionInfo>(),
        //function_specifier->inline
        make_unique<code_gen_productionInfo>(),
        //function_specifier->_Noreturn
        make_unique<code_gen_productionInfo>(),
        //alignment_specifier->_Alignas ( type_name )
        make_unique<code_gen_productionInfo>(),
        //alignment_specifier->_Alignas ( constant_expr )
        make_unique<code_gen_productionInfo>(),
        //declarator->pointer direct_declarator
        make_unique<code_gen_productionInfo>(),
        //declarator->direct_declarator
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->id
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->( declarator )
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ * ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ static type_qualifier_list assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ static assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ type_qualifier_list * ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ type_qualifier_list static assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ type_qualifier_list assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ type_qualifier_list ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator [ assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator ( )
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator ( parameter_type_list )
        make_unique<code_gen_productionInfo>(),
        //direct_declarator->direct_declarator ( identifier_list )
        make_unique<code_gen_productionInfo>(),
        //pointer->*
        make_unique<code_gen_productionInfo>(),
        //pointer->* pointer
        make_unique<code_gen_productionInfo>(),
        //pointer->* type_qualifier_list
        make_unique<code_gen_productionInfo>(),
        //pointer->* type_qualifier_list pointer
        make_unique<code_gen_productionInfo>(),
        //type_qualifier_list->type_qualifier
        make_unique<code_gen_productionInfo>(),
        //type_qualifier_list->type_qualifier_list type_qualifier
        make_unique<code_gen_productionInfo>(),
        //parameter_type_list->parameter_list
        make_unique<code_gen_productionInfo>(),
        //parameter_type_list->parameter_list , ...
        make_unique<code_gen_productionInfo>(),
        //parameter_list->parameter_declaration
        make_unique<code_gen_productionInfo>(),
        //parameter_list->parameter_list , parameter_declaration
        make_unique<code_gen_productionInfo>(),
        //parameter_declaration->declaration_specifiers declarator
        make_unique<code_gen_productionInfo>(),
        //parameter_declaration->declaration_specifiers abstract_declarator
        make_unique<code_gen_productionInfo>(),
        //parameter_declaration->declaration_specifiers
        make_unique<code_gen_productionInfo>(),
        //identifier_list->id
        make_unique<code_gen_productionInfo>(),
        //identifier_list->identifier_list , id
        make_unique<code_gen_productionInfo>(),
        //type_name->specifier_qualifier_list abstract_declarator
        make_unique<code_gen_productionInfo>(),
        //type_name->specifier_qualifier_list
        make_unique<code_gen_productionInfo>(),
        //abstract_declarator->pointer direct_abstract_declarator
        make_unique<code_gen_productionInfo>(),
        //abstract_declarator->pointer
        make_unique<code_gen_productionInfo>(),
        //abstract_declarator->direct_abstract_declarator
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->( abstract_declarator )
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[  ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[ * ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[ static type_qualifier_list assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[ static assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[ type_qualifier_list assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[ type_qualifier_list static assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[ type_qualifier_list ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->[ assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [  ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [ * ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [ static type_qualifier_list assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [ static assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list static assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator [ assignment_expr ]
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->(  )
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->( parameter_type_list )
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator (  )
        make_unique<code_gen_productionInfo>(),
        //direct_abstract_declarator->direct_abstract_declarator ( parameter_type_list )
        make_unique<code_gen_productionInfo>(),
        //initializer->{ initializer_list }
        make_unique<code_gen_productionInfo>(),
        //initializer->{ initializer_list , }
        make_unique<code_gen_productionInfo>(),
        //initializer->assignment_expr
        make_unique<code_gen_productionInfo>(),
        //initializer_list->designation initializer
        make_unique<code_gen_productionInfo>(),
        //initializer_list->initializer
        make_unique<code_gen_productionInfo>(),
        //initializer_list->initializer_list , designation initializer
        make_unique<code_gen_productionInfo>(),
        //initializer_list->initializer_list , initializer
        make_unique<code_gen_productionInfo>(),
        //designation->designator_list =
        make_unique<code_gen_productionInfo>(),
        //designator_list->designator
        make_unique<code_gen_productionInfo>(),
        //designator_list->designator_list designator
        make_unique<code_gen_productionInfo>(),
        //designator->. id
        make_unique<code_gen_productionInfo>(),
        //designator->[ constant_expr ]
        make_unique<code_gen_productionInfo>(),
        //static_assert_declaration->_Static_assert ( constant_expr , str )
        make_unique<code_gen_productionInfo>(),
        //expr->assignment_expr
        make_unique<gen_code_expr2assign2>(),
        //expr->expr , assignment_expr
        make_unique<gen_code_expr2assign1>(),
        //constant_expr->conditional_expr
        make_unique<code_genInChild>(),
        //assignment_expr->conditional_expr
        make_unique<gen_code_assign2cond>(),
        //assignment_expr->unary_expr assignment_operator assignment_expr
        make_unique<gen_code_assign>(),
        //assignment_operator->=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->*=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->/=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->%=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->+=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->-=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator-><<=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->>>=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->&=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->^=
        make_unique<code_gen_productionInfo>(),
        //assignment_operator->|=
        make_unique<code_gen_productionInfo>(),
        //conditional_expr->logic_or_expr
        make_unique<gen_code_cond2or>(),
        //conditional_expr->logic_or_expr ? expr : conditional_expr
        make_unique<code_gen_productionInfo>(),
        //logic_or_expr->logic_and_expr
        make_unique<gen_code_logic_or2and>(),
        //logic_or_expr->logic_or_expr || logic_and_expr
        make_unique<gen_code_logic_or>(),
        //logic_and_expr->or_expr
        make_unique<gen_code_logicand2or>(),
        //logic_and_expr->logic_and_expr && or_expr
        make_unique<gen_code_rule_andExpr>(),
        //or_expr->xor_expr
        make_unique<code_genInChildC>(),
        //or_expr->or_expr | xor_expr
        make_unique<gen_code_rule_orExpr>(),
        //xor_expr->and_expr
        make_unique<code_genInChildC>(),
        //xor_expr->xor_expr ^ and_expr
        make_unique<gen_code_rule_xorExpr>(),
        //and_expr->eq_expr
        make_unique<code_genInChildC>(),
        //and_expr->and_expr & eq_expr
        make_unique<gen_code_rule_andExpr>(),
        //eq_expr->relational_expr
        make_unique<code_genInChildC>(),
        //eq_expr->eq_expr == relational_expr
        make_unique<gen_code_rule_eqExpr>(),
        //eq_expr->eq_expr != relational_expr
        make_unique<gen_code_rule_neqExpr>(),
        //relational_expr->shift_expr
        make_unique<code_genInChildC>(),
        //relational_expr->relational_expr < shift_expr
        make_unique<gen_code_rule_ltExpr>(),
        //relational_expr->relational_expr > shift_expr
        make_unique<gen_code_rule_gtExpr>(),
        //relational_expr->relational_expr <= shift_expr
        make_unique<gen_code_rule_lteExpr>(),
        //relational_expr->relational_expr >= shift_expr
        make_unique<gen_code_rule_gteExpr>(),
        //shift_expr->add_expr
        make_unique<code_genInChildC>(),
        //shift_expr->shift_expr << add_expr
        make_unique<code_gen_productionInfo>(),
        //shift_expr->shift_expr >> add_expr
        make_unique<code_gen_productionInfo>(),
        //add_expr->mul_expr
        make_unique<code_genInChildC>(),
        //add_expr->add_expr + mul_expr
        make_unique<gen_code_rule_addExpr>(),
        //add_expr->add_expr - mul_expr
        make_unique<gen_code_rule_subExpr>(),
        //mul_expr->unary_expr
        make_unique<code_genInChildC>(),
        //mul_expr->mul_expr * unary_expr
        make_unique<gen_code_rule_mulExpr>(),
        //mul_expr->mul_expr / unary_expr
        make_unique<gen_code_rule_divExpr>(),
        //mul_expr->mul_expr % unary_expr
        make_unique<gen_code_rule_remExpr>(),
        //cast_expr->unary_expr
        make_unique<code_genInChildC>(),
        //cast_expr->( type_name ) cast_expr
        make_unique<code_gen_productionInfo>(),
        //unary_expr->postfix_expr
        make_unique<code_genInChildC>(),
        //unary_expr->unary_operator cast_expr
        make_unique<gen_code_unary_expr>(),
        //unary_expr->++ unary_expr
        make_unique<code_gen_productionInfo>(),
        //unary_expr->-- unary_expr
        make_unique<code_gen_productionInfo>(),
        //unary_expr->sizeof unary_expr
        make_unique<code_gen_productionInfo>(),
        //unary_expr->sizeof ( type_name )
        make_unique<code_gen_productionInfo>(),
        //unary_expr->_Alignof ( type_name )
        make_unique<code_gen_productionInfo>(),
        //unary_operator->&
        make_unique<code_gen_productionInfo>(),
        //unary_operator->*
        make_unique<code_gen_productionInfo>(),
        //unary_operator->+
        make_unique<code_gen_productionInfo>(),
        //unary_operator->-
        make_unique<code_gen_productionInfo>(),
        //unary_operator->~
        make_unique<code_gen_productionInfo>(),
        //unary_operator->!
        make_unique<code_gen_productionInfo>(),
        //argument_expression_list->assignment_expr
        make_unique<code_gen_productionInfo>(),
        //argument_expression_list->argument_expression_list , assignment_expr
        make_unique<code_gen_productionInfo>(),
        //postfix_expr->primary_expr
        make_unique<code_genInChildC>(),
        //postfix_expr->postfix_expr ( )
        make_unique<gen_code_postfix_expr2>(),
        //postfix_expr->postfix_expr . id
        make_unique<code_gen_productionInfo>(),
        //postfix_expr->postfix_expr -> id
        make_unique<code_gen_productionInfo>(),
        //postfix_expr->postfix_expr ++
        make_unique<code_gen_productionInfo>(),
        //postfix_expr->postfix_expr --
        make_unique<code_gen_productionInfo>(),
        //postfix_expr->postfix_expr [ expr ]
        make_unique<code_gen_productionInfo>(),
        //postfix_expr->postfix_expr ( argument_expression_list )
        make_unique<gen_code_postfix_expr3>(),
        //postfix_expr->( type_name ) { initializer_list }
        make_unique<code_gen_productionInfo>(),
        //postfix_expr->( type_name ) { initializer_list , }
        make_unique<code_gen_productionInfo>(),
        //String->str // str is just a token, like "hello"
        make_unique<code_gen_productionInfo>(),
        //String->__func__
        make_unique<code_gen_productionInfo>(),
        //generic_selection->_Generic ( assignment_expr , generic_assoc_list )
        make_unique<code_gen_productionInfo>(),
        //generic_assoc_list->generic_association
        make_unique<code_gen_productionInfo>(),
        //generic_assoc_list->generic_assoc_list , generic_association
        make_unique<code_gen_productionInfo>(),
        //generic_association->type_name : assignment_expr
        make_unique<code_gen_productionInfo>(),
        //generic_association->default : assignment_expr
        make_unique<code_gen_productionInfo>(),
        //constant->integer
        make_unique<code_gen_productionInfo>(),
        //constant->Float // Float is a token, like 3.14
        make_unique<code_gen_productionInfo>(),
        //constant->enumerate_constant
        make_unique<code_gen_productionInfo>(),
        //primary_expr->( expr )
        make_unique<gen_code_primary_expr2>(),
        //primary_expr->id // id is identifier, like abc
        make_unique<gen_code_primary_expr1>(),
        //primary_expr->constant
        make_unique<code_gen_productionInfo>(),
        //primary_expr->String // String is not a token
        make_unique<code_gen_productionInfo>(),
        //primary_expr->generic_selection
        make_unique<code_gen_productionInfo>(),
};