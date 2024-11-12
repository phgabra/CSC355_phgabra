#include "symbol.h"
#include "gpl_assert.h"

using namespace std;

Symbol::Symbol(string name, int initial_value)
{
  m_name = name;
  m_type = INT;
  m_data_void_ptr = (void *) new int(initial_value);
  m_size = UNDEFINED_SIZE;
  validate();
}

Symbol::Symbol(string name, double initial_value)
{
  m_name = name;
  m_type = DOUBLE;
  m_data_void_ptr = (void *) new double(initial_value);
  m_size = UNDEFINED_SIZE;
  validate();
}

Symbol::Symbol(string name, string initial_value)
{
  m_name = name;
  m_type = STRING;
  m_data_void_ptr = (void *) new string(initial_value);
  m_size = UNDEFINED_SIZE;
  validate();
}

void Symbol::set_int_value(int value, int index)
{
    validate_type_and_index(INT, index);
    if (is_array()) {
        ((int*)m_data_void_ptr)[index] = value;
    } else {
        *((int*)m_data_void_ptr) = value;
    }
}

void Symbol::set_double_value(double value, int index)
{
    validate_type_and_index(DOUBLE, index);
    if (is_array()) {
        ((double*)m_data_void_ptr)[index] = value;
    } else {
        *((double*)m_data_void_ptr) = value;
    }
}

void Symbol::set_string_value(const std::string &value, int index)
{
    validate_type_and_index(STRING, index);
    if (is_array()) {
        ((std::string*)m_data_void_ptr)[index] = value;
    } else {
        *((std::string*)m_data_void_ptr) = value;
    }
}



Symbol::Symbol(string name, Gpl_type type, int size)
{
  m_name = name;
  m_type = type;
  m_size = size;
  
  if (type == INT_ARRAY)
  {
      m_data_void_ptr = (void *) new int[size];
      for (int i = 0; i < size; i++)
          ((int *) m_data_void_ptr)[i] = 42;  // Initialize all ints to 42
  }
  else if (type == DOUBLE_ARRAY)
  {
      m_data_void_ptr = (void *) new double[size];
      for (int i = 0; i < size; i++)
          ((double *) m_data_void_ptr)[i] = 3.14159;  // Initialize all doubles to 3.14159
  }
  else if (type == STRING_ARRAY)
  {
      m_data_void_ptr = (void *) new string[size];
      for (int i = 0; i < size; i++)
          ((string *) m_data_void_ptr)[i] = "Hello world";  // Initialize all strings to "Hello world"
  }
  validate();
}

Symbol::~Symbol()
{
  // The Symbol "owns" the object it contains, it must delete it
  if (!is_array())
    switch (m_type)
    {
      case INT: delete (int *) m_data_void_ptr; break;
      case DOUBLE: delete (double *) m_data_void_ptr; break;
      case STRING: delete (string *) m_data_void_ptr; break;
      default: assert(0);
    }
  else
    switch (m_type)
    {
      case INT_ARRAY: delete [] (int *) m_data_void_ptr; break;
      case DOUBLE_ARRAY: delete [] (double *) m_data_void_ptr; break;
      case STRING_ARRAY: delete [] (string *) m_data_void_ptr; break;
      default: assert(0);
    }
}

// strip away the ARRAY bit from the type if there is one
Gpl_type Symbol::get_base_type() const 
{

  if (m_type & ARRAY)
      return (Gpl_type) (m_type - ARRAY);
  else
      return m_type;
}

void Symbol::validate_type_and_index(Gpl_type type, int index) const
{
  assert(m_type & type);

  assert((index == UNDEFINED_INDEX && m_size == UNDEFINED_SIZE) 
         || (index >= 0 && m_size >= 1 && index < m_size));
}

int Symbol::get_int_value(int index /* = UNDEFINED_INDEX */) const
{
  validate_type_and_index(INT, index);
  if (is_array())
    return ((int *) m_data_void_ptr)[index];
  else
    return *((int *) m_data_void_ptr);
}

double Symbol::get_double_value(int index /* = UNDEFINED_INDEX */) const
{
  validate_type_and_index(DOUBLE, index);
  if (is_array())
      return ((double *) m_data_void_ptr)[index];
  else
      return *((double *) m_data_void_ptr);
}

string Symbol::get_string_value(int index /* = UNDEFINED_INDEX */) const
{
  validate_type_and_index(STRING, index);
  if (is_array())
      return ((string *) m_data_void_ptr)[index];
  else
      return *((string *) m_data_void_ptr);
}

void Symbol::print(ostream &os) const
{
  Gpl_type base_type = get_base_type();

  if (is_array()) {
    for (int i = 0; i < m_size; i++) {
      os << gpl_type_to_string(base_type) << " " << m_name << "[" << i << "] = ";
      if (base_type == INT)
        os << get_int_value(i) << endl;
      else if (base_type == DOUBLE)
        os << get_double_value(i) << endl;
      else if (base_type == STRING)
        os << "\"" << get_string_value(i) << "\"" << endl;
    }
  } else {
    os << gpl_type_to_string(base_type) << " " << m_name << " = ";
    if (base_type == INT)
      os << get_int_value() << endl;
    else if (base_type == DOUBLE)
      os << get_double_value() << endl;
    else if (base_type == STRING)
      os << "\"" << get_string_value() << "\"" << endl;
  }
}

void Symbol::validate() const
{
  if (m_type & ARRAY)
    assert(m_size > 0);
  else
    assert(m_size == UNDEFINED_SIZE);

  assert(m_data_void_ptr != NULL);
  assert(m_name != "");
  assert(m_size != 0);
}
