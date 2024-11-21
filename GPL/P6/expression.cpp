#include <cmath>
using namespace std;

#include "expression.h"
#include "constant.h"
#include "variable.h"
#include "gpl_assert.h"
#include "error.h"

Expression::Expression(int value)
{
    m_variable = nullptr;
    m_lhs = nullptr;
    m_rhs = nullptr;

    m_type = INT;
    m_constant = new Constant(value);
}

Expression::Expression(double value)
{
    m_variable = nullptr;
    m_lhs = nullptr;
    m_rhs = nullptr;

    m_type = DOUBLE;
    m_constant = new Constant(value);
}

Expression::Expression(string *value)
{
    m_variable = nullptr;
    m_lhs = nullptr;
    m_rhs = nullptr;

    m_type = STRING;
    m_constant = new Constant(*value);
}

Expression::Expression(Variable *variable)
{
    if (variable == nullptr) {
        m_constant = nullptr;
        m_variable = nullptr;
        m_lhs = nullptr;
        m_rhs = nullptr;

        m_type = INT;

        return;
    } 

    m_constant = nullptr;
    m_lhs = nullptr;
    m_rhs = nullptr;

    m_type = variable->get_type();
    m_variable = variable;
    m_is_element = variable->is_array();
}

Expression::Expression(Operator_type op,
                       Expression *lhs,
                       Expression *rhs
                       )
{
    m_constant = nullptr;
    m_variable = nullptr;

    m_op = op;
    m_lhs = lhs;
    m_rhs = rhs;

    
  switch (op) {
      case PLUS:
      case MINUS:
      case MULTIPLY:
      case DIVIDE:
          m_type = (lhs->m_type == DOUBLE || rhs->m_type == DOUBLE) ? DOUBLE : INT;
          break;

      case AND:
      case OR:
      case EQUAL:
      case NOT_EQUAL:
      case LESS_THAN:
      case LESS_EQUAL:
      case GREATER_THAN:
      case GREATER_EQUAL:
          m_type = INT;
          break;

      case MOD:
          m_type = INT;
          break;
      default:
          assert(false && "Unknown unary operator");
  }
}

Expression::Expression(Operator_type op, Expression *operand)
{
    m_rhs = nullptr;
    m_constant = nullptr;
    m_variable = nullptr;

    m_op = op;
    m_lhs = operand;
    
    switch (op) {
        case NOT:
            m_type = INT;
            break;
        case UNARY_MINUS:
            m_type = operand->m_type;
            break;
        case ABS:
            m_type = operand->m_type;
            break;
        case SIN:
        case COS:
        case TAN:
        case ASIN:
        case ACOS:
        case ATAN:
        case SQRT:
            m_type = DOUBLE;
            break;
        case FLOOR:
        case RANDOM:
            m_type = INT;
            break;
        default:
            assert(false && "Unknown  operator");
    }
}

int Expression::eval_int()
{
    assert(m_type == INT || m_type == DOUBLE);

    if (m_type == DOUBLE)
        return static_cast<int>(eval_double());

    if (m_constant != NULL)
    {
    assert(m_variable == NULL);
    assert(m_lhs == NULL && m_rhs == NULL);

    return m_constant->get_int_value();
  }
  else if (m_variable != NULL)
  {
    assert(m_constant == NULL);
    assert(m_lhs == NULL && m_rhs == NULL);
    return m_variable->get_int_value();
  }

  // must be a binary or unary expression
  //   both binary and unary have m_lhs
  assert(m_lhs);

  if (m_op != NOT
      && m_op != UNARY_MINUS
      && m_op != FLOOR
      && m_op != RANDOM
      && m_op != ABS
     )
    assert(m_rhs);
  else assert(!m_rhs);


  // idea: replace switch with an array of labels and a goto
  switch (m_op)
  {
    case PLUS:
        return m_lhs->eval_int() + m_rhs->eval_int();
    case MINUS:
        return m_lhs->eval_int() - m_rhs->eval_int();
    case MULTIPLY:
        return m_lhs->eval_int() * m_rhs->eval_int();
    case DIVIDE:
    {
        int rhs;
        rhs = m_rhs->eval_int();
        // if this is still compile time, then don't allow
        // a floating point exception
        if (rhs == 0 && !Error::runtime())
        {
          Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
          return 0;
        }
        return m_lhs->eval_int() / rhs;
    }
    case MOD:
    {
        int rhs;
        rhs = m_rhs->eval_int();
        // if this is still compile time, then don't allow
        // a floating point exception
        if (rhs == 0 && !Error::runtime())
        {
          Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
          return 0;
        }
        return m_lhs->eval_int() % rhs;

    }
    case NOT:
        assert(m_rhs == NULL);
        // eval m_lhs as a double in case it is a double
        // INT's can be evaluated as either an INT or DOUBLE
        return !m_lhs->eval_double();
    case UNARY_MINUS:
        assert(m_rhs == NULL);
        return -m_lhs->eval_int();
    case ABS:
        return (int) std::abs(m_lhs->eval_int());
    case FLOOR:
        return (int) floor(m_lhs->eval_double());
    case RANDOM:
    {
        int range = (int) floor(m_lhs->eval_double());
        if (range < 1)
        {
          Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, 
                       m_lhs->get_type() == INT ?  
                          to_string(m_lhs->eval_int())
                          : to_string(m_lhs->eval_double())
                      );
          range = 2;
        }
        return rand() % range;
    }
    case AND:
        return m_lhs->eval_double() && m_rhs->eval_double();
    case OR:
        return m_lhs->eval_double() || m_rhs->eval_double();
    case EQUAL:
        if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
          return m_lhs->eval_string() == m_rhs->eval_string();
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
          return (m_lhs->eval_int() == m_rhs->eval_int());
        else return (m_lhs->eval_double() == m_rhs->eval_double());
    case NOT_EQUAL:
        if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
          return m_lhs->eval_string() != m_rhs->eval_string();
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
          return m_lhs->eval_int() != m_rhs->eval_int();
        else return m_lhs->eval_double() != m_rhs->eval_double();

    case LESS_THAN:
        if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
          return m_lhs->eval_string() < m_rhs->eval_string();
        else if (m_lhs->m_type == DOUBLE || m_rhs->m_type == DOUBLE)
          return m_lhs->eval_double() < m_rhs->eval_double();
        else return m_lhs->eval_int() < m_rhs->eval_int();

    case LESS_EQUAL:
        if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
          return m_lhs->eval_string() <= m_rhs->eval_string();
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
          return m_lhs->eval_int() <= m_rhs->eval_int();
        else return m_lhs->eval_double() <= m_rhs->eval_double();
    case GREATER_THAN:
        if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
          return m_lhs->eval_string() > m_rhs->eval_string();
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
          return m_lhs->eval_int() > m_rhs->eval_int();
        else return m_lhs->eval_double() > m_rhs->eval_double();
    case GREATER_EQUAL:
        if (m_lhs->m_type == STRING || m_rhs->m_type == STRING)
          return m_lhs->eval_string() >= m_rhs->eval_string();
        else if (m_lhs->m_type == INT && m_rhs->m_type == INT)
          return m_lhs->eval_int() >= m_rhs->eval_int();
        else return m_lhs->eval_double() >= m_rhs->eval_double();
    // no other operators are legal for int
    default: assert(0 && "undefined switch value");
  }
  assert(false && "should never reach this");
  return 0; // to prevent a compilation warning
}

double Expression::eval_double()
{
  // INT expressions can be in an expression tree that is double
  // when this happens, evaluate the int as a double
  assert(m_type == INT || m_type == DOUBLE);

  if (m_type == INT)
    return (double) eval_int();
  else if (m_constant != NULL)
  {
    assert(m_constant);
    return m_constant->get_double_value();
  }
  else if (m_variable != NULL)
  {
    assert(m_variable);
    return m_variable->get_double_value();
  }

  // must be a unary or binary expression
  //   both unary and binary expressions have a lhs
  assert(m_lhs);

  // if it is not one of the legal double unary operators
  // there must be a m_rhs
  if (m_op != SIN
      && m_op != COS
      && m_op != TAN
      && m_op != ASIN
      && m_op != ACOS
      && m_op != ATAN
      && m_op != SQRT
      && m_op != ABS
      && m_op != UNARY_MINUS
     )
  {
    assert(m_rhs);
  }
  switch (m_op)
  {
    case PLUS:
      return m_lhs->eval_double() + m_rhs->eval_double();
    case MINUS:
      return m_lhs->eval_double() - m_rhs->eval_double();
    case MULTIPLY:
      return m_lhs->eval_double() * m_rhs->eval_double();
    case DIVIDE:
    {
      double rhs = m_rhs->eval_double();
      // if this is still compile time, then don't allow
      // a floating point exception
      if (rhs == 0 && !Error::runtime())
      {
        Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
        return 0;
      }
      return m_lhs->eval_double() / rhs;
    }
    case UNARY_MINUS:
      return -m_lhs->eval_double();
    case SIN:
      return sin(m_lhs->eval_double() * M_PI / 180.0);
    case COS:
      return cos(m_lhs->eval_double() * M_PI / 180.0);
    case TAN :
      return tan(m_lhs->eval_double() * M_PI / 180.0);
    case ASIN:
      return asin(m_lhs->eval_double()) * 180.0 / M_PI;
    case ACOS:
      return acos(m_lhs->eval_double()) * 180.0 / M_PI;
    case ATAN :
      return atan(m_lhs->eval_double()) * 180.0 / M_PI;
    case SQRT:
      return sqrt(m_lhs->eval_double());
    case ABS:
      return std::abs(m_lhs->eval_double());
    case FLOOR:
      assert(false && "should never have a double floor");
      return floor(m_lhs->eval_double());
    // no other operators are legal double operators
    default: assert(0);
  }
  assert(false && "should never get here");
  return 0; // to prevent a compiler warning
}

string Expression::eval_string()
{
  // can only call eval_string() on the following types of expressions
  assert(m_type == STRING || m_type == INT || m_type == DOUBLE || m_type == INT_ARRAY || m_type == DOUBLE_ARRAY);

  // INT and DOUBLE expressions are automatically cast into strings
  // for example:  the int 42 is converted into the string "42"
  // this is done because there is no other way to convert numbers into
  // strings.
  if (m_type == INT)
  {
    return to_string(eval_int());
  }
  if (m_type == DOUBLE)
  {
    return to_string(eval_double());
  }
  if (m_constant != NULL)
  {
    assert(m_variable == NULL);
    return m_constant->get_string_value();
  }
  if (m_variable != NULL)
  {
    assert(m_constant == NULL);
    return m_variable->get_string_value();
  }

  // must really be a string expression
  // the only legal string operator is (+)
  // (that is, the only one that produces a string, ==, <, > etc produce INT)
  assert(m_lhs != NULL && m_rhs != NULL);
  assert(m_op == PLUS);
  return m_lhs->eval_string() + m_rhs->eval_string();
}

Animation_block *Expression::eval_animation_block()
{
    // Ensure the Expression type is ANIMATION_BLOCK
    assert(m_type == ANIMATION_BLOCK);

    // Retrieve the Animation_block* from the associated Variable
    return m_variable->get_animation_block_value();
}
