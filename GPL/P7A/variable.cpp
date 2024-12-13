#include "variable.h"
#include "symbol.h"
#include "expression.h"
#include "game_object.h"
#include "gpl_type.h"
#include "gpl_assert.h"
#include "error.h"
#include <sstream>
using namespace std;

Variable::Variable(Symbol *symbol)
{
    m_symbol = symbol;
    m_expression = nullptr;  // Not an array access
    m_type = m_symbol->get_type();
    m_is_valid = true;
}

Variable::Variable(Symbol *symbol, Expression *expression)
{
    m_symbol = symbol;
    m_expression = expression;  // Array access with index

    // Set m_type to the element type rather than the full array type
    if (m_symbol->get_type() == INT_ARRAY)
        m_type = INT;
    else if (m_symbol->get_type() == DOUBLE_ARRAY)
        m_type = DOUBLE;
    else if (m_symbol->get_type() == STRING_ARRAY)
        m_type = STRING;
    else
        m_type = m_symbol->get_type();  // For non-array cases

    m_is_valid = true;
    m_size = m_symbol->size();
}

Variable::Variable(Symbol *symbol, std::string field)
    : m_symbol(symbol), m_field(new std::string(field))
{
    if (symbol->is_game_object()) // Ensure the symbol represents a game object
    {
        Game_object *game_object = symbol->get_game_object_value();
        assert(game_object != nullptr); // Ensure the game object exists

        // Use get_member_variable_type to determine the type of the member variable
        Status status = game_object->get_member_variable_type(field, m_type);
        if (status != OK)
        {
            Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, field); // Handle unknown member
            m_type = NO_TYPE;
            m_is_valid = false;
        }
        else
        {
            m_is_valid = true;
        }

        m_base_game_object_type = symbol->get_type(); // Store the base game object type
    }
    else
    {
        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, symbol->get_name());
        m_type = NO_TYPE;
        m_is_valid = false; // Mark as invalid if not a game object
    }
}

Variable::Variable(Symbol *symbol, Expression *expression, std::string field)
    : m_symbol(symbol), m_expression(expression), m_field(new std::string(field))
{
    // Ensure the symbol represents a game object array
    if (symbol->is_game_object() && symbol->is_array())
    {
        int index = m_expression->eval_int(); // Evaluate the index

        // Retrieve the game object at the given index
        Game_object *game_object = symbol->get_game_object_value(index);
        assert(game_object != nullptr); // Ensure the game object exists

        // Use get_member_variable_type to determine the type of the member variable
        Status status = game_object->get_member_variable_type(field, m_type);
        if (status != OK) {
            Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, field); // Handle unknown member
            m_type = NO_TYPE;
            m_is_valid = false;
        } else {
            m_is_valid = true;
        }

        m_base_game_object_type = symbol->get_type(); // Store the base game object type
    }
    else
    {
        Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, symbol->get_name());
        m_type = NO_TYPE;
        m_is_valid = false; // Mark as invalid if not a game object
    }
}


Variable::Variable()
{
    m_symbol = nullptr;
    m_expression = nullptr;
    m_type = INT;  // Default type (can be anything)
    m_is_valid = false;  // Mark as invalid
}

string Variable::get_name() const
{
  string name = m_symbol->get_name();
  // Add [] at the end of name string to indicate the variable is an array.
  if (m_expression)
  {
    name += "[]";
  }
  return name;
}

int Variable::get_int_value() const
{
    if (!m_field) // Non-member variable
    {
        if (!m_expression) // Simple variable
            return m_symbol->get_int_value();
        else // Indexed variable
            return m_symbol->get_int_value(eval_index_with_error_checking());
    }
    else // Member variable like rect.x or rects[k].x
    {
        Game_object *cur_game_object;
        if (!m_expression) // rect.x
            cur_game_object = m_symbol->get_game_object_value();
        else // rects[k].x
            cur_game_object = m_symbol->get_game_object_value(eval_index_with_error_checking());

        int value;
        Status status = cur_game_object->get_member_variable(*m_field, value);
        assert(status == OK);
        return value;
    }
}

double Variable::get_double_value() const
{
    if (!m_field) // Non-member variable
    {
        if (!m_expression) // Simple variable
            return m_symbol->get_double_value();
        else // Indexed variable
            return m_symbol->get_double_value(eval_index_with_error_checking());
    }
    else // Member variable like rect.rotation or rects[k].rotation
    {
        Game_object *cur_game_object;
        if (!m_expression) // rect.rotation
            cur_game_object = m_symbol->get_game_object_value();
        else // rects[k].rotation
            cur_game_object = m_symbol->get_game_object_value(eval_index_with_error_checking());

        double value;
        Status status = cur_game_object->get_member_variable(*m_field, value);
        assert(status == OK);
        return value;
    }
}

std::string Variable::get_string_value() const
{
    if (!m_field) // Non-member variable
    {
        if (!m_expression) // Simple variable
            return m_symbol->get_string_value();
        else // Indexed variable
            return m_symbol->get_string_value(eval_index_with_error_checking());
    }
    else // Member variable like rect.name or rects[k].name
    {
        Game_object *cur_game_object;
        if (!m_expression) // rect.name
            cur_game_object = m_symbol->get_game_object_value();
        else // rects[k].name
            cur_game_object = m_symbol->get_game_object_value(eval_index_with_error_checking());

        std::string value;
        Status status = cur_game_object->get_member_variable(*m_field, value);
        assert(status == OK);
        return value;
    }
}

Animation_block *Variable::get_animation_block_value() const
{
    // Ensure the Variable is of type ANIMATION_BLOCK
    assert(m_type == ANIMATION_BLOCK);

    // Return the stored Animation_block pointer
    return m_symbol->get_animation_block_value();
}

void Variable::set(int value)
{
    if (m_expression)
    {
        int index = eval_index_with_error_checking();
        m_symbol->set_value(index, value);
    }
    else
    {
        m_symbol->set_value(0, value);
    }
}

void Variable::set(double value)
{
    if (m_expression)
    {
        int index = eval_index_with_error_checking();
        m_symbol->set_value(index, value);
    }
    else
    {
        m_symbol->set_value(0, value);
    }
}

void Variable::set(string value)
{
    if (m_expression)
    {
        int index = eval_index_with_error_checking();
        m_symbol->set_value(index, value);
    }
    else
    {
        m_symbol->set_value(0, value);
    }
}

void Variable::set(Animation_block* value)
{
    if (m_expression)
    {
        int index = eval_index_with_error_checking();
        m_symbol->set_value(index, value);
    }
    else
    {
        m_symbol->set_value(0, value);
    }
}

// Evaluate expression if there is one, return index if index is out of bounds, 
// issue error, return 0 (0 is always in bounds)
int Variable::eval_index_with_error_checking() const
{
  assert(m_expression); // should only be called if this is an array

  int index = m_expression->eval_int();

  // an annoying special case
  // if the index is -1 it confuses symbol that uses -1 for 
  //   not an array
  if (m_symbol->index_within_range(index))
  {
    return index;
  }
  else
  {
    Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS,
                 m_symbol->get_name(),to_string(index));

    return 0; // 0 is always within range
  }
}
