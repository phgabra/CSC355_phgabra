
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "gpl_type.h"
#include "variable.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Variable;
class Constant;


class Expression
{
  public:
    Expression(int value);
    Expression(double value);
    Expression(string *value);

    Expression(Variable *variable);
    Expression(Operator_type op,
               Expression *lhs,
               Expression *rhs
              );

    Expression(Operator_type op,
               Expression *operand
              );

    Gpl_type get_type() {return m_type;}
    
    // Evaluate expressions. Check the instructions for more detail.
    int eval_int();
    double eval_double();
    string eval_string();
    Variable* get_variable() const { return m_variable; }
    bool is_constant() {return m_constant != NULL;}
    bool is_array_expression() {
        return m_variable && m_variable->is_array();
    }
    bool eval_variable() {return m_variable;}
    bool is_array_element() {return m_variable && m_variable->is_array_element();}
  private:
    bool m_is_element;
    Gpl_type m_type = NO_TYPE;
    Operator_type m_op = NO_OP;
    Expression *m_rhs = NULL;
    Expression *m_lhs = NULL;
    Constant *m_constant = NULL;
    Variable *m_variable = NULL;

};

#endif // #ifndef EXPRESSION_H
