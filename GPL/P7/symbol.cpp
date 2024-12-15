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
            for (int i = 0; i < size; i++) {
                ((int*)m_data_void_ptr)[i] = 0;
            }
            break;
            
        case DOUBLE_ARRAY:
            m_data_void_ptr = (void *) new double[size];
            for (int i = 0; i < size; i++) {
                ((double*)m_data_void_ptr)[i] = 0.0;
            }
            break;
            
        case STRING_ARRAY:
            m_data_void_ptr = (void *) new string[size];
            for (int i = 0; i < size; i++) {
                ((string*)m_data_void_ptr)[i] = "";
            }
            break;

        // Game object arrays
        case CIRCLE_ARRAY:
            m_data_void_ptr = (void *) new Circle[size];
            for (int i = 0; i < size; i++) {
                new (&((Circle*)m_data_void_ptr)[i]) Circle();
            }
            break;

        case RECTANGLE_ARRAY:
            m_data_void_ptr = (void *) new Rectangle[size];
            for (int i = 0; i < size; i++) {
                new (&((Rectangle*)m_data_void_ptr)[i]) Rectangle();
            }
            break;

        case TRIANGLE_ARRAY:
            m_data_void_ptr = (void *) new Triangle[size];
            for (int i = 0; i < size; i++) {
                new (&((Triangle*)m_data_void_ptr)[i]) Triangle();
            }
            break;

        case TEXTBOX_ARRAY:
            m_data_void_ptr = (void *) new Textbox[size];
            for (int i = 0; i < size; i++) {
                new (&((Textbox*)m_data_void_ptr)[i]) Textbox();
            }
            break;

        case PIXMAP_ARRAY:
            m_data_void_ptr = (void *) new Pixmap[size];
            for (int i = 0; i < size; i++) {
                new (&((Pixmap*)m_data_void_ptr)[i]) Pixmap();
            }
            break;
            
        default:
            assert(false && "Unhandled array type in Symbol constructor");
    }

    validate();
}

Symbol::~Symbol()
{
    if (!is_array())
    {
        assert(m_size == UNDEFINED_SIZE && "Arrays of Animation_block are not allowed");
        switch (m_type)
        {
            case INT: delete (int *) m_data_void_ptr; break;
            case DOUBLE: delete (double *) m_data_void_ptr; break;
            case STRING: delete (string *) m_data_void_ptr; break;
            case CIRCLE: delete (Circle *) m_data_void_ptr; break;
            case RECTANGLE: delete (Rectangle *) m_data_void_ptr; break;
            case TRIANGLE: delete (Triangle *) m_data_void_ptr; break;
            case TEXTBOX: delete (Textbox *) m_data_void_ptr; break;
            case PIXMAP: delete (Pixmap *) m_data_void_ptr; break;
            case ANIMATION_BLOCK: delete static_cast<Animation_block*>(m_data_void_ptr);break;
            default: assert(false);
        }
    }
    else
    {
        switch (m_type)
        {
            case INT_ARRAY: delete[] (int *) m_data_void_ptr; break;
            case DOUBLE_ARRAY: delete[] (double *) m_data_void_ptr; break;
            case STRING_ARRAY: delete[] (string *) m_data_void_ptr; break;
            case CIRCLE_ARRAY: 
                delete[] static_cast<Circle*>(m_data_void_ptr); 
                break;
            case RECTANGLE_ARRAY: 
                delete[] static_cast<Rectangle*>(m_data_void_ptr); 
                break;
            case TRIANGLE_ARRAY: 
                delete[] static_cast<Triangle*>(m_data_void_ptr); 
                break;
            case TEXTBOX_ARRAY: 
                delete[] static_cast<Textbox*>(m_data_void_ptr); 
                break;
            case PIXMAP_ARRAY: 
                delete[] static_cast<Pixmap*>(m_data_void_ptr); 
                break;
            default: assert(false);
        }
    }
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
    m_data_void_ptr = nullptr;
    switch (type)
    {
        case CIRCLE:
            m_data_void_ptr = new Circle();
            break;
        case RECTANGLE:
            m_data_void_ptr = new Rectangle();
            break;
        case TRIANGLE:
            m_data_void_ptr = new Triangle();
            break;
        case TEXTBOX:
            m_data_void_ptr = new Textbox();
            break;
        case PIXMAP:
            m_data_void_ptr = new Pixmap();
            break;
        case ANIMATION_BLOCK:
            m_data_void_ptr = new Animation_block();
            break;
        default:
            assert(false && "Unhandled game object type in constructor");
    }

    validate();
}

Symbol::Symbol(string name, Animation_block* initial_value)
{
    m_name = name;
    m_type = ANIMATION_BLOCK;
    m_data_void_ptr = (void*)initial_value;
    m_size = UNDEFINED_SIZE; // Animation_block are not allowed
    validate();
}

Symbol::Symbol(string name, Gpl_type type, bool is_animation_parameter)
{
    m_name = name;
    m_type = type;
    m_size = UNDEFINED_SIZE;
    m_data_void_ptr = nullptr;  // Don't create object for animation parameters
    validate();
}

Gpl_type Symbol::get_base_type() const 
{

  if (m_type & ARRAY)
      return (Gpl_type) (m_type - ARRAY);
  else
      return m_type;
}

void Symbol::validate_type_and_index(Gpl_type type, int index) const
{

    // validate the type
    assert(m_type & type);

    if (is_array() && (m_type & GAME_OBJECT))
    {
        if (index == UNDEFINED_INDEX)
            return;
            

        assert(index >= 0 && index < m_size);
        return;
    }

    assert((index == UNDEFINED_INDEX && m_size == UNDEFINED_SIZE) || 
           (index >= 0 && m_size >= 1 && index < m_size));
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

void Symbol::set_game_object_value(Game_object* value) {
    assert(is_game_object() && !is_array());
    if (value == nullptr) {
        m_data_void_ptr = nullptr;
        return;
    }

    m_data_void_ptr = value;
}

Game_object* Symbol::get_game_object_value(int index) const {
    Game_object* obj = nullptr;
    if (is_array()) {
        switch(m_type) {
            case CIRCLE_ARRAY:
                obj = &(((Circle*)m_data_void_ptr)[index]);
                break;
            case RECTANGLE_ARRAY:
                obj = &(((Rectangle*)m_data_void_ptr)[index]);
                break;
            case TRIANGLE_ARRAY:
                obj = &(((Triangle*)m_data_void_ptr)[index]);
                break;
            case TEXTBOX_ARRAY:
                obj = &(((Textbox*)m_data_void_ptr)[index]);
                break;
            case PIXMAP_ARRAY:
                obj = &(((Pixmap*)m_data_void_ptr)[index]);
                break;
            default:
                assert(false && "Unknown game object array type");
        }
    } else {
        obj = static_cast<Game_object*>(m_data_void_ptr);
    }
    return obj;
}

Animation_block* Symbol::get_animation_block_value() const
{
    validate_type_and_index(ANIMATION_BLOCK, UNDEFINED_INDEX);

    assert(!is_array());

    return static_cast<Animation_block*>(m_data_void_ptr);
}


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

void Symbol::set_value(Animation_block* value)
{
    // Allow either direct animation_block variables or game object array elements
    assert((m_type == ANIMATION_BLOCK || (m_type & GAME_OBJECT)) && 
           (m_type == ANIMATION_BLOCK ? !is_array() : true));  // Only prevent arrays for direct animation blocks
    
    if (m_type == ANIMATION_BLOCK) {
        m_data_void_ptr = static_cast<void*>(value);
    } else {
        // For game objects (including array elements), set the animation_block member
        Game_object* obj = get_game_object_value();  // This already handles arrays correctly
        obj->set_animation_block(value);
    }
}

void Symbol::set_value(Game_object* value) {
    assert(is_game_object() && !is_array());
    m_data_void_ptr = value;
}

void Symbol::print(ostream &os) const
{
    if (is_array())
    {
        for (int i = 0; i < m_size; i++)
        {
            if (is_game_object()) 
            {
                Game_object* obj = get_game_object_value(i);
                if (obj)
                {
                    std::string symbol_name = m_name + "[" + std::to_string(i) + "]";
                    obj->print(symbol_name, os); 
                }
            } else {
            os << gpl_type_to_string(get_base_type()) << " " << m_name << "[" << i << "] = ";
            if (is_int())
                os << get_int_value(i);
                else if (is_double())
                    os << get_double_value(i);
                else if (is_string())
                    os << "\"" << get_string_value(i) << "\"";
            }
            os << std::endl;

        }
    }
    else
    {
        if (is_game_object())
        {
            Game_object* obj = static_cast<Game_object*>(m_data_void_ptr);
            if (obj)
                obj->print(m_name, os); 
        }
        else if (m_type == ANIMATION_BLOCK)
        {
            os << "animation_block " << m_name;
        }
        else {
            os << gpl_type_to_string(get_base_type()) << " " << m_name << " = ";
            if (is_int())
                os << get_int_value();
            else if (is_double())
                os << get_double_value();
            else if (is_string())
                os << "\"" << get_string_value() << "\"";
        }
        os << std::endl;
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
