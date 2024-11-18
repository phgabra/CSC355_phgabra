#include "variable.h"
#include "symbol.h"
#include "expression.h"
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
    if (m_expression)  // If this is an array access
    {
        int index = eval_index_with_error_checking();
        return m_symbol->get_int_value(index);
    }
    return m_symbol->get_int_value();
}

double Variable::get_double_value() const
{
    if (m_expression)
    {
        int index = eval_index_with_error_checking();
        return m_symbol->get_double_value(index);
    }
    return m_symbol->get_double_value();
}

string Variable::get_string_value() const
{
    if (m_expression)
    {
        int index = eval_index_with_error_checking();
        return m_symbol->get_string_value(index);
    }
    return m_symbol->get_string_value();
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
