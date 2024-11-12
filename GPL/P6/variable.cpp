#include "variable.h"
#include "symbol.h"
#include "expression.h"
#include "gpl_type.h"
#include "gpl_assert.h"
#include "error.h"
#include <sstream>
using namespace std;

Variable::Variable(Symbol *symbol)
    : m_symbol(symbol), m_expression(nullptr)
{
    assert(symbol->get_type() != INT_ARRAY && 
           symbol->get_type() != DOUBLE_ARRAY && 
           symbol->get_type() != STRING_ARRAY);
}

Variable::Variable(Symbol *symbol, Expression *expression)
    : m_symbol(symbol), m_expression(expression)
{
    assert(symbol->get_type() == INT_ARRAY || 
           symbol->get_type() == DOUBLE_ARRAY || 
           symbol->get_type() == STRING_ARRAY);
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
    if (m_expression) {
        // For array elements, get value at the evaluated index
        return m_symbol->get_int_value(eval_index_with_error_checking());
    }
    return m_symbol->get_int_value();  // For simple variables
}

double Variable::get_double_value() const
{
    if (m_expression) {
        // For array elements, get value at the evaluated index
        return m_symbol->get_double_value(eval_index_with_error_checking());
    }
    return m_symbol->get_double_value();  // For simple variables
}

string Variable::get_string_value() const
{
    if (m_expression) {
        // For array elements, get value at the evaluated index
        return m_symbol->get_string_value(eval_index_with_error_checking());
    }
    return m_symbol->get_string_value();  // For simple variables
}

void Variable::set(int value)
{
    // Ensure this Variable is of type INT or INT_ARRAY
    if (m_symbol->get_type() == INT || m_symbol->get_type() == INT_ARRAY) {
        if (m_expression) {
            // For array elements, set the value at the evaluated index
            m_symbol->set_int_value(value, eval_index_with_error_checking());
        } else {
            // For simple variables, set the integer value directly
            m_symbol->set_int_value(value);
        }
    } else {
        Error::error(Error::ASSIGNMENT_TYPE_ERROR, m_symbol->get_name(), "int");
    }
}

void Variable::set(double value)
{
    // Ensure this Variable is of type DOUBLE or DOUBLE_ARRAY
    if (m_symbol->get_type() == DOUBLE || m_symbol->get_type() == DOUBLE_ARRAY) {
        if (m_expression) {
            // For array elements, set the value at the evaluated index
            m_symbol->set_double_value(value, eval_index_with_error_checking());
        } else {
            // For simple variables, set the double value directly
            m_symbol->set_double_value(value);
        }
    } else {
        Error::error(Error::ASSIGNMENT_TYPE_ERROR, m_symbol->get_name(), "double");
    }
}

void Variable::set(string value)
{
    // Ensure this Variable is of type STRING or STRING_ARRAY
    if (m_symbol->get_type() == STRING || m_symbol->get_type() == STRING_ARRAY) {
        if (m_expression) {
            // For array elements, set the value at the evaluated index
            m_symbol->set_string_value(value, eval_index_with_error_checking());
        } else {
            // For simple variables, set the string value directly
            m_symbol->set_string_value(value);
        }
    } else {
        Error::error(Error::ASSIGNMENT_TYPE_ERROR, m_symbol->get_name(), "string");
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
