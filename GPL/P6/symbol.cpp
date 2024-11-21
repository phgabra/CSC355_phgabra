#include "symbol.h"
#include "gpl_assert.h"
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
            for (int i = 0; i < size; i++)
                ((int *)m_data_void_ptr)[i] = 0;
            break;

        case DOUBLE_ARRAY:
            m_data_void_ptr = (void *) new double[size];
            for (int i = 0; i < size; i++)
                ((double *)m_data_void_ptr)[i] = 0.0;
            break;

        case STRING_ARRAY:
            m_data_void_ptr = (void *) new string[size];
            for (int i = 0; i < size; i++)
                ((string *)m_data_void_ptr)[i] = "";
            break;

        case CIRCLE_ARRAY:
            m_data_void_ptr = (void *) new Circle[size];
            break;

        case RECTANGLE_ARRAY:
            m_data_void_ptr = (void *) new Rectangle[size];
            break;

        case TRIANGLE_ARRAY:
            m_data_void_ptr = (void *) new Triangle[size];
            break;

        case TEXTBOX_ARRAY:
            m_data_void_ptr = (void *) new Textbox[size];
            break;

        case PIXMAP_ARRAY:
            m_data_void_ptr = (void *) new Pixmap[size];
            break;

        default:
            assert(0); // Unhandled type
    }

    validate();
}

Symbol::Symbol(string name, Gpl_type type)
{
    assert(type == CIRCLE
           || type == RECTANGLE
           || type == TRIANGLE
           || type == TEXTBOX
           || type == PIXMAP
           || type == ANIMATION_BLOCK
          );
  
    m_name = name;
    m_type = type;
    m_size = UNDEFINED_SIZE;
  
    switch(type)
    {
        case CIRCLE:
            m_data_void_ptr = (void *) new Circle();
            break;
        case RECTANGLE:
            m_data_void_ptr = (void *) new Rectangle();
            break;
        case TRIANGLE:
            m_data_void_ptr = (void *) new Triangle();
            break;
        case TEXTBOX:
            m_data_void_ptr = (void *) new Textbox();
            break;
        case PIXMAP:
            m_data_void_ptr = (void *) new Pixmap();
            break;
        case ANIMATION_BLOCK:
            m_data_void_ptr = nullptr; // No object created until explicitly set
            break;
        default:
            assert(0); // Unhandled type
    }
}

Symbol::~Symbol()
{
  // The Symbol "owns" the object it contains, it must delete it
  if (!is_array())
  {
    switch (m_type)
    {
      case INT: 
          delete (int *) m_data_void_ptr; 
          break;
      case DOUBLE: 
          delete (double *) m_data_void_ptr; 
          break;
      case STRING: 
          delete (string *) m_data_void_ptr; 
          break;
      case CIRCLE: 
          delete (Circle *) m_data_void_ptr; 
          break;
      case RECTANGLE: 
          delete (Rectangle *) m_data_void_ptr; 
          break;
      case TRIANGLE: 
          delete (Triangle *) m_data_void_ptr; 
          break;
      case TEXTBOX: 
          delete (Textbox *) m_data_void_ptr; 
          break;
      case PIXMAP: 
          delete (Pixmap *) m_data_void_ptr; 
          break;
      case ANIMATION_BLOCK: 
          delete (Animation_block *) m_data_void_ptr; 
          break;
      default: 
          assert(0); // Unhandled type
    }
  }
  else // Arrays
  {
    switch (m_type)
    {
      case INT_ARRAY: 
          delete [] (int *) m_data_void_ptr; 
          break;
      case DOUBLE_ARRAY: 
          delete [] (double *) m_data_void_ptr; 
          break;
      case STRING_ARRAY: 
          delete [] (string *) m_data_void_ptr; 
          break;
      default: 
          assert(0); // Arrays of other types are not supported
    }
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

Game_object *Symbol::get_game_object_value(int index /* = UNDEFINED_INDEX */) const
{
    validate_type_and_index(GAME_OBJECT, index);
  
    if (is_array())
    {
      // since this is an array of actual object, can't consider it an array of Game_object
      // must consider each type: Rectangle, Triangle, etc...

      switch(m_type)
      {
        case CIRCLE_ARRAY:
        {
          Circle *object_array = (Circle *) m_data_void_ptr;
          return object_array + index;
          break;
        }
        case RECTANGLE_ARRAY:
        {
            Rectangle *object_array = (Rectangle *) m_data_void_ptr;
            return &object_array[index];
        }
        case TRIANGLE_ARRAY:
        {
            Triangle *object_array = (Triangle *) m_data_void_ptr;
            return &object_array[index];
        }
        case TEXTBOX_ARRAY:
        {
            Textbox *object_array = (Textbox *) m_data_void_ptr;
            return &object_array[index];
        }
        case PIXMAP_ARRAY:
        {
            Pixmap *object_array = (Pixmap *) m_data_void_ptr;
            return &object_array[index];
        }

        default: 
        {
          assert(false && "given type is not handled by switch");
          return NULL;
        }
      }
    }
    else
      // m_data_void_ptr is a void pointer, that really points to a Game_object.
      return (Game_object *) m_data_void_ptr;
}

Animation_block *Symbol::get_animation_block_value() const
  {
    validate_type_and_index(ANIMATION_BLOCK, UNDEFINED_INDEX);
  
    // arrays of Animation_blocks are not allowed
    assert(!is_array());
    // return &(*((Animation_block *) m_data_void_ptr));
    return (Animation_block *) m_data_void_ptr;
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
    // If it's an array, iterate through elements and print them
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
            else if (is_game_object())
            {
                Game_object* obj = get_game_object_value(i);
                if (obj)
                {
                    obj->print(m_name, os); // Pass the symbol name and output stream
                }
                else
                    os << "null";
            }
            
            if (i < m_size - 1)
                os << std::endl;
        }
    }
    else // If it's not an array, print the single value
    {
        if (is_int())
            os << gpl_type_to_string(get_base_type()) << " " << m_name << " = " << get_int_value();
        else if (is_double())
            os << gpl_type_to_string(get_base_type()) << " " << m_name << " = " << get_double_value();
        else if (is_string())
            os << gpl_type_to_string(get_base_type()) << " " << m_name << " = " << "\"" << get_string_value() << "\"";
        else if (is_game_object())
        {
            Game_object* obj = get_game_object_value();
            if (obj)
            {
                obj->print(m_name, os); // Pass the symbol name and output stream
            }
            else
                os << "null";
        }
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
