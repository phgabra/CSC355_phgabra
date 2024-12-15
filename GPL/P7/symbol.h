#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>

#include "gpl_type.h"
#include "gpl_assert.h"

class Symbol_table;
class Game_object;
class Animation_block;

const int UNDEFINED_INDEX = -1;
const int UNDEFINED_SIZE = -1;

class Symbol
{
  public:

    // non-array variables
    Symbol(std::string name, int initial_value);
    Symbol(std::string name, double initial_value);
    Symbol(std::string name, std::string initial_value);
    Symbol(std::string name, Animation_block* initial_value);
    // array: int, double, string, circle, rectangle, triangle, textbox, pixmap
    Symbol(std::string name, Gpl_type type, int size);
    Symbol(std::string name, Gpl_type type, bool is_animation_parameter);

    ~Symbol();

    std::string get_name() {return m_name;}

    Gpl_type get_type() const {return m_type;}

    // strip away the ARRAY bit.
    Gpl_type get_base_type() const;
    // Constructor for game_objects
    Symbol(std::string name, Gpl_type type);

    // Returns game_object value
    Game_object* get_game_object_value(int index=UNDEFINED_INDEX) const;
    void set_game_object_value(Game_object* value);
    bool is_array() const {return m_type & ARRAY;}
    bool index_within_range(int index) 
    {assert(is_array()); return 0 <= index && index < m_size;}

    // should not ask the size of a symbol if it is not an array
    int size() {assert(is_array()); return m_size;}

    bool is_int() const {return m_type & INT;}
    bool is_double() const {return m_type & DOUBLE;}
    bool is_string() const {return m_type & STRING;}
    bool is_game_object() const {return m_type & GAME_OBJECT;}
    bool is_animation_block() const {return m_type == ANIMATION_BLOCK;}
    
    void set_value(int index, int value);
    void set_value(int index, double value);
    void set_value(int index, const std::string& value);
    void set_value(int value);
    void set_value(double value);
    void set_value(Animation_block* value);
    void set_value(const std::string& value);
    void set_value(Game_object* value);
    void validate_type_and_index(Gpl_type type, int index) const;
    int get_int_value(int index = UNDEFINED_INDEX) const;
    double get_double_value(int index = UNDEFINED_INDEX) const;
    std::string get_string_value(int index = UNDEFINED_INDEX) const;
    Animation_block* get_animation_block_value() const;
    void print(std::ostream &os) const;

    void* get_data_void_ptr() { return m_data_void_ptr; }
    void set_data_void_ptr(void* data) { m_data_void_ptr = data; }

  private:
    Symbol(const Symbol&); 
    const Symbol &operator=(const Symbol&);

    void validate() const; 

    Gpl_type m_type = NO_TYPE;
    std::string m_name = "";
    void *m_data_void_ptr = NULL;
    int m_size = 0;
};

#endif // #ifndef SYMBOL_H
