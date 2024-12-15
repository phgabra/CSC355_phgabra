#include "variable.h"
#include "symbol.h"
#include "expression.h"
#include "gpl_type.h"
#include "gpl_assert.h"
#include "error.h"
#include "game_object.h"
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

Variable::Variable(Symbol *symbol, std::string *field, Expression *expression)
{
    m_symbol = symbol;
    m_expression = expression;
    m_is_valid = false;
    m_type = NO_TYPE;

    if (!symbol) {
        Error::error(Error::UNDECLARED_MEMBER, "Unknown Symbol", *field);
        return;
    }

    m_field = field ? new std::string(*field) : nullptr;

    if (!m_field) {
        return;
    }

    try {
        Game_object *obj = nullptr;

        // Get the game object value based on whether an expression is present
        if (m_expression) {
            int index = 0;
            obj = m_symbol->get_game_object_value(index);
        } else {
            obj = m_symbol->get_game_object_value();
        }

        // Check if the object is valid
        if (!obj) {
            Error::error(Error::OPERAND_MUST_BE_A_GAME_OBJECT, m_symbol->get_name(), *m_field);
            return;
        }

        // Determine the field type of the game object
        Gpl_type field_type;
        Status status = obj->get_member_variable_type(*m_field, field_type);

        if (status == OK) {
            m_type = field_type;
            m_is_valid = true;
        } else {
            Error::error(Error::UNDECLARED_MEMBER, m_symbol->get_name(), *m_field);
        }
    } catch (...) {
        // Handle any unexpected errors gracefully
        m_is_valid = false;
        m_type = NO_TYPE;
    }
}

Variable::Variable()
{
    m_symbol = nullptr;
    m_expression = nullptr;
    m_type = INT;  // Default type (can be anything)
    m_is_valid = false;  // Mark as invalid
}

std::string Variable::get_name() const
{
  string name = m_symbol->get_name();
  // Add [] at the end of an array name
  if (m_expression)
  {
    name += "[]";
  }
  if (m_field) {
    name += "." + *m_field;
  }
  return name;
}

int Variable::get_int_value() const
{
    
    // member variable access first
    if (m_field)
    {
        Game_object *cur_game_object;
        int array_index = 0;
        
        if (m_expression)
        {
            array_index = m_expression->eval_int();
            
            if (!m_symbol->index_within_range(array_index)) {
                Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, 
                            m_symbol->get_name(), 
                            std::to_string(array_index));
                array_index = 0;
            }
        }
        
        cur_game_object = m_expression ? 
                         m_symbol->get_game_object_value(array_index) :
                         m_symbol->get_game_object_value();


        if (!cur_game_object) {
            return 0;
        }

        int value;
        Status status = cur_game_object->get_member_variable(*m_field, value);
        
        if (status != OK) {
            return 0;
        }
        return value;
    }
    
    // Handle regular variable access
    if (m_expression)
    {
        int index = m_expression->eval_int();
        if (!m_symbol->index_within_range(index)) {
            Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, 
                        m_symbol->get_name(), 
                        std::to_string(index));
            index = 0;
        }
        return m_symbol->get_int_value(index);
    }
    
    return m_symbol->get_int_value();
}

double Variable::get_double_value() const
{
    if (!m_field)
    {
        if (m_expression)
        {
            int index = eval_index_with_error_checking();
            return m_symbol->get_double_value(index);
        }
        return m_symbol->get_double_value();
    }
    else
    {
        Game_object *cur_game_object;

        if (m_expression)
        {
            cur_game_object = m_symbol->get_game_object_value(eval_index_with_error_checking());
        }
        else
        {
            cur_game_object = m_symbol->get_game_object_value();
        }

        double value;
        Status status = cur_game_object->get_member_variable(*m_field, value);
        assert(status == OK);
        return value;
    }
}

std::string Variable::get_string_value() const
{
    if (!m_field)
    {
        if (m_expression)
        {
            int index = eval_index_with_error_checking();
            return m_symbol->get_string_value(index);
        }
        return m_symbol->get_string_value();
    }
    else
    {
        Game_object *cur_game_object;

        if (m_expression)
        {
            cur_game_object = m_symbol->get_game_object_value(eval_index_with_error_checking());
        }
        else
        {
            cur_game_object = m_symbol->get_game_object_value();
        }

        std::string value;
        Status status = cur_game_object->get_member_variable(*m_field, value);
        assert(status == OK);
        return value;
    }
}

Animation_block* Variable::get_animation_block_value()
{
    if (has_field()) {
        // Handle member variable case
        Game_object* obj = m_symbol->get_game_object_value();
        Animation_block* value;
        Status status = obj->get_member_variable(*m_field, value);
        assert(status == OK);
        return value;
    }
    else {
        // Handle direct animation block case
        assert(m_symbol->get_type() == ANIMATION_BLOCK);
        return m_symbol->get_animation_block_value();
    }
}

void Variable::set(int value)
{
    if (m_field)  // If this is a member variable access
    {
        Game_object* obj = m_expression ? 
            m_symbol->get_game_object_value(eval_index_with_error_checking()) :
            m_symbol->get_game_object_value();
            
        if (obj)
        {
            Status status = obj->set_member_variable(*m_field, value);
            assert(status == OK);
        }
    }
    else if (m_expression)  // If this is an array access
    {
        int index = eval_index_with_error_checking();
        m_symbol->set_value(index, value);
    }
    else  // Regular variable
    {
        m_symbol->set_value(value);
    }
}

void Variable::set(double value)
{
    if (m_field)  // If this is a member variable access
    {
        Game_object* obj = m_expression ? 
            m_symbol->get_game_object_value(eval_index_with_error_checking()) :
            m_symbol->get_game_object_value();
            
        if (obj)
        {
            Status status = obj->set_member_variable(*m_field, value);
            assert(status == OK);
        }
    }
    else if (m_expression)  // If this is an array access
    {
        int index = eval_index_with_error_checking();
        m_symbol->set_value(index, value);
    }
    else  // Regular variable
    {
        m_symbol->set_value(value);
    }
}
void Variable::set(string value)
{
    if (m_field)  // If this is a member variable access
    {
        Game_object* obj = m_expression ? 
            m_symbol->get_game_object_value(eval_index_with_error_checking()) :
            m_symbol->get_game_object_value();
            
        if (obj)
        {
            Status status = obj->set_member_variable(*m_field, value);
            assert(status == OK);
        }
        return;
    }
    if (m_expression && m_expression != nullptr)
    {
        int index = eval_index_with_error_checking();
        m_symbol->set_value(index, value);
    }
    else
    {
        m_symbol->set_value(value);
    }
}

int Variable::near_handler(Variable* other)
{
    Game_object* this_obj = m_expression ? 
        m_symbol->get_game_object_value(eval_index_with_error_checking()) :
        m_symbol->get_game_object_value();

    Game_object* other_obj = other->m_expression ? 
        other->m_symbol->get_game_object_value(other->eval_index_with_error_checking()) :
        other->m_symbol->get_game_object_value();

    return this_obj->near(other_obj);
}

int Variable::touches_handler(Variable* other)
{
    Game_object* this_obj = m_expression ? 
        m_symbol->get_game_object_value(eval_index_with_error_checking()) :
        m_symbol->get_game_object_value();

    Game_object* other_obj = other->m_expression ? 
        other->m_symbol->get_game_object_value(other->eval_index_with_error_checking()) :
        other->m_symbol->get_game_object_value();

    return this_obj->touches(other_obj);
}

void Variable::set(Animation_block* value)
{
    assert(m_type == ANIMATION_BLOCK);
    m_symbol->set_value(value);
}

int Variable::eval_index_with_error_checking() const
{
    // safety checks
    if (!m_symbol) {
        return 0;
    }

    if (!m_expression) {
        return 0;
    }

    try {
        int index = m_expression->eval_int();

        if (m_symbol->index_within_range(index)) {
            return index;
        } else {
            Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, 
                        m_symbol->get_name(), 
                        std::to_string(index));
            return 0;
        }
    } catch (...) {
        return 0;
    }
}

int Variable::get_base_int_value() const
{
    if (!m_symbol) return 0;
    
    if (m_field)
    {
        if(m_symbol->is_array()) {
            int index = eval_index_with_error_checking();
            Game_object *obj = m_symbol->get_game_object_value(index);
            if (!obj) return 0;
            int value;
            Status status = obj->get_member_variable(*m_field, value);
            if (status != OK) return 0;
            return value;
        }

        Game_object *obj = m_symbol->get_game_object_value();
        if (!obj) return 0;
        
        int value;
        Status status = obj->get_member_variable(*m_field, value);
        if (status != OK) return 0;
        return value;
    }

    // Add handling for array access
    if (m_expression)
    {
        int index = eval_index_with_error_checking();
        return m_symbol->get_int_value(index);
    }

    return m_symbol->get_int_value();
}

Gpl_type Variable::get_base_game_object_type() const
{
    // If this is a member variable
    if (m_field)
    {
        Game_object *obj = m_symbol->get_game_object_value();
        if (!obj) return NO_TYPE;
        return obj->get_type();
    }
    
    // If this is a game object variable
    if (m_symbol && (m_symbol->get_type() & GAME_OBJECT))
    {
        return m_symbol->get_type();
    }
    
    return NO_TYPE;
}
