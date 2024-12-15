// updated 2/14/2016

#include <vector>
#include "animation_block.h"
#include "game_object.h"
#include "gpl_assert.h"
#include "symbol.h"
using namespace std;

void Animation_block::initialize(Symbol *parameter_symbol, string name)
{
  m_name = name;
  // during error recovery a NULL parameter_symbol can be passed to Animation_block()
  if (parameter_symbol)
    assert(parameter_symbol->is_game_object());
  m_parameter_symbol = parameter_symbol;

}

void Animation_block::execute(Game_object *argument) {
    static bool executing = false;
    if (executing) return;
    executing = true;

    if (m_parameter_symbol) {
        Game_object* original = m_parameter_symbol->get_game_object_value();
        // std::cout << "\n=== Before execution ===" << std::endl;
        // argument->debug_print();
        // std::cout << "\n=== Original ===" << std::endl;
        // original->debug_print();
        
        m_parameter_symbol->set_game_object_value(argument);
        Statement_block::execute();
        
        // std::cout << "\n=== After execution ===" << std::endl;
        // argument->debug_print();
        // std::cout << "\n=== Original ===" << std::endl;
        // original->debug_print();
        
        m_parameter_symbol->set_game_object_value(original);
    } else {
        Statement_block::execute();
    }

    executing = false;
}

Animation_block::Animation_block(const std::string &name, Symbol *parameter)
{
    initialize(parameter, name);
}