%{

// there is a compatibility problem with my current cygwin environment
// this appears to fix the problem
#undef __GNUC_MINOR__

#include "error.h"
#include "gpl_assert.h"
#include "symbol_table.h"
#include "symbol.h"
#include "expression.h"
#include "variable.h"
#include "game_object.h"
#include "animation_block.h"
#include "if_statement.h"
#include "for_statement.h"
#include "print_statement.h"
#include "exit_statement.h"
#include "assign_statement.h"
#include <iostream>
#include <sstream>
#include <cmath> // for floor()
#include <stack>
using namespace std;

extern int yylex();
extern int yyerror(const char *);
extern int line_count;  // from gpl.l, used for statement blocks

int undeclared = 0;
Symbol_table *sym_table = Symbol_table::instance();
// Global variable to make the construction of object much less complex
// Only one object can ever be under construction at one time
Game_object *cur_object_under_construction = 0;
string cur_object_under_construction_name;
std::stack<Statement_block*> statement_block_stack;


%}

%union {
  int                                   union_int;
  double                                union_double;
  std::string                           *union_string;  // MUST be a pointer to a string ARG!
  Expression                            *union_expression;
  Variable                              *union_variable;
  Symbol                                *symbol;
  Gpl_type                              gpl_type;
  int                                   simple_type;
  int                                   math_operator_type;
  Window::Keystroke                     keystroke;
  Statement_block                       *statement_block;
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

%type <simple_type> simple_type
%type <gpl_type> object_type
%type <union_expression> expression
%type <union_expression> primary_expression
%type <union_expression> optional_initializer
%type <union_variable> variable
%type <union_variable> variable_declaration
%type <math_operator_type> math_operator
%type <symbol> animation_parameter
%type <keystroke> keystroke
%type <statement_block> if_block
%type <statement_block> statement_block
%type <statement_block> statement_block_creator

%%

//---------------------------------------------------------------------
program:
    declaration_list block_list
    ;

//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration T_SEMIC
    | empty
    ;

//---------------------------------------------------------------------
declaration:
    simple_type T_ID optional_initializer
    {
        std::string var_name = *$2;
        delete $2;

        Symbol *new_symbol = nullptr;

        // Create a default symbol based on the declared type
        if ($1 == T_INT) {
            new_symbol = new Symbol(var_name, 0);
        } else if ($1 == T_DOUBLE) {
            new_symbol = new Symbol(var_name, 0.0);
        } else if ($1 == T_STRING) {
            new_symbol = new Symbol(var_name, "");
        } else if ($1 == ANIMATION_BLOCK) {
            new_symbol = new Symbol(var_name, nullptr); // Default animation_block value
        }

        // Attempt to insert the symbol into the symbol table
        if (!Symbol_table::instance()->insert(new_symbol)) {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, var_name);
            delete new_symbol;
        } else if ($3) {
            Gpl_type initializer_type = $3->get_type();

            // Handle animation_block assignments
            if (initializer_type == ANIMATION_BLOCK && $1 != ANIMATION_BLOCK) {
                if ($1 == T_INT) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                                gpl_type_to_string(initializer_type),
                                var_name,
                                "int");
                } else if ($1 == T_DOUBLE) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                                gpl_type_to_string(initializer_type),
                                var_name,
                                "double");
                } else if ($1 == T_STRING) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                                gpl_type_to_string(initializer_type),
                                var_name,
                                "string");
                }

            }
            // Handle other type mismatches
            else if ($1 == T_INT && initializer_type != INT) {
                // Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                //              gpl_type_to_string(initializer_type),
                //              var_name,
                //              "int");
            } else if ($1 == T_DOUBLE && initializer_type != DOUBLE && initializer_type != INT) {
                // Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                //              gpl_type_to_string(initializer_type),
                //              var_name,
                //              "double");
            } else if ($1 == T_STRING && initializer_type != STRING) {
                // Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                //              gpl_type_to_string(initializer_type),
                //              var_name,
                //              "string");
            } else {
                // Valid initialization: set the symbol's value
                if ($1 == T_INT) {
                    new_symbol->set_value($3->eval_int());
                } else if ($1 == T_DOUBLE) {
                    new_symbol->set_value($3->eval_double());
                } else if ($1 == T_STRING) {
                    new_symbol->set_value($3->eval_string());
                }
            }

            delete $3; // Clean up
        }
    }
    | simple_type T_ID T_LBRACKET expression T_RBRACKET
    {
        std::string array_name = *$2;
        Gpl_type expr_type = $4->get_type();

        // Check if the size expression is valid
        if (expr_type != INT) {
            Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, gpl_type_to_string(expr_type), array_name);
            delete $2;
            delete $4;
        } else {
            int array_size = $4->eval_int();
            delete $2;
            delete $4;

            if (array_size < 1) {
                Error::error(Error::INVALID_ARRAY_SIZE, array_name, std::to_string(array_size));
            } else {
                Symbol *new_symbol = ($1 == T_INT) ? new Symbol(array_name, INT_ARRAY, array_size)
                                  : ($1 == T_DOUBLE) ? new Symbol(array_name, DOUBLE_ARRAY, array_size)
                                  : new Symbol(array_name, STRING_ARRAY, array_size);

                // Insert the array symbol into the symbol table
                if (!sym_table->insert(new_symbol)) {
                    Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, array_name);
                    delete new_symbol;
                }
            }
        }
    }
    | object_declaration
    | forward_declaration
    ;

//---------------------------------------------------------------------
variable_declaration:
    simple_type T_ID optional_initializer
    ;

//---------------------------------------------------------------------
simple_type:
    T_INT { $$ = T_INT; }
    | T_DOUBLE { $$ = T_DOUBLE; }
    | T_STRING { $$ = T_STRING; }
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

object_declaration:
    object_type T_ID
    {
        // Always create the object, even if it won't be inserted into the symbol table
        Symbol *symbol = new Symbol(*$2, $1);

        // Check if the variable is already declared
        if (Symbol_table::instance()->lookup(*$2)) {
            // Emit error for previously declared variable
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);

            // Allow parameter parsing for the created object, but it won't be added to the symbol table
            cur_object_under_construction = symbol->get_game_object_value();
            cur_object_under_construction_name = symbol->get_name();
        } else {
            // Attempt to insert the symbol into the symbol table
            if (!sym_table->insert(symbol)) {
                // Fallback error handling (shouldn't reach here)
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
                delete symbol;
            } else {
                // Prepare for parameter parsing
                cur_object_under_construction = symbol->get_game_object_value();
                cur_object_under_construction_name = symbol->get_name();
            }
        }
    }
    T_LPAREN parameter_list_or_empty T_RPAREN
    {
        // Reset the global construction variables after parameter parsing
        cur_object_under_construction = nullptr;
        delete $2; // Free memory allocated for T_ID
    }
    | object_type T_ID T_LBRACKET expression T_RBRACKET
    {
        // Check if the variable is already declared
        if (Symbol_table::instance()->lookup(*$2)) {
            // Emit error for previously declared variable
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);

            delete $4;

            // Skip further processing
            cur_object_under_construction = nullptr;
        } else {
            // Check the type of the size expression
            Gpl_type expr_type = $4->get_type();

            if (expr_type != INT) {
                // Report an error for non-integer array size
                Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER,
                             gpl_type_to_string(expr_type),
                             *$2);

                // Free memory for T_ID and the expression
                delete $2;
                delete $4;

                // Skip further processing
                cur_object_under_construction = nullptr;
            } else {
                // Evaluate the size expression
                int size = $4->eval_int();
                delete $4; // Free memory allocated for the expression

                if (size <= 0) {
                    // Report an error for invalid array size
                    Error::error(Error::INVALID_ARRAY_SIZE, *$2, std::to_string(size));
                } else {
                    // Map object type to array type
                    Gpl_type array_type;
                    if ($1 == CIRCLE)
                        array_type = CIRCLE_ARRAY;
                    else if ($1 == RECTANGLE)
                        array_type = RECTANGLE_ARRAY;
                    else if ($1 == TRIANGLE)
                        array_type = TRIANGLE_ARRAY;
                    else if ($1 == TEXTBOX)
                        array_type = TEXTBOX_ARRAY;
                    else if ($1 == PIXMAP)
                        array_type = PIXMAP_ARRAY;
                    else {
                        Error::error(Error::ASSIGNMENT_TYPE_ERROR, *$2);
                    }

                    // Create the array symbol
                    Symbol *symbol = new Symbol(*$2, array_type, size);

                    if (!sym_table->insert(symbol)) {
                        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
                        delete symbol;
                    }
                }
                delete $2; // Free memory allocated for T_ID
            }
        }
    }
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE { $$ = TRIANGLE; }
    | T_PIXMAP { $$ = PIXMAP; }
    | T_CIRCLE { $$ = CIRCLE; }
    | T_RECTANGLE { $$ = RECTANGLE; }
    | T_TEXTBOX { $$ = TEXTBOX; }
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
    {
        std::string parameter = *$1;
        delete $1; // Free memory allocated for T_ID

        Expression *value_expression = $3;
        Gpl_type value_expression_type = value_expression->get_type();

        // Ensure `cur_object_under_construction` is valid
        if (!cur_object_under_construction) {
            delete value_expression;
            return 0;
        }

        // Get the type of the parameter in the game object
        Status status;
        Gpl_type parameter_type;
        status = cur_object_under_construction->get_member_variable_type(parameter, parameter_type);

        if (status == OK)
        {
            // Handle assignment of an ANIMATION_BLOCK
            if (parameter_type == ANIMATION_BLOCK)
            {
                if (value_expression_type != ANIMATION_BLOCK) {
                    // The provided value is not an animation block
                    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                                 parameter,
                                 gpl_type_to_string(value_expression_type));
                } else {
                    // Verify type compatibility between object and animation block
                    Animation_block *block = value_expression->eval_animation_block();
                    Symbol *parameter_symbol = block->get_parameter_symbol();
                    if (parameter_symbol->get_type() != cur_object_under_construction->get_type()) {
                        // Type mismatch
                        Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT,
                                     cur_object_under_construction_name,
                                     block->name());
                    } else {
                        // Valid assignment
                        cur_object_under_construction->set_member_variable(parameter, block);
                    }
                }
            }
            // Handle implicit conversion for DOUBLE <- INT
            else if (parameter_type == DOUBLE && value_expression_type == INT)
            {
                double converted_value = value_expression->eval_int() * 1.0;
                cur_object_under_construction->set_member_variable(parameter, converted_value);
            }
            // Handle implicit conversion for STRING <- INT or STRING <- DOUBLE
            else if (parameter_type == STRING &&
                     (value_expression_type == INT || value_expression_type == DOUBLE))
            {
                std::string converted_value = value_expression->eval_string();
                cur_object_under_construction->set_member_variable(parameter, converted_value);
            }
            // Handle mismatched types
            else if (parameter_type != value_expression_type)
            {
                Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE,
                             cur_object_under_construction_name,
                             parameter,
                             gpl_type_to_string(parameter_type));
            }
            else
            {
                // Set the parameter value based on its type
                if (parameter_type == INT)
                    cur_object_under_construction->set_member_variable(parameter, value_expression->eval_int());
                else if (parameter_type == DOUBLE)
                    cur_object_under_construction->set_member_variable(parameter, value_expression->eval_double());
                else if (parameter_type == STRING)
                    cur_object_under_construction->set_member_variable(parameter, value_expression->eval_string());
            }
        }
        else
        {
            // Handle unknown parameters
            std::string base_type_name = gpl_type_to_string(cur_object_under_construction->get_type());
            Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER,
                         base_type_name,
                         parameter);
        }

        delete value_expression; // Free memory allocated for the expression
    }
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
    {
        // Create a new Animation_block
        Symbol *animation_symbol = new Symbol(*$3, ANIMATION_BLOCK);
        if (!sym_table->insert(animation_symbol))
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$3);
        }

        // Retrieve the Animation_block and initialize it with the parameter
        Animation_block *animation_block = animation_symbol->get_animation_block_value();
        assert(animation_block != nullptr); // Ensure animation_block is valid
        animation_block->initialize($5, *$3); // Initialize with parameter symbol and name

        delete $3; // Clean up
    }
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
  {
      // COMPLETE ME
  }
  ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID T_LPAREN check_animation_parameter T_RPAREN T_LBRACE statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    {
        // Create a new Game_object parameter
        Symbol *parameter_symbol = new Symbol(*$2, $1);
        if (!sym_table->insert(parameter_symbol))
        {
            Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2);
        }
        else
        {
            // Mark the object as a parameter (never animate or draw)
            parameter_symbol->get_game_object_value()->never_animate();
            parameter_symbol->get_game_object_value()->never_draw();
        }

        $$ = parameter_symbol; // Pass the Symbol pointer up the tree
        delete $2; // Clean up
    }
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    object_type T_ID
    ;

//---------------------------------------------------------------------
on_block:
  T_ON keystroke statement_block
  {
      // COMPLETE ME
  }
  ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    {
      $$ = Window::SPACE;
    }
    | T_LEFTARROW
    {
      $$ = Window::LEFTARROW;
    }
    | T_RIGHTARROW
    {
      $$ = Window::RIGHTARROW;
    }
    | T_UPARROW
    {
      $$ = Window::UPARROW;
    }
    | T_DOWNARROW
    {
      $$ = Window::DOWNARROW;
    }
    | T_LEFTMOUSE_DOWN
    {
      $$ = Window::LEFTMOUSE_DOWN;
    }
    | T_MIDDLEMOUSE_DOWN
    {
      $$ = Window::MIDDLEMOUSE_DOWN;
    }
    | T_RIGHTMOUSE_DOWN
    {
      $$ = Window::RIGHTMOUSE_DOWN;
    }
    | T_LEFTMOUSE_UP
    {
      $$ = Window::LEFTMOUSE_UP;
    }
    | T_MIDDLEMOUSE_UP
    {
      $$ = Window::MIDDLEMOUSE_UP;
    }
    | T_RIGHTMOUSE_UP
    {
      $$ = Window::RIGHTMOUSE_UP;
    }
    | T_MOUSE_MOVE
    {
      $$ = Window::MOUSE_MOVE;
    }
    | T_MOUSE_DRAG
    {
      $$ = Window::MOUSE_DRAG;
    }
    | T_F1
    {
      $$ = Window::F1;
    }
    | T_AKEY
    {
      $$ = Window::AKEY;
    }
    | T_SKEY
    {
      $$ = Window::SKEY;
    }
    | T_DKEY
    {
      $$ = Window::DKEY;
    }
    | T_FKEY
    {
      $$ = Window::FKEY;
    }
    | T_HKEY
    {
      $$ = Window::HKEY;
    }
    | T_JKEY
    {
      $$ = Window::JKEY;
    }
    | T_KKEY
    {
      $$ = Window::KKEY;
    }
    | T_LKEY
    {
      $$ = Window::LKEY;
    }
    | T_WKEY
    {
      $$ = Window::WKEY;
    }
    | T_ZKEY
    {
      $$ = Window::ZKEY;
    }
    ;

//---------------------------------------------------------------------
if_block:
  statement_block_creator statement end_of_statement_block
  {
      $$ = $1;
  }
  | statement_block
  {
      $$ = $1;
  }
  ;

//---------------------------------------------------------------------
statement_block:
  T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
  {
      $$ = $2;
  }
  ;

//---------------------------------------------------------------------
statement_block_creator:
  {
      Statement_block *new_block = new Statement_block();
      statement_block_stack.push(new_block);
      $$ = new_block;
  }
  ;

//---------------------------------------------------------------------
end_of_statement_block:
  {
      assert(!statement_block_stack.empty());
      statement_block_stack.pop();
  }
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
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC
    ;

//---------------------------------------------------------------------
if_statement:
  T_IF T_LPAREN expression T_RPAREN if_block %prec IF_NO_ELSE
  {
      Expression *expr = $3;
      if (expr->get_type() != INT)
      {
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
        expr = new Expression(0);
      }
      statement_block_stack.top()->insert(new If_statement(expr,$5));
  }
  | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block
  {
      // COMPLETE ME
  }
  ;

//---------------------------------------------------------------------
for_statement:
  T_FOR T_LPAREN
    statement_block_creator assign_statement_or_empty end_of_statement_block
    T_SEMIC expression T_SEMIC
    statement_block_creator assign_statement_or_empty end_of_statement_block
    T_RPAREN statement_block
  {
      // COMPLETE ME
  }
  ;

//---------------------------------------------------------------------
print_statement:
  T_PRINT T_LPAREN expression T_RPAREN
  {
      Expression *expr = $3;
      if (expr->get_type() != INT
        && expr->get_type() != DOUBLE
        && expr->get_type() != STRING
       )
      {
        Error::error(Error::INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION);
        // for error handling
        expr = new Expression(0);
      }
      statement_block_stack.top()->insert(new Print_statement(expr, $1)); // $1 has line_number
  }
  ;

//---------------------------------------------------------------------
exit_statement:
  T_EXIT T_LPAREN expression T_RPAREN
  {
      // COMPLETE ME
  }
  ;

//---------------------------------------------------------------------
assign_statement_or_empty:
    assign_statement
    | empty
    ;

//---------------------------------------------------------------------
assign_statement:
  variable T_ASSIGN expression
  {
      Variable *lhs = $1;
      Expression *rhs = $3;
      Gpl_type lhs_type = lhs->get_type();
      Gpl_type rhs_type = rhs->get_type();

      // game_object is illegal on lhs of assignment
      if (lhs_type & GAME_OBJECT)
      {
        Error::error(Error::INVALID_LHS_OF_ASSIGNMENT,
              lhs->get_name(),
              gpl_type_to_string(lhs_type)
              );
      }

      // if variable is an INT, expression must be INT
      // if variable is a DOUBLE, expression must be INT or DOUBLE
      // if variable is a STRING, expression must be STRING,INT, or DOUBLE
      // if variable is a ANIMATION_BLOCK, expression ANIMATION_BLOCK
      else if ((lhs_type == INT && rhs_type != INT)
          ||(lhs_type==DOUBLE&&(rhs_type != INT && rhs_type!=DOUBLE))
          ||(lhs_type == STRING && rhs_type == ANIMATION_BLOCK)
          ||(lhs_type==ANIMATION_BLOCK&& rhs_type != ANIMATION_BLOCK)
          )
      {
        Error::error(Error::ASSIGNMENT_TYPE_ERROR,
                     gpl_type_to_string(lhs_type),
                     gpl_type_to_string(rhs_type)
                    );
      }
        else if (lhs_type==ANIMATION_BLOCK)
        {
          // since lhs is an ANIMATION_BLOCK, it SHOULD take one of these forms
          // circle.animation_block =
          // circles[index].animation_block =

          // this is ok
          //   my_rect.animation_block = bounce;
          // this is NOT ok
          //   bounce = move;
          // check to make sure it is not this illegal form
          if (lhs->is_non_member_animation_block())
          {
            Error::error(Error::CANNOT_ASSIGN_TO_NON_MEMBER_ANIMATION_BLOCK,
                         lhs->get_name()
                        );
          }
          else
          {
  
            // get the type of the Game_object on the LHS
            Gpl_type lhs_base_object_type = lhs->get_base_game_object_type();
  
            Gpl_type rhs_param_type = rhs->eval_animation_block()->get_parameter_symbol()->get_type();
  
            // Animation_block *block = rhs->eval_animation_block();
            // Symbol *sym = block->get_parameter_symbol();
  
            if (lhs_base_object_type != rhs_param_type)
            {
              Error::error(Error::ANIMATION_BLOCK_ASSIGNMENT_PARAMETER_TYPE_ERROR,
                           gpl_type_to_string(lhs_base_object_type),
                           gpl_type_to_string(rhs_param_type)
                          );
  
            }
            else statement_block_stack.top()->insert(new Assign_statement(ASSIGN, lhs, rhs));
            }
          }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(ASSIGN, lhs, rhs));
      }
  }
  | variable T_PLUS_ASSIGN expression
  {
      Gpl_type lhs_type = $1->get_type();
      Gpl_type rhs_type = $3->get_type();

      // game_object & statement_block are illegal on lhs of +=
      if ((lhs_type & GAME_OBJECT) || (lhs_type == ANIMATION_BLOCK))
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT,
                  $1->get_name(),
                  gpl_type_to_string(lhs_type)
              );
      }

      // if variable is an INT, expression must be INT
      // if variable is a DOUBLE, expression must be INT or DOUBLE
      // if variable is a STRING, expression must be STRING,INT, or DOUBLE
      else if ((lhs_type == INT && rhs_type != INT)
          ||(lhs_type==DOUBLE&&(rhs_type != INT && rhs_type!=DOUBLE))
          ||(lhs_type == STRING && rhs_type == ANIMATION_BLOCK)
          )
      {
        Error::error(Error::PLUS_ASSIGNMENT_TYPE_ERROR,
              gpl_type_to_string(lhs_type),
              gpl_type_to_string(rhs_type)
              );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(PLUS_ASSIGN, $1, $3));
      }
  }
  | variable T_MINUS_ASSIGN expression
  {
      Gpl_type lhs_type = $1->get_type();
      Gpl_type rhs_type = $3->get_type();

      // game_object & statement_block & string are illegal on lhs of +=
      if (lhs_type != INT && lhs_type != DOUBLE)
      {
        Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT,
                  $1->get_name(),
                  gpl_type_to_string(lhs_type)
                 );
      }

      // if variable is an INT, expression must be INT
      // if variable is a DOUBLE, expression must be INT or DOUBLE
      else if ((lhs_type == INT && rhs_type != INT)
          ||(lhs_type==DOUBLE&&(rhs_type != INT && rhs_type!=DOUBLE))
          )
      {
        Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR,
              gpl_type_to_string(lhs_type),
              gpl_type_to_string(rhs_type)
              );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(MINUS_ASSIGN, $1, $3));
      }
  }
  | variable T_PLUS_PLUS
  {
      Gpl_type lhs_type = $1->get_type();
      if (lhs_type != INT)
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_PLUS,
                  $1->get_name(),
                  gpl_type_to_string(lhs_type)
                 );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(PLUS_PLUS, $1));
      }
  }
  | variable T_MINUS_MINUS
  {
      Gpl_type lhs_type = $1->get_type();
      if (lhs_type != INT)
      {
        Error::error(Error::INVALID_LHS_OF_MINUS_MINUS,
                  $1->get_name(),
                  gpl_type_to_string(lhs_type)
                 );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(MINUS_MINUS, $1));
      }
  }
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
            Error::error(Error::VARIABLE_IS_AN_ARRAY, *$1);
            $$ = nullptr;
        } else {
            $$ = new Variable(sym);
        }

        delete $1;
    }
    | T_ID T_LBRACKET expression T_RBRACKET
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);

        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1 + "[]");
            $$ = nullptr;
        } else if (!sym->is_array()) {
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            $$ = nullptr;
        } else {
            Gpl_type index_type = $3->get_type();

            if (index_type != INT) {
                Error::error(
                    Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                    *$1,
                    "A " + gpl_type_to_string(index_type) + " expression"
                );
                $$ = nullptr;
            } else {
                $$ = new Variable(sym, $3);
            }
        }

        delete $1;
    }
    | T_ID T_PERIOD T_ID
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);

        if (!sym) {
            // Variable not found
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            $$ = nullptr;
        } else if (!sym->is_game_object()) {
            // Variable is not a game object
            Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
            $$ = nullptr;
        } else {
            // Check if the member variable exists
            Game_object *game_object = sym->get_game_object_value();
            assert(game_object != nullptr);

            Gpl_type member_type;
            if (game_object->get_member_variable_type(*$3, member_type) != OK) {
                // Member variable does not exist
                Error::error(Error::UNDECLARED_MEMBER, *$1, *$3);
                $$ = nullptr;
            } else {
                // Member exists, create the variable
                $$ = new Variable(sym, *$3);
            }
        }

        delete $1;
        delete $3;
    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);

        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1 + "[]");
            $$ = nullptr;
        } else {
            if (!sym->is_array()) {
                Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
                $$ = nullptr;
            } else {
                int index = $3->eval_int();
                if (!sym->is_game_object()) {
                    Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
                    $$ = nullptr;
                } else {
                    $$ = new Variable(sym, $3, *$6); // Member variable like `rects[i].x`
                }
            }
        }

        delete $1;
        delete $6;
    }   
    ;

//---------------------------------------------------------------------
expression:
    primary_expression
    { 
        $$ = ($1 == nullptr) ? new Expression(0) : $1;
    }
    | expression T_OR expression
    {
        bool lhs_valid = ($1 != nullptr && $1->get_type() != STRING);
        bool rhs_valid = ($3 != nullptr && $3->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||", gpl_type_to_string($1->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||", gpl_type_to_string($3->get_type()));
        }

        $$ = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(OR, $1, $3);
    }
    | expression T_AND expression
    {
        bool lhs_valid = ($1 != nullptr && $1->get_type() != STRING);
        bool rhs_valid = ($3 != nullptr && $3->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&", gpl_type_to_string($1->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&", gpl_type_to_string($3->get_type()));
        }

        $$ = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(AND, $1, $3);
    }
    | expression T_LESS_EQUAL expression
    {
        $$ = ($1 == nullptr || $3 == nullptr) 
            ? new Expression(0) 
            : new Expression(LESS_EQUAL, $1, $3);
    }
    | expression T_GREATER_EQUAL expression
    {
        $$ = ($1 == nullptr || $3 == nullptr) 
            ? new Expression(0) 
            : new Expression(GREATER_EQUAL, $1, $3);
    }
    | expression T_LESS expression
    {
        $$ = ($1 == nullptr || $3 == nullptr) 
            ? new Expression(0) 
            : new Expression(LESS_THAN, $1, $3);
    }
    | expression T_GREATER expression
    {
        $$ = ($1 == nullptr || $3 == nullptr) 
            ? new Expression(0) 
            : new Expression(GREATER_THAN, $1, $3);
    }
    | expression T_EQUAL expression
    {
        $$ = ($1 == nullptr || $3 == nullptr) 
            ? new Expression(0) 
            : new Expression(EQUAL, $1, $3);
    }
    | expression T_NOT_EQUAL expression
    {
        $$ = ($1 == nullptr || $3 == nullptr) 
            ? new Expression(0) 
            : new Expression(NOT_EQUAL, $1, $3);
    }
    | expression T_PLUS expression
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($1->get_type() == STRING || $3->get_type() == STRING) {
            auto result = new string($1->eval_string() + $3->eval_string());
            $$ = new Expression(result);
        } else {
            $$ = new Expression(PLUS, $1, $3);
        }
    }
    | expression T_MINUS expression
    {
        bool lhs_valid = ($1 != nullptr && $1->get_type() != STRING);
        bool rhs_valid = ($3 != nullptr && $3->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-", gpl_type_to_string($1->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string($3->get_type()));
        }

        $$ = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(MINUS, $1, $3);
    }
    | expression T_MULTIPLY expression
    {
        bool lhs_valid = ($1 != nullptr && $1->get_type() != STRING);
        bool rhs_valid = ($3 != nullptr && $3->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*", gpl_type_to_string($1->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*", gpl_type_to_string($3->get_type()));
        }

        $$ = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(MULTIPLY, $1, $3);
    }
    | expression T_DIVIDE expression
    {
        bool lhs_valid = ($1 != nullptr && $1->get_type() != STRING);
        bool rhs_valid = ($3 != nullptr && $3->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/", gpl_type_to_string($1->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/", gpl_type_to_string($3->get_type()));
        }

        $$ = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(DIVIDE, $1, $3);
    }
    | expression T_MOD expression
    {
        bool lhs_valid = ($1 != nullptr && $1->get_type() == INT);
        bool rhs_valid = ($3 != nullptr && $3->get_type() == INT);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%", gpl_type_to_string($1->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%", gpl_type_to_string($3->get_type()));
        }

        $$ = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(MOD, $1, $3);
    }
    | T_MINUS expression %prec UNARY_OPS
    {
        if ($2 == nullptr) {
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
        if ($2 == nullptr) {
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
        if ($3 == nullptr) {
            $$ = new Expression(0);
        } else if ($3->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                         operator_to_string(static_cast<Operator_type>($1)), 
                         gpl_type_to_string($3->get_type()));
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
        $$ = ($2 == nullptr) ? new Expression(0) : $2;
    }
    | variable 
    { 
        $$ = ($1 == nullptr) ? new Expression(0) : new Expression($1);
    }
    | T_INT_CONSTANT 
    { 
        $$ = new Expression($1); 
    }
    | T_TRUE 
    { 
        $$ = new Expression(1); 
    }
    | T_FALSE 
    { 
        $$ = new Expression(0); 
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
    T_SIN { $$ = SIN; }
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
