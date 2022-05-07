#include "compiler.h"
#include "CProductions.h"
#include "Csymbols.hpp"
#include "C_rule_attr.h"
#include "C_rule_code.h"
#include <vector>


using std::vector;

vector<Production> &CProductions::getProductions(){
    // first non-terminal is the start non-terminal
    using AST::genTree;
    static vector<Production> productions={
        Production("translation_unit", "external_declaration", genTree<CSym::translation_unit>),
        Production("translation_unit", "translation_unit external_declaration", genTree<CSym::translation_unit>),

        Production("external_declaration", "function_definition", genTree<CSym::external_declaration>),
        Production("external_declaration", "declaration", genTree<CSym::external_declaration>),

        Production("function_definition", "declaration_specifiers declarator declaration_list compound_statement", genTree<CSym::function_definition>),
        Production("function_definition", "declaration_specifiers declarator compound_statement", genTree<CSym::function_definition>),

        Production("statement", "labeled_statement", genTree<CSym::statement>),
        Production("statement", "compound_statement", genTree<CSym::statement>),
        Production("statement", "expression_statement", genTree<CSym::statement>),
        Production("statement", "selection_statement", genTree<CSym::statement>),
        Production("statement", "iteration_statement", genTree<CSym::statement>),
        Production("statement", "jump_statement", genTree<CSym::statement>),

        Production("labeled_statement", "id : statement", genTree<CSym::labeled_statement>),
        Production("labeled_statement", "case constant_expr : statement", genTree<CSym::labeled_statement>),
        Production("labeled_statement", "default : statement", genTree<CSym::labeled_statement>),

        Production("compound_statement", "{ }", genTree<CSym::compound_statement>),
        Production("compound_statement", "{ block_item_list }", genTree<CSym::compound_statement>),

        Production("block_item_list", "block_item", genTree<CSym::block_item_list>),
        Production("block_item_list", "block_item_list block_item", genTree<CSym::block_item_list>),

        Production("block_item", "declaration", genTree<CSym::block_item>),
        Production("block_item", "statement", genTree<CSym::block_item>),

        Production("expression_statement", ";", genTree<CSym::expression_statement>),
        Production("expression_statement", "expr ;", genTree<CSym::expression_statement>),

        Production("selection_statement", "if ( expr ) statement else statement", genTree<CSym::selection_statement>),
        Production("selection_statement", "if ( expr ) statement", genTree<CSym::selection_statement>),
        Production("selection_statement", "switch ( expr ) statement", genTree<CSym::selection_statement>),

        Production("iteration_statement", "while ( expr ) statement", genTree<CSym::iteration_statement>),
        Production("iteration_statement", "do statement while ( expr )", genTree<CSym::iteration_statement>),
        Production("iteration_statement", "for ( expression_statement expression_statement ) statement", genTree<CSym::iteration_statement>),
        Production("iteration_statement", "for ( expression_statement expression_statement expr ) statement", genTree<CSym::iteration_statement>),
        Production("iteration_statement", "for ( declaration expression_statement ) statement", genTree<CSym::iteration_statement>),
        Production("iteration_statement", "for ( declaration expression_statement expr ) statement", genTree<CSym::iteration_statement>),

        Production("jump_statement", "goto id ;", genTree<CSym::jump_statement>),
        Production("jump_statement", "continue ;", genTree<CSym::jump_statement>),
        Production("jump_statement", "break ;", genTree<CSym::jump_statement>),
        Production("jump_statement", "return ;", genTree<CSym::jump_statement>),
        Production("jump_statement", "return expr ;", genTree<CSym::jump_statement>),

        Production("declaration_list", "declaration", genTree<CSym::declaration_list>),
        Production("declaration_list", "declaration_list declaration", genTree<CSym::declaration_list>),

        Production("declaration", "declaration_specifiers ;", genTree<CSym::declaration>),
        Production("declaration", "declaration_specifiers init_declarator_list ;", genTree<CSym::declaration>),
        Production("declaration", "static_assert_declaration", genTree<CSym::declaration>),

        Production("declaration_specifiers", "storage_class_specifier", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "storage_class_specifier declaration_specifiers", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "type_specifier", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "type_specifier declaration_specifiers", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "type_qualifier", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "function_specifier", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "alignment_specifier", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "type_qualifier declaration_specifiers", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "function_specifier declaration_specifiers", genTree<CSym::declaration_specifiers>),
        Production("declaration_specifiers", "alignment_specifier declaration_specifiers", genTree<CSym::declaration_specifiers>),

        Production("init_declarator_list", "init_declarator", genTree<CSym::init_declarator_list>),
        Production("init_declarator_list", "init_declarator_list , init_declarator", genTree<CSym::init_declarator_list>),

        Production("init_declarator", "declarator", genTree<CSym::init_declarator>),
        Production("init_declarator", "declarator = initializer", genTree<CSym::init_declarator>),

        Production("storage_class_specifier", "typedef", genTree<CSym::storage_class_specifier>),
        Production("storage_class_specifier", "extern", genTree<CSym::storage_class_specifier>),
        Production("storage_class_specifier", "static", genTree<CSym::storage_class_specifier>),
            Production("storage_class_specifier", "_Thread_local", genTree<CSym::storage_class_specifier>),
        Production("storage_class_specifier", "auto", genTree<CSym::storage_class_specifier>),
        Production("storage_class_specifier", "register", genTree<CSym::storage_class_specifier>),

        Production("type_specifier", "void", genTree<CSym::type_specifier>),
        Production("type_specifier", "char", genTree<CSym::type_specifier>),
        Production("type_specifier", "short", genTree<CSym::type_specifier>),
        Production("type_specifier", "int", genTree<CSym::type_specifier>),
        Production("type_specifier", "long", genTree<CSym::type_specifier>),
        Production("type_specifier", "float", genTree<CSym::type_specifier>),
        Production("type_specifier", "double", genTree<CSym::type_specifier>),
        Production("type_specifier", "signed", genTree<CSym::type_specifier>),
        Production("type_specifier", "unsigned", genTree<CSym::type_specifier>),
        Production("type_specifier", "_Bool", genTree<CSym::type_specifier>),
        Production("type_specifier", "_Complex", genTree<CSym::type_specifier>),
        Production("type_specifier", "_Imaginary", genTree<CSym::type_specifier>),
        Production("type_specifier", "atomic_type_specifier", genTree<CSym::type_specifier>),
        Production("type_specifier", "struct_or_union_specifier", genTree<CSym::type_specifier>),
        Production("type_specifier", "enum_specifier", genTree<CSym::type_specifier>),
        Production("type_specifier", "typedef_name", genTree<CSym::type_specifier>),
//        Production("type_specifier", "id", genTree<CSym::type_specifier>),

        Production("struct_or_union_specifier", "struct_or_union { struct_declaration_list }", genTree<CSym::struct_or_union_specifier>),
        Production("struct_or_union_specifier", "struct_or_union id { struct_declaration_list }", genTree<CSym::struct_or_union_specifier>),
        Production("struct_or_union_specifier", "struct_or_union id", genTree<CSym::struct_or_union_specifier>),

        Production("struct_or_union", "struct", genTree<CSym::struct_or_union>),
        Production("struct_or_union", "union", genTree<CSym::struct_or_union>),

        Production("struct_declaration_list", "struct_declaration", genTree<CSym::struct_declaration_list>),
        Production("struct_declaration_list", "struct_declaration_list struct_declaration", genTree<CSym::struct_declaration_list>),

        Production("struct_declaration", "specifier_qualifier_list ;", genTree<CSym::struct_declaration>),
        Production("struct_declaration", "specifier_qualifier_list struct_declarator_list ;", genTree<CSym::struct_declaration>),
        Production("struct_declaration", "static_assert_declaration", genTree<CSym::struct_declaration>),

        Production("specifier_qualifier_list", "type_specifier", genTree<CSym::specifier_qualifier_list>),
        Production("specifier_qualifier_list", "type_qualifier", genTree<CSym::specifier_qualifier_list>),
        Production("specifier_qualifier_list", "type_specifier specifier_qualifier_list", genTree<CSym::specifier_qualifier_list>),
        Production("specifier_qualifier_list", "type_qualifier specifier_qualifier_list", genTree<CSym::specifier_qualifier_list>),

        Production("struct_declarator_list", "struct_declarator", genTree<CSym::struct_declarator_list>),
        Production("struct_declarator_list", "struct_declarator_list , struct_declarator", genTree<CSym::struct_declarator_list>),

        Production("struct_declarator", ": constant_expr", genTree<CSym::struct_declarator>),
        Production("struct_declarator", "declarator : constant_expr", genTree<CSym::struct_declarator>),
        Production("struct_declarator", "declarator", genTree<CSym::struct_declarator>),

        Production("enum_specifier", "enum { enumerator_list }", genTree<CSym::enum_specifier>),
        Production("enum_specifier", "enum { enumerator_list , }", genTree<CSym::enum_specifier>),
        Production("enum_specifier", "enum id { enumerator_list }", genTree<CSym::enum_specifier>),
        Production("enum_specifier", "enum id { enumerator_list , }", genTree<CSym::enum_specifier>),
        Production("enum_specifier", "enum id", genTree<CSym::enum_specifier>),

        Production("enumerator_list", "enumerator", genTree<CSym::enumerator_list>),
        Production("enumerator_list", "enumerator_list , enumerator", genTree<CSym::enumerator_list>),

        Production("enumerator", "id = constant_expr", genTree<CSym::enumerator>),
        Production("enumerator", "id", genTree<CSym::enumerator>),

        Production("atomic_type_specifier", "_Atomic ( type_name )", genTree<CSym::atomic_type_specifier>),

        Production("type_qualifier", "const", genTree<CSym::type_qualifier>),
        Production("type_qualifier", "restrict", genTree<CSym::type_qualifier>),
        Production("type_qualifier", "volatile", genTree<CSym::type_qualifier>),
        Production("type_qualifier", "_Atomic", genTree<CSym::type_qualifier>),

        Production("function_specifier", "inline", genTree<CSym::function_specifier>),
        Production("function_specifier", "_Noreturn", genTree<CSym::function_specifier>),

        Production("alignment_specifier", "_Alignas ( type_name )", genTree<CSym::alignment_specifier>),
        Production("alignment_specifier", "_Alignas ( constant_expr )", genTree<CSym::alignment_specifier>),

        Production("declarator", "pointer direct_declarator", genTree<CSym::declarator>),
        Production("declarator", "direct_declarator", genTree<CSym::declarator>),

        Production("direct_declarator", "id", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "( declarator )", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ * ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ static type_qualifier_list assignment_expr ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ static assignment_expr ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ type_qualifier_list * ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ type_qualifier_list static assignment_expr ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ type_qualifier_list assignment_expr ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator [ type_qualifier_list ]", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator ( )", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator ( parameter_type_list )", genTree<CSym::direct_declarator>),
        Production("direct_declarator", "direct_declarator ( identifier_list )", genTree<CSym::direct_declarator>),

        Production("pointer", "*", genTree<CSym::pointer>),
        Production("pointer", "* pointer", genTree<CSym::pointer>),
        Production("pointer", "* type_qualifier_list", genTree<CSym::pointer>),
        Production("pointer", "* type_qualifier_list pointer", genTree<CSym::pointer>),

        Production("type_qualifier_list", "type_qualifier", genTree<CSym::type_qualifier_list>),
        Production("type_qualifier_list", "type_qualifier_list type_qualifier", genTree<CSym::type_qualifier_list>),

        Production("parameter_type_list", "parameter_list", genTree<CSym::parameter_type_list>),
        Production("parameter_type_list", "parameter_list , ...", genTree<CSym::parameter_type_list>),

        Production("parameter_list", "parameter_declaration", genTree<CSym::parameter_list>),
        Production("parameter_list", "parameter_list , parameter_declaration", genTree<CSym::parameter_list>),

        Production("parameter_declaration", "declaration_specifiers declarator", genTree<CSym::parameter_declaration>),
        Production("parameter_declaration", "declaration_specifiers abstract_declarator", genTree<CSym::parameter_declaration>),
        Production("parameter_declaration", "declaration_specifiers", genTree<CSym::parameter_declaration>),

        Production("identifier_list", "id", genTree<CSym::identifier_list>),
        Production("identifier_list", "identifier_list , id", genTree<CSym::identifier_list>),

        Production("type_name", "specifier_qualifier_list abstract_declarator", genTree<CSym::type_name>),
        Production("type_name", "specifier_qualifier_list", genTree<CSym::type_name>),

        Production("abstract_declarator", "pointer direct_abstract_declarator", genTree<CSym::abstract_declarator>),
        Production("abstract_declarator", "pointer", genTree<CSym::abstract_declarator>),
        Production("abstract_declarator", "direct_abstract_declarator", genTree<CSym::abstract_declarator>),

        Production("direct_abstract_declarator", "( abstract_declarator )", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[  ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[ * ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[ static type_qualifier_list assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[ static assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[ type_qualifier_list assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[ type_qualifier_list static assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[ type_qualifier_list ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "[ assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [  ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [ * ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [ static type_qualifier_list assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [ static assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [ type_qualifier_list assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [ type_qualifier_list static assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [ type_qualifier_list ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator [ assignment_expr ]", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "(  )", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "( parameter_type_list )", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator (  )", genTree<CSym::direct_abstract_declarator>),
        Production("direct_abstract_declarator", "direct_abstract_declarator ( parameter_type_list )", genTree<CSym::direct_abstract_declarator>),

        Production("initializer", "{ initializer_list }", genTree<CSym::initializer>),
        Production("initializer", "{ initializer_list , }", genTree<CSym::initializer>),
        Production("initializer", "assignment_expr", genTree<CSym::initializer>),

        Production("initializer_list", "designation initializer", genTree<CSym::initializer_list>),
        Production("initializer_list", "initializer", genTree<CSym::initializer_list>),
        Production("initializer_list", "initializer_list , designation initializer", genTree<CSym::initializer_list>),
        Production("initializer_list", "initializer_list , initializer", genTree<CSym::initializer_list>),

        Production("designation", "designator_list =", genTree<CSym::designation>),

        Production("designator_list", "designator", genTree<CSym::designator_list>),
        Production("designator_list", "designator_list designator", genTree<CSym::designator_list>),

        Production("designator", ". id", genTree<CSym::designator>),
        Production("designator", "[ constant_expr ]", genTree<CSym::designator>),

        Production("static_assert_declaration", "_Static_assert ( constant_expr , str )", genTree<CSym::static_assert_declaration>),

        Production("expr", "assignment_expr", genTree<CSym::expr>),
        Production("expr", "expr , assignment_expr", genTree<CSym::expr>),

        Production("constant_expr", "conditional_expr", genTree<CSym::constant_expr>),

        Production("assignment_expr", "conditional_expr", genTree<CSym::assignment_expr>),
        Production("assignment_expr", "unary_expr assignment_operator assignment_expr", genTree<CSym::assignment_expr>),

        Production("assignment_operator", "=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "*=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "/=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "%=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "+=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "-=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "<<=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", ">>=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "&=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "^=", genTree<CSym::assignment_operator>),
        Production("assignment_operator", "|=", genTree<CSym::assignment_operator>),

        Production("conditional_expr", "logic_or_expr", genTree<CSym::conditional_expr>),
        Production("conditional_expr", "logic_or_expr ? expr : conditional_expr", genTree<CSym::conditional_expr>),

        Production("logic_or_expr", "logic_and_expr", genTree<CSym::logical_or_expr>),
        Production("logic_or_expr", "logic_or_expr || logic_and_expr", genTree<CSym::logical_or_expr>),

        Production("logic_and_expr", "or_expr", genTree<CSym::logical_and_expr>),
        Production("logic_and_expr", "logic_and_expr && or_expr", genTree<CSym::logical_and_expr>),


        Production("or_expr", "xor_expr", genTree<CSym::inclusive_or_expr>),
        Production("or_expr", "or_expr | xor_expr", genTree<CSym::inclusive_or_expr>),

        Production("xor_expr", "and_expr", genTree<CSym::exclusive_or_expr>),
        Production("xor_expr", "xor_expr ^ and_expr", genTree<CSym::exclusive_or_expr>),

        Production("and_expr", "eq_expr", genTree<CSym::and_expr>),
        Production("and_expr", "and_expr & eq_expr", genTree<CSym::and_expr>),


        Production("eq_expr", "relational_expr", genTree<CSym::equality_expr>),
        Production("eq_expr", "eq_expr == relational_expr", genTree<CSym::equality_expr>),
        Production("eq_expr", "eq_expr != relational_expr", genTree<CSym::equality_expr>),

        Production("relational_expr", "shift_expr", genTree<CSym::relational_expr>),
        Production("relational_expr", "relational_expr < shift_expr", genTree<CSym::relational_expr>),
        Production("relational_expr", "relational_expr > shift_expr", genTree<CSym::relational_expr>),
        Production("relational_expr", "relational_expr <= shift_expr", genTree<CSym::relational_expr>),
        Production("relational_expr", "relational_expr >= shift_expr", genTree<CSym::relational_expr>),

        Production("shift_expr", "add_expr", genTree<CSym::shift_expr>),
        Production("shift_expr", "shift_expr << add_expr", genTree<CSym::shift_expr>),
        Production("shift_expr", "shift_expr >> add_expr", genTree<CSym::shift_expr>),

        Production("add_expr", "mul_expr", genTree<CSym::add_expr>),
        Production("add_expr", "add_expr + mul_expr", genTree<CSym::add_expr>),
        Production("add_expr", "add_expr - mul_expr", genTree<CSym::add_expr>),

        Production("mul_expr", "unary_expr", genTree<CSym::mul_expr>),
        Production("mul_expr", "mul_expr * unary_expr", genTree<CSym::mul_expr>),
        Production("mul_expr", "mul_expr / unary_expr", genTree<CSym::mul_expr>),
        Production("mul_expr", "mul_expr % unary_expr", genTree<CSym::mul_expr>),

        Production("cast_expr", "unary_expr", genTree<CSym::cast_expr>),
        Production("cast_expr", "( type_name ) cast_expr", genTree<CSym::cast_expr>),

        Production("unary_expr", "postfix_expr", genTree<CSym::unary_expr>),
        Production("unary_expr", "unary_operator cast_expr", genTree<CSym::unary_expr>),
        Production("unary_expr", "++ unary_expr", genTree<CSym::unary_expr>),
        Production("unary_expr", "-- unary_expr", genTree<CSym::unary_expr>),
        Production("unary_expr", "sizeof unary_expr", genTree<CSym::unary_expr>),
        Production("unary_expr", "sizeof ( type_name )", genTree<CSym::unary_expr>),
        Production("unary_expr", "_Alignof ( type_name )", genTree<CSym::unary_expr>),

        Production("unary_operator", "&", genTree<CSym::unary_operator>),
        Production("unary_operator", "*", genTree<CSym::unary_operator>),
        Production("unary_operator", "+", genTree<CSym::unary_operator>),
        Production("unary_operator", "-", genTree<CSym::unary_operator>),
        Production("unary_operator", "~", genTree<CSym::unary_operator>),
        Production("unary_operator", "!", genTree<CSym::unary_operator>),

        Production("argument_expression_list", "assignment_expr", genTree<CSym::argument_expression_list>),
        Production("argument_expression_list", "argument_expression_list , assignment_expr", genTree<CSym::argument_expression_list>),

        Production("postfix_expr", "primary_expr", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "postfix_expr ( )", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "postfix_expr . id", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "postfix_expr -> id", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "postfix_expr ++", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "postfix_expr --", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "postfix_expr [ expr ]", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "postfix_expr ( argument_expression_list )", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "( type_name ) { initializer_list }", genTree<CSym::postfix_expr>),
        Production("postfix_expr", "( type_name ) { initializer_list , }", genTree<CSym::postfix_expr>),

        Production("String", "str", genTree<CSym::String>),
        Production("String", "__func__", genTree<CSym::String>),

        Production("generic_selection", "_Generic ( assignment_expr , generic_assoc_list )", genTree<CSym::generic_selection>),

        Production("generic_assoc_list", "generic_association", genTree<CSym::generic_assoc_list>),
        Production("generic_assoc_list", "generic_assoc_list , generic_association", genTree<CSym::generic_assoc_list>),

        Production("generic_association", "type_name : assignment_expr", genTree<CSym::generic_association>),
        Production("generic_association", "default : assignment_expr", genTree<CSym::generic_association>),

        Production("constant", "integer", genTree<CSym::constant>),
        Production("constant", "Float", genTree<CSym::constant>),
        Production("constant", "enumerate_constant", genTree<CSym::constant>),

        Production("primary_expr", "( expr )", genTree<CSym::primary_expr>),
        Production("primary_expr", "id", genTree<CSym::primary_expr>),
        Production("primary_expr", "constant", genTree<CSym::primary_expr>),
        Production("primary_expr", "String", genTree<CSym::primary_expr>),
        Production("primary_expr", "generic_selection", genTree<CSym::primary_expr>),
    };
    for(int i=0;i<productions.size();i++){
        productions[i].setAttrs(*C_RuleAttributesPool::ruleAttrTable[i]);
        productions[i].setGenCodeInfo(*C_rule_code::ruleCodeTable[i]);
    }
    return productions;
}
