
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
#include "attr_rule_jump.h"

using std::unique_ptr;
using std::make_unique;
unique_ptr<ProductionInfo> C_RuleAttributesPool::ruleAttrTable[]={
    //translation_unit->external_declaration
    make_unique<AttrRuleDoNothing>(),

    //translation_unit->translation_unit external_declaration
    make_unique<AttrRuleDoNothing>(),

    //external_declaration->function_definition
    make_unique<AttrRuleDoNothing>(false),

    //external_declaration->declaration
    make_unique<AttrRuleSetDeclare>(),

    //function_definition->declaration_specifiers declarator declaration_list compound_statement
    make_unique<AttrRuleError>(),

    //function_definition->declaration_specifiers declarator compound_statement
    make_unique<AttrRuleFunc>(),

    //statement->labeled_statement
    make_unique<AttrRuleDoNothing>(false),

    //statement->compound_statement
    make_unique<AttrRuleDoNothing>(false),

    //statement->expression_statement
    make_unique<AttrRuleDoNothing>(false),

    //statement->selection_statement
    make_unique<AttrRuleDoNothing>(false),

    //statement->iteration_statement
    make_unique<AttrRuleDoNothing>(false),

    //statement->jump_statement
    make_unique<AttrRuleDoNothing>(false),
    //labeled_statement->id : statement
    make_unique<AttrRule>(),
    //labeled_statement->case constant_expr : statement
    make_unique<AttrRule>(),
    //labeled_statement->default : statement
    make_unique<AttrRule>(),

    //compound_statement->{ }
    make_unique<AttrRuleCompound>(),

    //compound_statement->{ block_item_list }
    make_unique<AttrRuleCompound>(),

    //block_item_list->block_item
    make_unique<AttrRuleDoNothing>(false),

    //block_item_list->block_item_list block_item
    make_unique<AttrRuleDoNothing>(false),

    //block_item->declaration
    make_unique<AttrRuleSetDeclare>(),

    //block_item->statement
    make_unique<AttrRuleDoNothing>(),

    //expression_statement->;
    make_unique<AttrRuleNull>(),

    //expression_statement->expr ;
    make_unique<AttrRuleDoNothing>(),

    //selection_statement->if ( expr ) statement else statement
    make_unique<AttrRuleSelection>(),

    //selection_statement->if ( expr ) statement
    make_unique<AttrRuleSelection>(),
    //selection_statement->switch ( expr ) statement
    make_unique<AttrRule>(),

    //iteration_statement->while ( expr ) statement
    make_unique<AttrRuleWhile>(),

    //iteration_statement->do statement while ( expr )
    make_unique<AttrRule>(),
    //iteration_statement->for ( expression_statement expression_statement ) statement
    make_unique<AttrRule>(),
    //iteration_statement->for ( expression_statement expression_statement expr ) statement
    make_unique<AttrRule>(),
    //iteration_statement->for ( declaration expression_statement ) statement
    make_unique<AttrRule>(),
    //iteration_statement->for ( declaration expression_statement expr ) statement
    make_unique<AttrRule>(),
    //jump_statement->goto id ;
    make_unique<AttrRule>(),
    //jump_statement->continue ;
    make_unique<AttrRule>(),
    //jump_statement->break ;
    make_unique<AttrRule>(),
    //jump_statement->return ;
    make_unique<AttrRuleNull>(),
    //jump_statement->return expr ;
    make_unique<AttrRuleReturn>(),

    //declaration_list->declaration
    make_unique<AttrRuleDoNothing>(),

    //declaration_list->declaration_list declaration
    make_unique<AttrRuleDoNothing>(),

    //declaration->declaration_specifiers ;
    make_unique<AttrRule>(),

    //declaration->declaration_specifiers init_declarator_list ;
    make_unique<AttrRuleDeclaration>(),

    //declaration->static_assert_declaration
    make_unique<AttrRule>(),

    //declaration_specifiers->storage_class_specifier
    make_unique<AttrRule>(),

    //declaration_specifiers->storage_class_specifier declaration_specifiers
    make_unique<AttrRule>(),

    //declaration_specifiers->type_specifier
    make_unique<AttrRuleDeclSpec>(),

    //declaration_specifiers->type_specifier declaration_specifiers
    make_unique<AttrRule>(),

    //declaration_specifiers->type_qualifier
    make_unique<AttrRule>(),
    //declaration_specifiers->function_specifier
    make_unique<AttrRule>(),
    //declaration_specifiers->alignment_specifier
    make_unique<AttrRule>(),
    //declaration_specifiers->type_qualifier declaration_specifiers
    make_unique<AttrRule>(),
    //declaration_specifiers->function_specifier declaration_specifiers
    make_unique<AttrRule>(),
    //declaration_specifiers->alignment_specifier declaration_specifiers
    make_unique<AttrRule>(),

    //init_declarator_list->init_declarator
    make_unique<AttrRuleInitList>(),
    //init_declarator_list->init_declarator_list , init_declarator
    make_unique<AttrRuleInitListMulti>(),

    //init_declarator->declarator
    make_unique<AttrRuleInitDecl>(),
    //init_declarator->declarator = initializer
    make_unique<AttrRule>(),
    //storage_class_specifier->typedef
    make_unique<AttrRule>(),
    //storage_class_specifier->extern
    make_unique<AttrRule>(),
    //storage_class_specifier->static
    make_unique<AttrRule>(),
    //storage_class_specifier->_Thread_local
    make_unique<AttrRule>(),
    //storage_class_specifier->auto
    make_unique<AttrRule>(),
    //storage_class_specifier->register
    make_unique<AttrRule>(),

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
    make_unique<AttrRule>(),

    //type_specifier->struct_or_union_specifier
    make_unique<AttrRule>(),

    //type_specifier->enum_specifier
    make_unique<AttrRule>(),

    //type_specifier->typedef_name
    make_unique<AttrRule>(),

    //struct_or_union_specifier->struct_or_union { struct_declaration_list }
    make_unique<AttrRule>(),

    //struct_or_union_specifier->struct_or_union id { struct_declaration_list }
    make_unique<AttrRule>(),
    //struct_or_union_specifier->struct_or_union id
    make_unique<AttrRule>(),
    //struct_or_union->struct
    make_unique<AttrRule>(),
    //struct_or_union->union
    make_unique<AttrRule>(),
    //struct_declaration_list->struct_declaration
    make_unique<AttrRule>(),
    //struct_declaration_list->struct_declaration_list struct_declaration
    make_unique<AttrRule>(),
    //struct_declaration->specifier_qualifier_list ;
    make_unique<AttrRule>(),
    //struct_declaration->specifier_qualifier_list struct_declarator_list ;
    make_unique<AttrRule>(),
    //struct_declaration->static_assert_declaration
    make_unique<AttrRule>(),
    //specifier_qualifier_list->type_specifier
    make_unique<AttrRule>(),
    //specifier_qualifier_list->type_qualifier
    make_unique<AttrRule>(),
    //specifier_qualifier_list->type_specifier specifier_qualifier_list
    make_unique<AttrRule>(),
    //specifier_qualifier_list->type_qualifier specifier_qualifier_list
    make_unique<AttrRule>(),
    //struct_declarator_list->struct_declarator
    make_unique<AttrRule>(),
    //struct_declarator_list->struct_declarator_list , struct_declarator
    make_unique<AttrRule>(),
    //struct_declarator->: constant_expr
    make_unique<AttrRule>(),
    //struct_declarator->declarator : constant_expr
    make_unique<AttrRule>(),
    //struct_declarator->declarator
    make_unique<AttrRule>(),
    //enum_specifier->enum { enumerator_list }
    make_unique<AttrRule>(),
    //enum_specifier->enum { enumerator_list , }
    make_unique<AttrRule>(),
    //enum_specifier->enum id { enumerator_list }
    make_unique<AttrRule>(),
    //enum_specifier->enum id { enumerator_list , }
    make_unique<AttrRule>(),
    //enum_specifier->enum id
    make_unique<AttrRule>(),

    //enumerator_list->enumerator
    make_unique<AttrRule>(),

    //enumerator_list->enumerator_list , enumerator
    make_unique<AttrRule>(),

    //enumerator->id = constant_expr
    make_unique<AttrRule>(),

    //enumerator->id
    make_unique<AttrRule>(),

    //atomic_type_specifier->_Atomic ( type_name )
    make_unique<AttrRule>(),

    //type_qualifier->const
    make_unique<AttrRule>(),

    //type_qualifier->restrict
    make_unique<AttrRule>(),

    //type_qualifier->volatile
    make_unique<AttrRule>(),

    //type_qualifier->_Atomic
    make_unique<AttrRule>(),

    //function_specifier->inline
    make_unique<AttrRule>(),

    //function_specifier->_Noreturn
    make_unique<AttrRule>(),

    //alignment_specifier->_Alignas ( type_name )
    make_unique<AttrRule>(),

    //alignment_specifier->_Alignas ( constant_expr )
    make_unique<AttrRule>(),

    //declarator->pointer direct_declarator
    make_unique<AttrRuleDeclDirectDeclPointer>(),

    //declarator->direct_declarator
    make_unique<AttrRuleDeclDirectDecl>(),

    //direct_declarator->id
    make_unique<AttrRuleDirectDeclSingleId>(),

    //direct_declarator->( declarator )
    make_unique<AttrRule>(),

    //direct_declarator->direct_declarator [ ]
    make_unique<AttrRule>(),

    //direct_declarator->direct_declarator [ * ]
    make_unique<AttrRule>(),

    //direct_declarator->direct_declarator [ static type_qualifier_list assignment_expr ]
    make_unique<AttrRule>(),

    //direct_declarator->direct_declarator [ static assignment_expr ]
    make_unique<AttrRule>(),
    //direct_declarator->direct_declarator [ type_qualifier_list * ]
    make_unique<AttrRule>(),
    //direct_declarator->direct_declarator [ type_qualifier_list static assignment_expr ]
    make_unique<AttrRule>(),
    //direct_declarator->direct_declarator [ type_qualifier_list assignment_expr ]
    make_unique<AttrRule>(),
    //direct_declarator->direct_declarator [ type_qualifier_list ]
    make_unique<AttrRule>(),
    //direct_declarator->direct_declarator [ assignment_expr ]
    make_unique<AttrRuleDirectDeclArray1>(),
    //direct_declarator->direct_declarator ( )
    make_unique<AttrRuleDirectDeclFuncWithoutPara>(),

    //direct_declarator->direct_declarator ( parameter_type_list )
    make_unique<AttrRuleDirectDeclFuncWithPara>(),
    //direct_declarator->direct_declarator ( identifier_list )
    make_unique<AttrRule>(),
    //pointer->*
    make_unique<AttrRulePointer1>(),
    //pointer->* pointer
    make_unique<AttrRulePointer2>(),
    //pointer->* type_qualifier_list
    make_unique<AttrRule>(),
    //pointer->* type_qualifier_list pointer
    make_unique<AttrRule>(),
    //type_qualifier_list->type_qualifier
    make_unique<AttrRule>(),
    //type_qualifier_list->type_qualifier_list type_qualifier
    make_unique<AttrRule>(),

    //parameter_type_list->parameter_list
    make_unique<AttrRuleParamTypeList>(false),

    //parameter_type_list->parameter_list , ...
    make_unique<AttrRuleParamTypeList>(true),

    //parameter_list->parameter_declaration
    make_unique<AttrRuleParamListSingleDecl>(),

    //parameter_list->parameter_list , parameter_declaration
    make_unique<AttrRuleParamListMultiDecl>(),

    //parameter_declaration->declaration_specifiers declarator
    make_unique<AttrRuleParameterDecl>(),

    //parameter_declaration->declaration_specifiers abstract_declarator
    make_unique<AttrRule>(),
    //parameter_declaration->declaration_specifiers
    make_unique<AttrRule>(),
    //identifier_list->id
    make_unique<AttrRule>(),
    //identifier_list->identifier_list , id
    make_unique<AttrRule>(),
    //type_name->specifier_qualifier_list abstract_declarator
    make_unique<AttrRule>(),
    //type_name->specifier_qualifier_list
    make_unique<AttrRule>(),
    //abstract_declarator->pointer direct_abstract_declarator
    make_unique<AttrRule>(),
    //abstract_declarator->pointer
    make_unique<AttrRule>(),
    //abstract_declarator->direct_abstract_declarator
    make_unique<AttrRule>(),
    //direct_abstract_declarator->( abstract_declarator )
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[  ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[ * ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[ static type_qualifier_list assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[ static assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[ type_qualifier_list assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[ type_qualifier_list static assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[ type_qualifier_list ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->[ assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [  ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [ * ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [ static type_qualifier_list assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [ static assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list static assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [ type_qualifier_list ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator [ assignment_expr ]
    make_unique<AttrRule>(),
    //direct_abstract_declarator->(  )
    make_unique<AttrRule>(),
    //direct_abstract_declarator->( parameter_type_list )
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator (  )
    make_unique<AttrRule>(),
    //direct_abstract_declarator->direct_abstract_declarator ( parameter_type_list )
    make_unique<AttrRule>(),
    //initializer->{ initializer_list }
    make_unique<AttrRule>(),
    //initializer->{ initializer_list , }
    make_unique<AttrRule>(),
    //initializer->assignment_expr
    make_unique<AttrRule>(),
    //initializer_list->designation initializer
    make_unique<AttrRule>(),
    //initializer_list->initializer
    make_unique<AttrRule>(),
    //initializer_list->initializer_list , designation initializer
    make_unique<AttrRule>(),
    //initializer_list->initializer_list , initializer
    make_unique<AttrRule>(),
    //designation->designator_list =
    make_unique<AttrRule>(),
    //designator_list->designator
    make_unique<AttrRule>(),
    //designator_list->designator_list designator
    make_unique<AttrRule>(),
    //designator->. id
    make_unique<AttrRule>(),
    //designator->[ constant_expr ]
    make_unique<AttrRule>(),
    //static_assert_declaration->_Static_assert ( constant_expr , str )
    make_unique<AttrRule>(),

    //expr->assignment_expr
    make_unique<AttrRuleExprDoNothing>(),
    //expr->expr , assignment_expr
    make_unique<AttrRule>(),
    //constant_expr->conditional_expr
    make_unique<AttrRule>(),

    //assignment_expr->conditional_expr
    make_unique<AttrRuleExprDoNothing>(),

    //assignment_expr->unary_expr assignment_operator assignment_expr
    make_unique<AttrRuleAssignExprAssign>(),

    //assignment_operator->=
    make_unique<AttrRuleOperator>(OperatorType::kEqual),
    //assignment_operator->*=
    make_unique<AttrRuleOperator>(OperatorType::kMultiplyEqual),
    //assignment_operator->/=
    make_unique<AttrRuleOperator>(OperatorType::kDivEqual),
    //assignment_operator->%=
    make_unique<AttrRuleOperator>(OperatorType::kModuleEqual),
    //assignment_operator->+=
    make_unique<AttrRuleOperator>(OperatorType::kPlusEqual),
    //assignment_operator->-=
    make_unique<AttrRuleOperator>(OperatorType::kMinusEqual),
    //assignment_operator-><<=
    make_unique<AttrRuleOperator>(OperatorType::kLeftShiftEqual),
    //assignment_operator->>>=
    make_unique<AttrRuleOperator>(OperatorType::kRightShiftEqual),
    //assignment_operator->&=
    make_unique<AttrRuleOperator>(OperatorType::kAndEqual),
    //assignment_operator->^=
    make_unique<AttrRuleOperator>(OperatorType::kXorEqual),
    //assignment_operator->|=
    make_unique<AttrRuleOperator>(OperatorType::kOrEqual),

    //conditional_expr->logic_or_expr
    make_unique<AttrRuleExprDoNothing>(),
    //conditional_expr->logic_or_expr ? expr : conditional_expr
    make_unique<AttrRule>(),

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
    make_unique<AttrRule>(),

    //xor_expr->and_expr
    make_unique<AttrRuleExprDoNothing>(),
    //xor_expr->xor_expr ^ and_expr
    make_unique<AttrRule>(),

    //and_expr->eq_expr
    make_unique<AttrRuleExprDoNothing>(),
    //and_expr->and_expr & eq_expr
    make_unique<AttrRule>(),

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
    make_unique<AttrRule>(),
    //shift_expr->shift_expr >> add_expr
    make_unique<AttrRule>(),

    //add_expr->mul_expr
    make_unique<AttrRuleExprDoNothing>(),

    //add_expr->add_expr + mul_expr
    make_unique<AttrRuleAddExpr>(),

    //add_expr->add_expr - mul_expr
    make_unique<AttrRuleMinusExpr>(),

    //mul_expr->unary_expr
    make_unique<AttrRuleExprDoNothing>(),

    //mul_expr->mul_expr * unary_expr
    make_unique<AttrRuleMultExpr>(),

    //mul_expr->mul_expr / unary_expr
    make_unique<AttrRuleDivExpr>(),

    //mul_expr->mul_expr % unary_expr
    make_unique<AttrRuleRemExpr>(),

    //cast_expr->unary_expr
    make_unique<AttrRuleExprDoNothing>(),
    //cast_expr->( type_name ) cast_expr
    make_unique<AttrRule>(),

    //unary_expr->postfix_expr
    make_unique<AttrRuleExprDoNothing>(),

    //unary_expr->unary_operator cast_expr
    make_unique<AttrRuleUnaryExpr>(),
    //unary_expr->++ unary_expr
    make_unique<AttrRule>(),
    //unary_expr->-- unary_expr
    make_unique<AttrRule>(),
    //unary_expr->sizeof unary_expr
    make_unique<AttrRule>(),
    //unary_expr->sizeof ( type_name )
    make_unique<AttrRule>(),
    //unary_expr->_Alignof ( type_name )
    make_unique<AttrRule>(),
    //unary_operator->&
    make_unique<AttrRule>(),
    //unary_operator->*
    make_unique<AttrRule>(),
    //unary_operator->+
    make_unique<AttrRule>(),

    //unary_operator->-
    make_unique<AttrRuleUnaryOperator>(UnaryOperatorType::kMinus),
    //unary_operator->~
    make_unique<AttrRule>(),

    //unary_operator->!
    make_unique<AttrRuleUnaryOperator>(UnaryOperatorType::kExclaim),

    //argument_expression_list->assignment_expr
    make_unique<AttrRuleDoNothing>(),

    //argument_expression_list->argument_expression_list , assignment_expr
    make_unique<AttrRule>(),

    //postfix_expr->primary_expr
    make_unique<AttrRuleExprDoNothing>(),

    //postfix_expr->postfix_expr ( )
    make_unique<AttrRulePostfixExprFuncApp0>(),
    //postfix_expr->postfix_expr . id
    make_unique<AttrRule>(),
    //postfix_expr->postfix_expr -> id
    make_unique<AttrRule>(),
    //postfix_expr->postfix_expr ++
    make_unique<AttrRule>(),
    //postfix_expr->postfix_expr --
    make_unique<AttrRule>(),
    //postfix_expr->postfix_expr [ expr ]
    make_unique<AttrRulePostfixExprArray>(),

    //postfix_expr->postfix_expr ( argument_expression_list )
    make_unique<AttrRulePostfixExprFuncApp1>(),
    //postfix_expr->( type_name ) { initializer_list }
    make_unique<AttrRule>(),
    //postfix_expr->( type_name ) { initializer_list , }
    make_unique<AttrRule>(),

        //TODO:
    //String->str // str is just a token, like "hello"
    make_unique<AttrRuleConstant<TokenType::STRING>>(),
    //String->__func__
    make_unique<AttrRule>(),
    //generic_selection->_Generic ( assignment_expr , generic_assoc_list )
    make_unique<AttrRule>(),
    //generic_assoc_list->generic_association
    make_unique<AttrRule>(),
    //generic_assoc_list->generic_assoc_list , generic_association
    make_unique<AttrRule>(),
    //generic_association->type_name : assignment_expr
    make_unique<AttrRule>(),
    //generic_association->default : assignment_expr
    make_unique<AttrRule>(),

    //constant->integer // token
    make_unique<AttrRuleConstant<TokenType::INTEGER>>(),

    //constant->Float // Float is a token, like 3.14
    make_unique<AttrRuleConstant<TokenType::FLOAT>>(),
    //constant->enumerate_constant
    make_unique<AttrRule>(),

    //primary_expr->( expr )
    make_unique<AttrRulePrimaryExprParens>(),

    //primary_expr->id // id is identifier, like abc
    make_unique<AttrRulePrimaryExprId>(),

    //primary_expr->constant
    make_unique<AttrRulePrimaryExprConstant>(),

        //TODO:
    //primary_expr->String // String is not a token
    make_unique<AttrRulePrimaryExprConstant>(),
    //primary_expr->generic_selection
    make_unique<AttrRule>(),

};
