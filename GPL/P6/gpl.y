%{

// there is a compatibility problem with my current cygwin environment
// this appears to fix the problem
#undef __GNUC_MINOR__

#include "error.h"
#include "gpl_assert.h"
#include "symbol_table.h"
#include "symbol.h"
#include "gpl_type.h"
#include "expression.h"
#include "variable.h"
#include "constant.h"
#include <iostream>
#include <sstream>
#include <cmath> // for floor()
#include <stack>
using namespace std;

extern int yylex();
extern int yyerror(const char *);
extern int line_count;  // from gpl.l, used for statement blocks

int undeclared = 0;
Symbol_table *symbol_table = Symbol_table::instance();

%}

%union {
  int                           union_int;
  double                        union_double;
  std::string                   *union_string;  // MUST be a pointer to a string ARG!
  int                           gpl_type;
  Expression                    *union_expression;
  Variable                      *union_variable;
}

%error-verbose

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"
%token <union_int> T_FORWARD "forward" // value is line number
%token T_INITIALIZATION      "initialization" 
%token T_TERMINATION         "termination" 

%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_ON                  "on"
%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"
%token T_ZKEY                "zkey"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_ANIMATION           "animation"

%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token <union_int> T_PRINT   "print" // value is line number
%token <union_int> T_EXIT    "exit" // value is line number

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="
%token T_PLUS_PLUS           "++"
%token T_MINUS_MINUS         "--"

%token T_MULTIPLY            "*"
%token T_DIVIDE              "/"
%token T_MOD                 "%"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_FLOOR               "floor"
%token T_ABS                 "abs"
%token T_RANDOM              "random"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!="

%token T_AND                 "&&"
%token T_OR                  "||"
%token T_NOT                 "!"

%token <union_string> T_ID              "identifier"
%token <union_int> T_INT_CONSTANT       "int constant"
%token <union_double> T_DOUBLE_CONSTANT "double constant"
%token <union_string> T_STRING_CONSTANT "string constant"

%token T_ERROR               "error"

%nonassoc IF_NO_ELSE
%nonassoc T_ELSE

%left T_NEAR T_TOUCHES
%left T_OR 
%left T_AND
%left T_EQUAL T_NOT_EQUAL
%left T_LESS T_GREATER T_LESS_EQUAL T_GREATER_EQUAL 
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_MOD
%nonassoc UNARY_OPS

%type <gpl_type> simple_type
%type <gpl_type> math_operator
%type <union_expression> expression
%type <union_expression> primary_expression
%type <union_expression> optional_initializer
%type <union_variable> variable

%%


//---------------------------------------------------------------------
program:
    declaration_list block_list
    ;

//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | empty
    ;

//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC
    ;

//---------------------------------------------------------------------
variable_declaration:
    simple_type T_ID optional_initializer
    {
        std::string var_name = *$2;
        int declared_type = $1;
        Symbol *new_symbol = nullptr;

        if ($3) {
            Expression *initializer_expr = $3;
            int initializer_type = initializer_expr->get_type();

            // Ensure initializer type matches the declared variable type
            if (initializer_type != declared_type) {
                std::string declared_type_str = gpl_type_to_string(static_cast<Gpl_type>(declared_type));
                std::string initializer_type_str = gpl_type_to_string(static_cast<Gpl_type>(initializer_type));

                Error::error(Error::ASSIGNMENT_TYPE_ERROR, "Cannot assign an expression of type '" 
                             + initializer_type_str + "' to a variable of type '" + declared_type_str + "'");
                
                // Use default value for recovery based on declared type
                if (declared_type == INT) {
                    new_symbol = new Symbol(var_name, 0);
                } else if (declared_type == DOUBLE) {
                    new_symbol = new Symbol(var_name, 0.0);
                } else if (declared_type == STRING) {
                    new_symbol = new Symbol(var_name, std::string(""));
                }
            } else {
                // Initialize with evaluated value based on the matching type
                if (declared_type == INT) {
                    new_symbol = new Symbol(var_name, initializer_expr->eval_int());
                } else if (declared_type == DOUBLE) {
                    new_symbol = new Symbol(var_name, initializer_expr->eval_double());
                } else if (declared_type == STRING) {
                    new_symbol = new Symbol(var_name, initializer_expr->eval_string());
                }
            }
        } else {
            // No initializer provided; assign default value based on type
            if (declared_type == INT) {
                new_symbol = new Symbol(var_name, 0);
            } else if (declared_type == DOUBLE) {
                new_symbol = new Symbol(var_name, 0.0);
            } else if (declared_type == STRING) {
                new_symbol = new Symbol(var_name, std::string(""));
            }
        }

        // Insert the symbol into the symbol table and handle re-declaration error
        if (new_symbol && !symbol_table->insert(new_symbol)) {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, var_name);
            delete new_symbol;
        }
    }
    ;

//---------------------------------------------------------------------
simple_type:
    T_INT { $$ = INT; }
    | T_DOUBLE { $$ = DOUBLE; }
    | T_STRING { $$ = STRING; }
    ;

//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression
    {
        $$ = $2;
    }
    | empty
    {
        $$ = nullptr;
    }
    ;
//---------------------------------------------------------------------
object_declaration:
    object_type T_ID T_LPAREN parameter_list_or_empty T_RPAREN
    | object_type T_ID T_LBRACKET expression T_RBRACKET
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    | T_PIXMAP
    | T_CIRCLE
    | T_RECTANGLE
    | T_TEXTBOX
    ;

//---------------------------------------------------------------------
parameter_list_or_empty :
    parameter_list
    | empty
    ;

//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter
    ;

//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
    ;

//---------------------------------------------------------------------
block_list:
    block_list block
    | empty
    ;

//---------------------------------------------------------------------
block:
    initialization_block
    | termination_block
    | animation_block
    | on_block
    ;

//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block
    ;

//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block
    ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID T_LPAREN check_animation_parameter T_RPAREN T_LBRACE statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    object_type T_ID
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    | T_LEFTARROW
    | T_RIGHTARROW
    | T_UPARROW
    | T_DOWNARROW
    | T_LEFTMOUSE_DOWN
    | T_MIDDLEMOUSE_DOWN
    | T_RIGHTMOUSE_DOWN
    | T_LEFTMOUSE_UP
    | T_MIDDLEMOUSE_UP
    | T_RIGHTMOUSE_UP
    | T_MOUSE_MOVE
    | T_MOUSE_DRAG
    | T_F1
    | T_AKEY
    | T_SKEY
    | T_DKEY
    | T_FKEY
    | T_HKEY
    | T_JKEY
    | T_KKEY
    | T_LKEY
    | T_WKEY
    | T_ZKEY
  ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block
    | statement_block
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
statement_block_creator:
    // this goes to nothing so that you can put an action here in p7
    ;

//---------------------------------------------------------------------
end_of_statement_block:
    // this goes to nothing so that you can put an action here in p7
    ;

//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | empty
    ;

//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | print_statement T_SEMIC
    | exit_statement T_SEMIC
    | assign_statement_or_empty T_SEMIC
    ;

//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN if_block
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN statement_block_creator assign_statement_or_empty end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement_or_empty end_of_statement_block T_RPAREN statement_block
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
assign_statement_or_empty:
    assign_statement
    | empty
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    | variable T_PLUS_ASSIGN expression
    | variable T_MINUS_ASSIGN expression
    | variable T_PLUS_PLUS
    | variable T_MINUS_MINUS
    ;

//---------------------------------------------------------------------
variable:
    T_ID
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);
        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            $$ = nullptr;
        } else if (sym->is_array()) {
            // Error if trying to use an array without indexing
            Error::error(Error::VARIABLE_IS_AN_ARRAY, *$1);
            $$ = nullptr;
        } else {
            $$ = new Variable(sym);  // Regular variable handling
        }
        delete $1;
    }
    | T_ID T_LBRACKET expression T_RBRACKET
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);
        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1+"[]");
            $$ = nullptr;
        } else if (!sym->is_array()) {
            // Error if trying to index a non-array variable
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            $$ = nullptr;
        } else {
            Gpl_type index_type = $3->get_type();

            // Check if the index expression is not an integer
            if (index_type != INT) {
                // Error: non-integer type used as array index
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A " + gpl_type_to_string(index_type) + " expression");
                $$ = nullptr;
            } else {
                // Valid array element access
                $$ = new Variable(sym, $3);
            }
    }
        delete $1;
    }
    ;
//---------------------------------------------------------------------
expression:
    primary_expression
    {
        if (!$1) {
            $$ = new Expression(0);  // Default to error state
        } else {
            $$ = $1;
        }
    }
    | expression T_OR expression
    {
        bool valid_left = ($1 && $1->get_type() != STRING);
        bool valid_right = ($3 && $3->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||", gpl_type_to_string($1->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||", gpl_type_to_string($3->get_type()));
        }

        $$ = (valid_left && valid_right) ? new Expression(OR, $1, $3) : new Expression(0);
    }
    | expression T_AND expression
    {
        bool valid_left = ($1 && $1->get_type() != STRING);
        bool valid_right = ($3 && $3->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&", gpl_type_to_string($1->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&", gpl_type_to_string($3->get_type()));
        }

        $$ = (valid_left && valid_right) ? new Expression(AND, $1, $3) : new Expression(0);
    }
    | expression T_LESS_EQUAL expression
    {
        $$ = ($1 && $3) ? new Expression(LESS_EQUAL, $1, $3) : new Expression(0);
    }
    | expression T_GREATER_EQUAL expression
    {
        $$ = ($1 && $3) ? new Expression(GREATER_EQUAL, $1, $3) : new Expression(0);
    }
    | expression T_LESS expression
    {
        $$ = ($1 && $3) ? new Expression(LESS_THAN, $1, $3) : new Expression(0);
    }
    | expression T_GREATER expression
    {
        $$ = ($1 && $3) ? new Expression(GREATER_THAN, $1, $3) : new Expression(0);
    }
    | expression T_EQUAL expression
    {
        $$ = ($1 && $3) ? new Expression(EQUAL, $1, $3) : new Expression(0);
    }
    | expression T_NOT_EQUAL expression
    {
        $$ = ($1 && $3) ? new Expression(NOT_EQUAL, $1, $3) : new Expression(0);
    }
    | expression T_PLUS expression
    {
        if (!$1 || !$3) {
            $$ = new Expression(0);
        } else if ($1->get_type() == STRING || $3->get_type() == STRING) {
            std::string* combined_string = new std::string($1->eval_string() + $3->eval_string());
            $$ = new Expression(combined_string);
        } else {
            $$ = new Expression(PLUS, $1, $3);
        }
    }
    | expression T_MINUS expression
    {
        bool valid_left = ($1 && $1->get_type() != STRING);
        bool valid_right = ($3 && $3->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-", gpl_type_to_string($1->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string($3->get_type()));
        }

        $$ = (valid_left && valid_right) ? new Expression(MINUS, $1, $3) : new Expression(0);
    }
    | expression T_MULTIPLY expression
    {
        bool valid_left = ($1 && $1->get_type() != STRING);
        bool valid_right = ($3 && $3->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*", gpl_type_to_string($1->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*", gpl_type_to_string($3->get_type()));
        }

        $$ = (valid_left && valid_right) ? new Expression(MULTIPLY, $1, $3) : new Expression(0);
    }
    | expression T_DIVIDE expression
    {
        bool valid_left = ($1 && $1->get_type() != STRING);
        bool valid_right = ($3 && $3->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/", gpl_type_to_string($1->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/", gpl_type_to_string($3->get_type()));
        }

        $$ = (valid_left && valid_right) ? new Expression(DIVIDE, $1, $3) : new Expression(0);
    }
    | expression T_MOD expression
    {
        bool valid_left = ($1 && $1->get_type() == INT);
        bool valid_right = ($3 && $3->get_type() == INT);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%", gpl_type_to_string($1->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%", gpl_type_to_string($3->get_type()));
        }

        $$ = (valid_left && valid_right) ? new Expression(MOD, $1, $3) : new Expression(0);
    }
    | T_MINUS expression %prec UNARY_OPS
    {
        if (!$2) {
            $$ = new Expression(0);
        } else if ($2->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string($2->get_type()));
            $$ = new Expression(0);
        } else {
            $$ = new Expression(UNARY_MINUS, $2);
        }
    }
    | T_NOT expression %prec UNARY_OPS
    {
        if (!$2) {
            $$ = new Expression(0);
        } else if ($2->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!", gpl_type_to_string($2->get_type()));
            $$ = new Expression(0);
        } else {
            $$ = new Expression(NOT, $2);
        }
    }
    | math_operator T_LPAREN expression T_RPAREN
    {
        if (!$3) {
            $$ = new Expression(0);
        } else if ($3->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(static_cast<Operator_type>($1)), gpl_type_to_string($3->get_type()));
            $$ = new Expression(0);
        } else {
            $$ = new Expression(static_cast<Operator_type>($1), $3);
        }
    }
    ;

//---------------------------------------------------------------------
primary_expression:
    T_LPAREN expression T_RPAREN
    {
        $$ = $2;
    }
    | variable
    {
        $$ = new Expression($1);
    }
    | T_INT_CONSTANT
    {
        $$ = new Expression($1);
    }
    | T_DOUBLE_CONSTANT
    {
        $$ = new Expression($1);
    }
    | T_STRING_CONSTANT
    {
        $$ = new Expression($1);
    }
    ;

//---------------------------------------------------------------------
math_operator:
    T_MULTIPLY { $$ = MULTIPLY; }
    | T_DIVIDE { $$ = DIVIDE; }
    | T_PLUS { $$ = PLUS; }
    | T_MINUS { $$ = MINUS; }
    | T_MOD { $$ = MOD; }
    | T_SIN { $$ = SIN; }
    | T_COS { $$ = COS; }
    | T_TAN { $$ = TAN; }
    | T_ASIN { $$ = ASIN; }
    | T_ACOS { $$ = ACOS; }
    | T_ATAN { $$ = ATAN; }
    | T_SQRT { $$ = SQRT; }
    | T_FLOOR { $$ = FLOOR; }
    | T_ABS { $$ = ABS; }
    | T_RANDOM { $$ = RANDOM; }
    ;

//---------------------------------------------------------------------
empty:
    // empty goes to nothing so that you can use empty in productions
    // when you want a production to go to nothing
    ;
