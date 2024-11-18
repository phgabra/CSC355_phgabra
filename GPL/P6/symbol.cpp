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


Symbol::Symbol(string name, Gpl_type type, int size)
{
    m_name = name;
    m_type = type;
    m_size = size;

    switch (type)
    {
        case INT_ARRAY:
            m_data_void_ptr = (void *) new int[size];
            // Initialize all elements to 0
            for (int i = 0; i < size; i++) {
                ((int*)m_data_void_ptr)[i] = 0;
            }
            break;
            
        case DOUBLE_ARRAY:
            m_data_void_ptr = (void *) new double[size];
            // Initialize all elements to 0.0
            for (int i = 0; i < size; i++) {
                ((double*)m_data_void_ptr)[i] = 0.0;
            }
            break;
            
        case STRING_ARRAY:
            m_data_void_ptr = (void *) new string[size];
            // Initialize all elements to empty string
            for (int i = 0; i < size; i++) {
                ((string*)m_data_void_ptr)[i] = "";
            }
            break;
            
        default:
            assert(0);  // if somehow an invalid type is passed in
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

//Added these series of setter methods
void Symbol::set_value(int value) {
    assert(is_int() && !is_array());
    int* int_ptr = static_cast<int*>(m_data_void_ptr);
    *int_ptr = value;
}

void Symbol::set_value(double value) {
    assert(is_double() && !is_array());
    double* double_ptr = static_cast<double*>(m_data_void_ptr);
    *double_ptr = value;
}

void Symbol::set_value(const std::string& value) {
    assert(is_string() && !is_array());
    std::string* string_ptr = static_cast<std::string*>(m_data_void_ptr);
    *string_ptr = value;
}

void Symbol::set_value(int index, int value) {
    assert(m_type == INT_ARRAY && m_data_void_ptr != nullptr);
    assert(index_within_range(index));
    ((int*)m_data_void_ptr)[index] = value;
}

void Symbol::set_value(int index, double value) {
    assert(m_type == DOUBLE_ARRAY && m_data_void_ptr != nullptr);
    assert(index_within_range(index));
    ((double*)m_data_void_ptr)[index] = value;
}

void Symbol::set_value(int index, const string& value) {
    assert(m_type == STRING_ARRAY && m_data_void_ptr != nullptr);
    assert(index_within_range(index));
    ((std::string*)m_data_void_ptr)[index] = value;
}

void Symbol::print(ostream &os) const
{

    //if it's an array, get the type and name of the array
    //as well as value at the current index
    //and print in the appropriate format for each element
    //contained in the array
    if (is_array())
    {
        for (int i = 0; i < m_size; i++)
        {
            os << gpl_type_to_string(get_base_type()) << " " << m_name << "[" << i << "] = ";
            if (is_int())
                os << get_int_value(i);
            else if (is_double())
                os << get_double_value(i);
            else if (is_string())
                os << "\"" << get_string_value(i) << "\"";
        
            if(i < m_size - 1)
                os << std::endl;
        }
    }
    //if it's not an array, just print the type, name, and value of the symbol
    else
    {
        os << gpl_type_to_string(get_base_type()) << " ";

        // Print name
        os << m_name;

        os << " = ";

        if (is_int())
            os << get_int_value();
        else if (is_double())
            os << get_double_value();
        else if (is_string())
            os << "\"" << get_string_value() << "\"";
    }

    os << endl;
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
