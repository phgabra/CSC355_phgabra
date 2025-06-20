/*
  class Variable describes an int/double/string/object/block variable
  that can appear on the left hand side (LHS) of an assignment expression
  or in an expression.

  There are three types of class Variable:
    global variables (global to the gpl namespace)
    member variables (a global gpl variable + textual name of the member)
    array element variable (can be either global or member)

  Global variables:
    Global gpl variables live in the symbol table.  class Variable
    is simply a wrapper around a class Symbol in this case.

  Member variables:
    There are two components to a member variable
        1) the object (which lives the the global gpl symbol table)
        2) the name of the member variable
    class Variable implements member variables by storing the
    class Symbol that contains the global object and the textual
    name of the member variable.  class Game_objects provides
    functions to access member variables using textual names.

  Array element variables:
    The array is stored in the symbol table (Symbol *m_symbol)
    The index expression is stored in this Variable clas (in m_expression)

    Before they are retrieved or set, the expression is evaluated and the
    result is passed to the Symbol object
*/

#ifndef VARIABLE_H
#define VARIABLE_H

#include "gpl_type.h"
#include <string>

class Symbol;
class Expression;

class Game_object;
class Animation_block;


class Variable
{
  public:
    // For regular variables.
    Variable(Symbol *symbol);
    // For arrays.
    Variable(Symbol *symbol, Expression *expression);
    // Constructor for member variables like rect.x
    Variable(Symbol *symbol, std::string field);
    // Constructor for indexed member variables like rects[k].x
    Variable(Symbol *symbol, Expression *expression, std::string field);

    // For placeholder variables.
    Variable();

    std::string get_name() const;
    bool is_array() const {return m_expression != NULL;}
    bool is_array_element() const { return is_array() && m_expression != nullptr; }
    // Getter functions.The functions return the value of the variable stored in 
    // the symbol's m_data_void_ptr. The functions need to handle two different types of
    // variables: (1) regular variable, (2) array.
    int get_int_value() const;
    double get_double_value() const;
    std::string get_string_value() const;
    // Getters for Game_object and Animation_block
    Game_object *get_game_object_value() const;
    Animation_block *get_animation_block_value() const; // New function for ANIMATION_BLOCK

    Gpl_type get_type() const {return m_type;}
    // Helper for base game object type
    Gpl_type get_base_game_object_type() const { return m_base_game_object_type; }


    bool is_int() const {return m_type & INT;} 
    bool is_double() const {return m_type & DOUBLE;}
    bool is_numeric() const {return m_type & INT || m_type & DOUBLE;}
    bool is_string() const {return m_type & STRING;}
    // Type checking helpers
    bool is_game_object() const { return m_type & GAME_OBJECT; }
    bool is_animation_block() const { return m_type == ANIMATION_BLOCK; }
    bool is_non_member_animation_block() const { return m_field == nullptr && is_animation_block(); }
    
    // Setter functions. The functions set the value, i.e., m_data_void_ptr,
    // of symbols. Note that m_data_void_ptr is a private member variable meaning that
    // you will want to declare and define setter functions in the Symbol class as well.
    // The functions need to handle two different types of variables: (1) regular variable,
    // (2) array.
    void set(int value);
    void set(double value);
    void set(std::string value);
    int size() const {return m_size;}
    bool is_valid() const {return m_is_valid;}

  private:
    Variable(const Variable&);  // disable default copy constructor
    const Variable &operator=(const Variable&); // disable default assignmnt

    // eval expression if there is one, return index
    // if index is out of bounds, issue error, return 0 (0 is always in bounds)
    int eval_index_with_error_checking() const;

    Symbol *m_symbol = NULL;
    Gpl_type m_type = NO_TYPE;

    Gpl_type m_base_game_object_type = NO_TYPE; // Base type for the game object.

    bool m_is_valid;
    int m_size;
    // The variable object sets m_expression pointer to the expression object
    // that represents an index of an array. For example,
    // arr[5] : 5 is an expression.
    // arr[k] : k is an expression.
    // arra[k+2] : k+2 is an expression.
    // Non-array variable object's m_expressions remains NULL.
    Expression *m_expression = NULL;
    std::string *m_field = nullptr; // Stores the member variable name (e.g., "x").
};


#endif // #ifndef VARIABLE_H

