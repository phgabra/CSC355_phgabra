%{

// there is a compatibility problem with my current cygwin environment
// this appears to fix the problem
#undef __GNUC_MINOR__
#include <algorithm>
#include "error.h"
#include "gpl_assert.h"
#include "symbol_table.h"
#include "symbol.h"
#include "expression.h"
#include "variable.h"
#include "event_manager.h"
#include "statement_block.h"
#include "animation_block.h"
#include "game_object.h"
#include "triangle.h"
#include "pixmap.h"
#include "circle.h"
#include "rectangle.h"
#include "textbox.h"
#include "window.h"
#include <iostream>
#include <sstream>
#include <cmath> // for floor()
#include <stack>
#include "if_statement.h"
#include "for_statement.h"
#include "print_statement.h"
#include "exit_statement.h"
#include "assign_statement.h"

using namespace std;

extern int yylex();
extern int yyerror(const char *);
extern int line_count;  // from gpl.l, used for statement blocks

// Tracks the count of undeclared variables
int undeclared = 0;

// Current game object under construction
Game_object* cur_object_under_construction = nullptr;
std::string cur_object_under_construction_name;
std::string cur_object_under_construction_type;

// Event manager instance
Event_manager* event_manager = Event_manager::instance();

// Statement block stack for managing nested statements
std::stack<Statement_block*> statement_block_stack;

// Animation blocks storage
std::vector<Animation_block*> animation_blocks;

// Singleton instance of the sym table
Symbol_table* sym_table = Symbol_table::instance();
%}

%union {
    int              union_int;
    double           union_double;
    std::string      *union_string;  
    Expression       *union_expression;
    Variable         *union_variable;
    Gpl_type         gpl_type;
    int              math_operator_type;
    Symbol           *union_symbol; 
    Statement_block  *union_statement_block;
}

%error-verbose
%type <gpl_type> simple_type
%type <gpl_type> object_type
%type <union_expression> expression
%type <union_expression> primary_expression
%type <union_expression> optional_initializer
%type <union_variable> variable
%type <math_operator_type> math_operator
%type <union_symbol> animation_parameter
%type <union_symbol> forward_declaration
%type <union_statement_block> if_block
%type <union_statement_block> statement_block
%type <union_statement_block> statement_block_creator
%type <union_int> keystroke
%type <union_statement_block> assign_statement_or_empty
%type <union_statement_block> for_statement
%type <union_statement_block> assign_statement
%type <union_statement_block> animation_block
%type <union_symbol> check_animation_parameter

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"
%token <union_int> T_FORWARD "forward" 
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
%token <union_int> T_PRINT   "print"
%token <union_int> T_EXIT    "exit" 

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

%%

//---------------------------------------------------------------------
program:
    declaration_list block_list
    {
        #if defined P7B
        if (!Error::num_errors())
        {
            for (auto& block : animation_blocks)
            {
                if (!block->complete())
                {
                    Error::error(Error::NO_BODY_PROVIDED_FOR_FORWARD, block->name());
                }
            }
        }
        #endif
    }
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

    string var_name = *$2;

    Symbol *new_symbol = nullptr;
    // Create default sym
    if ($1 == INT) {
        new_symbol = new Symbol(var_name, 0);
    } else if ($1 == DOUBLE) {
        new_symbol = new Symbol(var_name, 0.0);
    } else {
        new_symbol = new Symbol(var_name, "");
    }

    //Insert sym and check for errors
    if (!Symbol_table::instance()->insert(new_symbol)) {
        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, var_name);
    } else {

        // Handle optional initializer if present
        if ($3) {
            Gpl_type initializer_type = $3->get_type();
            if(initializer_type == NO_TYPE)
            {
                if ($1 == INT) {
                    new_symbol = new Symbol(var_name, 0);
                } else if ($1 == DOUBLE) {
                    new_symbol = new Symbol(var_name, 0.0);
                } else {
                    new_symbol = new Symbol(var_name, "");
                }
            } else {
                // Error if initializer is an array
                if (initializer_type == INT_ARRAY || initializer_type == DOUBLE_ARRAY || initializer_type == STRING_ARRAY) {
                    Error::error(Error::VARIABLE_IS_AN_ARRAY, $3->get_variable()->get_name());
                }
                // Error if types don't match
                else if ($1 == INT && initializer_type != INT) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string(initializer_type), var_name, "int");
                }
                // Error if types don't match
                else if ($1 == DOUBLE && initializer_type != DOUBLE && initializer_type != INT) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string(initializer_type), var_name, "double");
                }
                //Expression wrong type for string
                else if ($1 == STRING && initializer_type != STRING && initializer_type != INT && initializer_type != DOUBLE) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string(initializer_type), var_name, "string");
                }
                else {
                    // Now just set the value
                    if ($1 == INT) {
                        new_symbol->set_value($3->eval_int());
                    } else if ($1 == DOUBLE) {
                            new_symbol->set_value($3->eval_double());
                        } else { 
                            new_symbol->set_value($3->eval_string());
                        }
                }
            }
        }

    }
}
| simple_type T_ID T_LBRACKET expression T_RBRACKET
{
    Symbol_table *sym_table = Symbol_table::instance();
    string array_name = *$2;
    Expression* size_expr = $4;
    // Does expression exist?
    if (size_expr == nullptr) {
        Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, "null", array_name);
    }
    //is size an int?
    else if (size_expr->get_type() != INT) {
        Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, 
                    gpl_type_to_string(size_expr->get_type()), 
                    array_name);
    }
    else {
        int array_size = size_expr->eval_int();
        if (array_size < 1) {
            Error::error(Error::INVALID_ARRAY_SIZE, array_name, std::to_string(array_size));
        }
        else {
            Symbol *new_symbol = ($1 == INT) ? new Symbol(array_name, INT_ARRAY, array_size)
                              : ($1 == DOUBLE) ? new Symbol(array_name, DOUBLE_ARRAY, array_size)
                              : new Symbol(array_name, STRING_ARRAY, array_size);

            if (!sym_table->insert(new_symbol)) {
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, array_name);
            }
        }
    }

}
    | object_declaration
    | forward_declaration
    ;

//---------------------------------------------------------------------
simple_type:
    T_INT {
        $$ = static_cast<Gpl_type>(INT);
    }
    | T_DOUBLE {
        $$ = static_cast<Gpl_type>(DOUBLE);
    }
    | T_STRING {
        $$ = static_cast<Gpl_type>(STRING);
    }
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

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID
    {
        // Always create the object, even if it won't be inserted into the sym table
        Symbol *sym = new Symbol(*$2, $1);

        // Check if the variable is already declared
        if (Symbol_table::instance()->lookup(*$2)) {
            // Emit error for previously declared variable
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);

            // Allow parameter parsing for the created object, but it won't be added to the sym table
            cur_object_under_construction = sym->get_game_object_value();
            cur_object_under_construction_name = sym->get_name();
        } else {
            // Attempt to insert the sym into the sym table
            if (!sym_table->insert(sym)) {
                // Fallback error handling (shouldn't reach here)
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
                delete sym;
            } else {
                // Prepare for parameter parsing
                cur_object_under_construction = sym->get_game_object_value();
                cur_object_under_construction_name = sym->get_name();
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

                    // Create the array sym
                    Symbol *sym = new Symbol(*$2, array_type, size);

                    if (!sym_table->insert(sym)) {
                        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$2);
                        delete sym;
                    }
                }
                delete $2; // Free memory allocated for T_ID
            }
        }
    }
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE   { $$ = TRIANGLE; }
    | T_PIXMAP    { $$ = PIXMAP; }
    | T_CIRCLE    { $$ = CIRCLE; }
    | T_RECTANGLE { $$ = RECTANGLE; }
    | T_TEXTBOX   { $$ = TEXTBOX; }
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
        // Ensure the animation parameter is valid before proceeding
        if ($5 != nullptr)
        {
            Animation_block *block = new Animation_block(*$3, $5);
            Symbol *sym = new Symbol(*$3, block);

            // Attempt to insert the sym into the sym table
            if (!sym_table->insert(sym))
            {
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *$3);
                $$ = nullptr;
            }
            else
            {
                animation_blocks.push_back(block);  // Track animation blocks needing bodies
                $$ = sym;
            }
        }
        else
        {
            $$ = nullptr;
        }
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
    {
        event_manager->register_handler(Window::INITIALIZE, $2);
    }
    ;

//---------------------------------------------------------------------
termination_block:
    T_TERMINATION statement_block
    {
        event_manager->register_handler(Window::TERMINATE, $2);
    }
    ;

//---------------------------------------------------------------------
animation_block:
  T_ANIMATION T_ID T_LPAREN check_animation_parameter 
  {
      bool error_recovery = false;
      Symbol *sym = Symbol_table::instance()->lookup(*$2);
      Animation_block *animation_block = NULL;

      // Handle the case where the sym is missing or not an animation block
      if (!sym || !sym->is_animation_block()) 
      {
          Error::error(Error::NO_FORWARD_FOR_ANIMATION_BLOCK, *$2);
          animation_block = new Animation_block();
          animation_block->initialize(NULL, "error_recovery");
          error_recovery = true;
      } 
      else 
      {
          // Retrieve the existing animation block
          animation_block = sym->get_animation_block_value();

          if (animation_block->complete()) 
          {
              Error::error(Error::PREVIOUSLY_DEFINED_ANIMATION_BLOCK, *$2);
          }

          // Remove this block from the list of blocks needing bodies
          auto it = std::find(animation_blocks.begin(), animation_blocks.end(), animation_block);
          if (it != animation_blocks.end()) 
          {
              animation_blocks.erase(it);
          }
      }

      // Check if the parameter sym matches the forward declaration
      if (!error_recovery && $4 != animation_block->get_parameter_symbol()) 
      {
          Error::error(Error::ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD);
      }

      // Mark the animation block as complete and push it onto the stack
      animation_block->mark_complete();
      statement_block_stack.push(animation_block);

      $<union_statement_block>$ = animation_block;
  }
  T_RPAREN T_LBRACE statement_list T_RBRACE end_of_statement_block
  {
      $$ = $<union_statement_block>5;
  }
  ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    {
        // Create a new sym for the parameter
        Symbol *param_symbol = new Symbol(*$2, $1);
        
        // Get the game object and mark it as never draw/never animate
        Game_object* param_object = param_symbol->get_game_object_value();
        if (param_object) {
            param_object->never_draw();
            param_object->never_animate();
        }
        
        // Add to sym table
        if (!Symbol_table::instance()->insert(param_symbol)) {
            Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2);
            $$ = nullptr;
        } else {
            $$ = param_symbol;
        }
    }
    ;

//---------------------------------------------------------------------
check_animation_parameter:
  object_type T_ID
  {
      Gpl_type obj_type = $1;
      string id = *$2;
      Game_object *parameter = NULL;

      // Lookup the symbol in the symbol table
      Symbol *sym = sym_table->lookup(id);

      // Check if the symbol exists and is a valid game object
      if (sym && sym->is_game_object())
      {
          parameter = sym->get_game_object_value();
      }

      // Validate the parameter type
      if (!sym || !parameter || parameter->get_type() != obj_type)
      {
          $$ = NULL;  // Set result to NULL if validation fails
      }
      else
      {
          $$ = sym;  // Set result to the valid symbol
      }
  }
  ;

//---------------------------------------------------------------------
on_block:
  T_ON keystroke statement_block
  {
      event_manager->register_handler(static_cast<Window::Keystroke>($2), $3);
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

        // Validate the expression type
        if (expr->get_type() != INT)
        {
            Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
            expr = new Expression(0); // Default to a false condition
        }

        // Insert the "if" statement without an "else" block
        statement_block_stack.top()->insert(new If_statement(expr, $5));
    }
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block
    {
        Expression *expr = $3;

        // Validate the expression type
        if (expr->get_type() != INT)
        {
            Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
            expr = new Expression(0); // Default to a false condition
        }

        // Insert the "if" statement with an "else" block
        statement_block_stack.top()->insert(new If_statement(expr, $5, $7));
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
      Expression *expr = $7; 
      if (expr->get_type() != INT)
      {
          Error::error(Error::INVALID_TYPE_FOR_FOR_STMT_EXPRESSION);
          expr = new Expression(0);
      }
      statement_block_stack.top()->insert(new For_statement($3, expr, $9, $13));
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
        expr = new Expression(0);
      }
      statement_block_stack.top()->insert(new Print_statement(expr, $1));
  }
  ;

//---------------------------------------------------------------------
exit_statement:
  T_EXIT T_LPAREN expression T_RPAREN
  {
      Expression *expr = $3;
      if (expr->get_type() != INT)
      {
          Error::error(Error::EXIT_STATUS_MUST_BE_AN_INTEGER, gpl_type_to_string(expr->get_type()));
          expr = new Expression(0);
      }
      statement_block_stack.top()->insert(new Exit_statement(expr, $1)); // $1 has line number
  }
  ;

//---------------------------------------------------------------------
assign_statement_or_empty:
    assign_statement
    {
        $$ = $1;
    }
    | empty
    {
        $$ = nullptr;
    }
    ;

//---------------------------------------------------------------------
assign_statement:
  variable T_ASSIGN expression
  {
      Variable *lhs = $1;
      Expression *rhs = $3;
      Gpl_type lhs_type = lhs->get_type();
    if(lhs_type & GAME_OBJECT)
    {
        lhs_type = static_cast<Gpl_type>(lhs_type & ~ARRAY);
    }
      Gpl_type rhs_type = rhs->get_type();

      // game_object is illegal on lhs of assignment
      if ((lhs_type & GAME_OBJECT) && !lhs->has_field())
      {
          Error::error(Error::INVALID_LHS_OF_ASSIGNMENT,
                lhs->get_name(),
                gpl_type_to_string(lhs_type)
                );
      }

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
          if (lhs->is_non_member_animation_block())
          {
            Error::error(Error::CANNOT_ASSIGN_TO_NON_MEMBER_ANIMATION_BLOCK,
                         lhs->get_name()
                        );
          }
          else
          {
            Gpl_type lhs_base_object_type = lhs->get_base_game_object_type();
            Animation_block* rhs_block = rhs->eval_animation_block();
            Gpl_type rhs_param_type = rhs_block->get_parameter_symbol()->get_type();
  
            if ((Gpl_type)(lhs_base_object_type & ~ARRAY) != rhs_param_type)
            {
              Error::error(Error::ANIMATION_BLOCK_ASSIGNMENT_PARAMETER_TYPE_ERROR,
                           gpl_type_to_string((Gpl_type)(lhs_base_object_type & ~ARRAY)),
                           gpl_type_to_string(rhs_param_type)
                          );
            }
            else statement_block_stack.top()->insert(new Assign_statement(ASSIGN, lhs, rhs));
            }
          }
      else
      {
        statement_block_stack.top()->insert(new Assign_statement(ASSIGN, lhs, rhs));
      }
  }
  | variable T_PLUS_ASSIGN expression
  {
      Gpl_type lhs_type = $1->get_type();
      Gpl_type rhs_type = $3->get_type();

      if ((lhs_type & GAME_OBJECT) || (lhs_type == ANIMATION_BLOCK))
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT,
                  $1->get_name(),
                  gpl_type_to_string(lhs_type)
              );
      }

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

      else if ((lhs_type == INT && rhs_type != INT)
          ||(lhs_type==DOUBLE&&(rhs_type != INT && rhs_type!=DOUBLE))
          )
      {
        Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR,
              gpl_type_to_string(lhs_type),
              gpl_type_to_string(rhs_type)
              );
      }
      else 
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
      else 
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
      else 
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
        if (!sym)
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            $$ = nullptr;
        }
        else
        {
            $$ = new Variable(sym);
        }
    
    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);
        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1 + "[]");
            $$ = nullptr;
        } else 
        {
            if ($3->get_type() != INT) {
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A " + gpl_type_to_string($3->get_type()) + " expression");
                $$ = new Variable(sym, $3);
            } 
        if (!sym->is_array() || !sym->is_game_object()) {
            Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
            $$ = nullptr;
        } else {
            int index_value = $3->eval_int();
            $$ = new Variable(sym, $6, $3);
        }
        }

    }
    | T_ID T_LBRACKET expression T_RBRACKET
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);
        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *$1 + "[]");
            $$ = nullptr;
        } else if (!sym->is_array()) {
            
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
            $$ = new Variable();
        } else {
            if ($3->get_type() != INT) {
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A " + gpl_type_to_string($3->get_type()) + " expression");
                $$ = new Variable(sym, $3);
            } else {
                $$ = new Variable(sym, $3);  // Create Variable for array element
            }
        }
    }
    | T_ID T_PERIOD T_ID
    {
        Symbol *sym = Symbol_table::instance()->lookup(*$1);
        if (!sym)
        {
            Error::error(Error::UNDECLARED_VARIABLE, *$1);
            $$ = nullptr;
        }
        else if (!sym->is_game_object())
        {
            Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
            $$ = nullptr;
        }
        else
        {
            $$ = new Variable(sym, $3); // Create Variable for member variable
        }

    }
    ;

//---------------------------------------------------------------------
expression:
    primary_expression 
    { 
        if ($1 == nullptr) {
            $$ = new Expression(0);  // Set to a invalid expression if it's null
        } else {
            $$ = $1;
        }
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

        if (!lhs_valid || !rhs_valid) {
            $$ = new Expression(0);
        }
        else {
            $$ = new Expression(OR, $1, $3);
        }   
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

        if (!lhs_valid || !rhs_valid) {
            $$ = new Expression(0);
        }
        else {
            $$ = new Expression(AND, $1, $3);
        }
    }
    | expression T_LESS_EQUAL expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($1->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "<=", "animation_block");
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "<=", "animation_block");
            $$ = new Expression(0);
        } else {
            $$ = new Expression(LESS_EQUAL, $1, $3);
        }
    }
    | expression T_GREATER_EQUAL expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($1->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, ">=", "animation_block");
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, ">=", "animation_block");
            $$ = new Expression(0);
        } else {
            $$ = new Expression(GREATER_EQUAL, $1, $3);
        }
    }
    | expression T_LESS expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($1->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "<", "animation_block");
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "<", "animation_block");
            $$ = new Expression(0);
        } else {
            $$ = new Expression(LESS_THAN, $1, $3);
        }
    }
    | expression T_GREATER expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($1->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, ">", "animation_block");
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, ">", "animation_block");
            $$ = new Expression(0);
        } else {
            $$ = new Expression(GREATER_THAN, $1, $3);
        }
    }
    | expression T_EQUAL expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($1->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "==", "animation_block");
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "==", "animation_block");
            $$ = new Expression(0);
        } else {
            $$ = new Expression(EQUAL, $1, $3);
        }
    }
    | expression T_NOT_EQUAL expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($1->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "!=", "animation_block");
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!=", "animation_block");
            $$ = new Expression(0);
        } else {
            $$ = new Expression(NOT_EQUAL, $1, $3);
        }
    }
    | expression T_PLUS expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if (($1->get_type() == ANIMATION_BLOCK && $3->get_type() & GAME_OBJECT)
                   || ($1->get_type() & GAME_OBJECT && $3->get_type() == ANIMATION_BLOCK)) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "+");
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "+");
            $$ = new Expression(0);
        } else if ($1->get_type() == ANIMATION_BLOCK || $1->get_type() & GAME_OBJECT) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "+");
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK || $3->get_type() & GAME_OBJECT) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "+");
            $$ = new Expression(0);
        } else if ($1->get_type() == STRING || $3->get_type() == STRING) {
            $$ = new Expression(PLUS, $1, $3);
            $$->set_type(STRING);
        } else {
            $$ = new Expression(PLUS, $1, $3);
        }
    }
    | expression T_MINUS expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", "animation_block");
            $$ = new Expression(0);
        } else if ($1->get_type() == STRING || $3->get_type() == STRING) {
            if ($1->get_type() == STRING) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-", gpl_type_to_string($1->get_type()));
            $$ = new Expression(0);
            } 
            if ($3->get_type() == STRING) {
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string($3->get_type()));
                $$ = new Expression(0);
            }
        } 
        else {
            $$ = new Expression(MINUS, $1, $3);
        }
    }
    | expression T_MULTIPLY expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*", "animation_block");
            $$ = new Expression(0);
        } else if (!($1->get_type() == INT || $1->get_type() == DOUBLE) || 
                   !($3->get_type() == INT || $3->get_type() == DOUBLE)) {
            if ($1->get_type() != INT && $1->get_type() != DOUBLE) {
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*", gpl_type_to_string($1->get_type()));
            }
            if ($3->get_type() != INT && $3->get_type() != DOUBLE) {
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*", gpl_type_to_string($3->get_type()));
            }
            $$ = new Expression(0);
        } else {
            $$ = new Expression(MULTIPLY, $1, $3);
        }
    }
    | expression T_DIVIDE expression 
    {
        if ($1 == nullptr || $3 == nullptr) {
            $$ = new Expression(0);
        } else if ($3->get_type() == ANIMATION_BLOCK) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/", "animation_block");
            $$ = new Expression(0);
        } else if (!($1->get_type() == INT || $1->get_type() == DOUBLE) || 
                   !($3->get_type() == INT || $3->get_type() == DOUBLE)) {
            if ($1->get_type() != INT && $1->get_type() != DOUBLE) {
                Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/", gpl_type_to_string($1->get_type()));
            }
            if ($3->get_type() != INT && $3->get_type() != DOUBLE) {
                Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/", gpl_type_to_string($3->get_type()));
            }
            $$ = new Expression(0);
        } else {
            $$ = new Expression(DIVIDE, $1, $3);
        }
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

        if (!lhs_valid || !rhs_valid) {
            $$ = new Expression(0);
        }
        else {
            $$ = new Expression(MOD, $1, $3);
        }
    }
    | T_MINUS expression %prec UNARY_OPS 
    {
        if ($2 == nullptr) {
            $$ = new Expression(0);
        } else if ($2->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                         "-", 
                         gpl_type_to_string($2->get_type()));
            $$ = new Expression(0);
        } else {
            $$ = new Expression(UNARY_MINUS, $2);
        }
    }
    | T_NOT expression %prec UNARY_OPS 
    {
        if ($2 == nullptr) {
            $$ = new Expression(0);
        } 
        else if ($2->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!", gpl_type_to_string($2->get_type()));
            $$ = new Expression(0);
        } 
        else {
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
    | expression T_TOUCHES expression
    {
        bool left_valid = ($1 != nullptr && ($1->get_type() & GAME_OBJECT));
        bool right_valid = ($3 != nullptr && ($3->get_type() & GAME_OBJECT));

        // Check left operand
        if (!left_valid) {
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, "Left");
        }

        // Check right operand separately
        if (!right_valid) {
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, "Right");
        }

        // Create expression only if both are valid
        if (!left_valid || !right_valid) {
            $$ = new Expression(0);  // Invalid expression
        } else {
            $$ = new Expression(TOUCHES, $1, $3);
        }
    }
    | expression T_NEAR expression
    {
        if ($1->get_type() & GAME_OBJECT && $3->get_type() & GAME_OBJECT) {
            $$ = new Expression(NEAR, $1, $3);
        } else {
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT);
            $$ = new Expression(0);
        }
    }
    ;

//---------------------------------------------------------------------
primary_expression:
    T_LPAREN expression T_RPAREN 
    { 
        if ($2 == nullptr) {
            $$ = new Expression(0);  // Default invalid expression null
        } else {
            $$ = $2;
        }
    }
    | variable 
    { 
        if ($1 == nullptr) {
            $$ = new Expression(0);  // Default invalid expression if variable is null
        } else {
            $$ = new Expression($1);
        }
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
