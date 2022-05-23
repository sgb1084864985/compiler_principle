
//
// Created by zlz on 22-4-29.
//

#include "C_rule_attr.h"
#include "attr_rule_func.h"
#include "attr_rule_compound_stmt.h"
#include "attr_rule_decl.h"
#include "attr_rule_type_spec.h"
#include "attr_rule_expr.h"
#include "attr_rule_select.h"
#include "attr_rule_while.h"
#include "attr_rule_params.h"

using std::unique_ptr;
using std::make_unique;
unique_ptr<ProductionInfo> C_RuleAttributesPool::ruleAttrTable[]={
    //translation_unit->external_declaration
    make_unique<AttrRuleDoNothing>(),

    //translation_unit->translation_unit external_declaration
    make_unique<AttrRuleDoNothing>(),

    //external_declaration->function_definition
    make_unique<AttrRuleDoNothing>(),

    //external_declaration->declaration
    make_unique<AttrRuleDoNothing>(),

    //function_definition->declaration_specifiers declarator declaration_list compound_statement
    make_unique<AttrRuleError>(),

        //TODO:
    //function_definition->declaration_specifiers declarator compound_statement
    make_unique<AttrRuleFunc>(),

    //statement->labeled_statement
    make_unique<AttrRuleDoNothing>(),

    //statement->compound_statement
    make_unique<AttrRuleDoNothing>(),

    //statement->expression_statement
    make_unique<AttrRuleDoNothing>(),

    //statement->selection_statement
    make_unique<AttrRuleDoNothing>(),

    //statement->iteration_statement
    make_unique<AttrRuleDoNothing>(),

    //statement->jump_statement
    make_unique<AttrRuleDoNothing>(),
    //labeled_statement->id : statement
    make_unique<ProductionInfo>(),
    //labeled_statement->case constant_expr : statement
    make_unique<ProductionInfo>(),
    //labeled_statement->default : statement
    make_unique<ProductionInfo>(),

        //TODO:
    //compound_statement->{ }
    make_unique<AttrRuleDoNothing>(),

    //compound_statement->{ block_item_list }
    make_unique<AttrRuleCompound>(),

    //block_item_list->block_item
    make_unique<AttrRuleDoNothing>(),

    //block_item_list->block_item_list block_item
    make_unique<AttrRuleDoNothing>(),

    //block_item->declaration
    make_unique<AttrRuleDoNothing>(),

    //block_item->statement
    make_unique<AttrRuleDoNothing>(),

    //expression_statement->;
    make_unique<AttrRuleDoNothing>(),

    //expression_statement->expr ;
    make_unique<AttrRuleDoNothing>(),

    //selection_statement->if ( expr ) statement else statement
    make_unique<AttrRuleSelection>(),

    //selection_statement->if ( expr ) statement
    make_unique<AttrRuleSelection>(),
    //selection_statement->switch ( expr ) statement
    make_unique<ProductionInfo>(),

    //iteration_statement->while ( expr ) statement
    make_unique<AttrRuleWhile>(),

    //iteration_statement->do statement while ( expr )
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( expression_statement expression_statement ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( expression_statement expression_statement expr ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( declaration expression_statement ) statement
    make_unique<ProductionInfo>(),
    //iteration_statement->for ( declaration expression_statement expr ) statement
    make_unique<ProductionInfo>(),
    //jump_statement->goto id ;
    make_unique<ProductionInfo>(),
    //jump_statement->continue ;
    make_unique<ProductionInfo>(),
    //jump_statement->break ;
    make_unique<ProductionInfo>(),
    //jump_statement->return ;
    make_unique<ProductionInfo>(),
    //jump_statement->return expr ;
    make_unique<ProductionInfo>(),

    //declaration_list->declaration
    make_unique<AttrRuleDoNothing>(),

    //declaration_list->declaration_list declaration
    make_unique<ProductionInfo>(),

    //declaration->declaration_specifiers ;
    make_unique<ProductionInfo>(),

    //declaration->declaration_specifiers init_declarator_list ;
    make_unique<AttrRuleDeclaration>(),

    //declaration->static_assert_declaration
    make_unique<ProductionInfo>(),

    //declaration_specifiers->storage_class_specifier
    make_unique<ProductionInfo>(),

    //declaration_specifiers->storage_class_specifier declaration_specifiers
    make_unique<ProductionInfo>(),

    //declaration_specifiers->type_specifier
    make_unique<AttrRuleDeclSpec>(),

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
    make_unique<AttrRuleInitList>(),
    //init_declarator_list->init_declarator_list , init_declarator
    make_unique<ProductionInfo>(),

    //init_declarator->declarator
    make_unique<AttrRuleInitDecl>(),
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
    make_unique<AttrRuleTypeSpec<CTS::VOID>>(),

    //type_specifier->char
    make_unique<AttrRuleTypeSpec<CTS::CHAR>>(),

    //type_specifier->short
    make_unique<AttrRuleTypeSpec<CTS::SHORT>>(),

    //type_specifier->int
    make_unique<AttrRuleTypeSpec<CTS::INT>>(),

    //type_specifier->long
    make_unique<AttrRuleTypeSpec<CTS::LONG>>(),

    //type_specifier->float
    make_unique<AttrRuleTypeSpec<CTS::FLOAT>>(),

    //type_specifier->double
    make_unique<AttrRuleTypeSpec<CTS::DOUBLE>>(),

    //type_specifier->signed
    make_unique<AttrRuleTypeSpec<CTS::type_unset>>(),

    //type_specifier->unsigned
    make_unique<AttrRuleTypeSpec<CTS::type_unset>>(),

    //type_specifier->_Bool
    make_unique<AttrRuleDoNothing>(),

    //type_specifier->_Complex
    make_unique<AttrRuleDoNothing>(),

    //type_specifier->_Imaginary
    make_unique<AttrRuleDoNothing>(),

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
    make_unique<AttrRuleDeclDirectDecl>(),

    //direct_declarator->id
    make_unique<AttrRuleDirectDeclSingleId>(),

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
    make_unique<AttrRuleDirectDeclFuncWithoutPara>(),

    //direct_declarator->direct_declarator ( parameter_type_list )
    make_unique<AttrRuleDirectDeclFuncWithPara>(),
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
    make_unique<AttrRuleParamTypeList>(false),

    //parameter_type_list->parameter_list , ...
    make_unique<AttrRuleParamTypeList>(true),

		// TODO
    //parameter_list->parameter_declaration
    make_unique<ProductionInfo>(),

        //TODO:
    //parameter_list->parameter_list , parameter_declaration
    make_unique<ProductionInfo>(),

        //TODO:
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

    //expr->assignment_expr
    make_unique<AttrRuleExprDoNothing>(),
    //expr->expr , assignment_expr
    make_unique<ProductionInfo>(),
    //constant_expr->conditional_expr
    make_unique<ProductionInfo>(),

    //assignment_expr->conditional_expr
    make_unique<AttrRuleExprDoNothing>(),

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
    make_unique<AttrRuleExprDoNothing>(),
    //conditional_expr->logic_or_expr ? expr : conditional_expr
    make_unique<ProductionInfo>(),

    //logic_or_expr->logic_and_expr
    make_unique<AttrRuleExprDoNothing>(),

    //logic_or_expr->logic_or_expr || logic_and_expr
    make_unique<AttrRuleLogicOrExpr>(),

    //logic_and_expr->or_expr
    make_unique<AttrRuleExprDoNothing>(),

    //logic_and_expr->logic_and_expr && or_expr
    make_unique<AttrRuleLogicAndExpr>(),

    //or_expr->xor_expr
    make_unique<AttrRuleExprDoNothing>(),

    //or_expr->or_expr | xor_expr
    make_unique<ProductionInfo>(),

    //xor_expr->and_expr
    make_unique<AttrRuleExprDoNothing>(),
    //xor_expr->xor_expr ^ and_expr
    make_unique<ProductionInfo>(),

    //and_expr->eq_expr
    make_unique<AttrRuleExprDoNothing>(),
    //and_expr->and_expr & eq_expr
    make_unique<ProductionInfo>(),

	//eq_expr->relational_expr
	make_unique<AttrRuleExprDoNothing>(),

	//eq_expr->eq_expr == relational_expr
    make_unique<AttrRuleEqExpr>(),

	//eq_expr->eq_expr != relational_expr
    make_unique<AttrRuleNotEqExpr>(),

	//relational_expr->shift_expr
    make_unique<AttrRuleExprDoNothing>(),

    //relational_expr->relational_expr < shift_expr
    make_unique<AttrRuleLessThanExpr>(),

    //relational_expr->relational_expr > shift_expr
    make_unique<AttrRuleGreaterThanExpr>(),

    //relational_expr->relational_expr <= shift_expr
    make_unique<AttrRuleLessEqualExpr>(),

    //relational_expr->relational_expr >= shift_expr
    make_unique<AttrRuleGreaterEqualExpr>(),

    //shift_expr->add_expr
    make_unique<AttrRuleExprDoNothing>(),
    //shift_expr->shift_expr << add_expr
    make_unique<ProductionInfo>(),
    //shift_expr->shift_expr >> add_expr
    make_unique<ProductionInfo>(),

    //add_expr->mul_expr
    make_unique<AttrRuleExprDoNothing>(),

        //TODO:
    //add_expr->add_expr + mul_expr
    make_unique<AttrRuleAddExpr>(),

        //TODO:
    //add_expr->add_expr - mul_expr
    make_unique<AttrRuleMinusExpr>(),

        //TODO:
    //mul_expr->unary_expr
    make_unique<AttrRuleExprDoNothing>(),

        //TODO:
    //mul_expr->mul_expr * unary_expr
    make_unique<AttrRuleMultExpr>(),

        //TODO:
    //mul_expr->mul_expr / unary_expr
    make_unique<AttrRuleDivExpr>(),

    //mul_expr->mul_expr % unary_expr
    make_unique<ProductionInfo>(),

        //TODO:
    //cast_expr->unary_expr
    make_unique<AttrRuleExprDoNothing>(),
    //cast_expr->( type_name ) cast_expr
    make_unique<ProductionInfo>(),

        //TODO:
    //unary_expr->postfix_expr
    make_unique<AttrRuleExprDoNothing>(),

        //TODO:
    //unary_expr->unary_operator cast_expr
    make_unique<AttrRuleUnaryExpr>(),
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

        //TODO:
    //unary_operator->-
    make_unique<AttrRuleUnaryOperator>(OperatorType::kMinus),
    //unary_operator->~
    make_unique<ProductionInfo>(),

        //TODO:
    //unary_operator->!
    make_unique<AttrRuleUnaryOperator>(OperatorType::kExclaim),

        //TODO:
    //argument_expression_list->assignment_expr
    make_unique<ProductionInfo>(),

        //TODO:
    //argument_expression_list->argument_expression_list , assignment_expr
    make_unique<ProductionInfo>(),

        //TODO:
    //postfix_expr->primary_expr
    make_unique<AttrRuleExprDoNothing>(),

        //TODO:
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
    //postfix_expr->postfix_expr [ expr ]
    make_unique<ProductionInfo>(),

        //TODO:
    //postfix_expr->postfix_expr ( argument_expression_list )
    make_unique<ProductionInfo>(),
    //postfix_expr->( type_name ) { initializer_list }
    make_unique<ProductionInfo>(),
    //postfix_expr->( type_name ) { initializer_list , }
    make_unique<ProductionInfo>(),

        //TODO:
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

        //TODO:
    //constant->integer // token
    make_unique<ProductionInfo>(),

        //TODO:
    //constant->Float // Float is a token, like 3.14
    make_unique<ProductionInfo>(),
    //constant->enumerate_constant
    make_unique<ProductionInfo>(),

        //TODO:
    //primary_expr->( expr )
    make_unique<ProductionInfo>(),

        //TODO:
    //primary_expr->id // id is identifier, like abc
    make_unique<ProductionInfo>(),

        //TODO:
    //primary_expr->constant
    make_unique<ProductionInfo>(),

        //TODO:
    //primary_expr->String // String is not a token
    make_unique<ProductionInfo>(),
    //primary_expr->generic_selection
    make_unique<ProductionInfo>(),

};
