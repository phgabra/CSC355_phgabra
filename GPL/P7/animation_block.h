// updated 2/14/2016

/*
  An Animation_block is a Statement_block with:
    a parameter symbol pointer (m_parameter_symbol)
    a name (m_name)
    a flag to indicate if the body exists 
        (forward + animation block -vs- forward w/o animation block)
 
  When an animation is executed, it needs to know both the formal and
  the actual parameters.  At parse time the formal parameter is known and
  is passed to Animation_block::initialize().

  At execution, the actual parameter is known and is passed to execute()

  p6 & p7:  can use this file (you do not have to change it) 

  p8: must (1) implement flag to indicate if body exists 
                  will need a set and get functions
           (2) write the body of Animation_block::execute()
*/

#ifndef ANIMATION_BLOCK_H
#define ANIMATION_BLOCK_H

#include <string>

#include "statement_block.h"
class Symbol;
class Game_object;

class Animation_block : public Statement_block
{
  public:
    Animation_block() {}; // default constructor
    Animation_block(const Animation_block &); // copy constructor
    Animation_block(const std::string &name, Symbol *parameter); // Add this constructor

    void initialize(Symbol *parameter_symbol, std::string name);

    void execute(Game_object *argument);

    Symbol *get_parameter_symbol() {return m_parameter_symbol;}
    std::string name() {return m_name;}
    bool complete() const { return m_has_body; }
    void mark_complete() { m_has_body = true; }

  private:

    Symbol *m_parameter_symbol = NULL;
    std::string m_name = "you forgot to call initialize() on this Animation_block";
    bool m_has_body = false;
    
    const Animation_block &operator=(const Animation_block &);
};

#endif // #ifndef ANIMATION_BLOCK_H
