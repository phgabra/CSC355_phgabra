#include "symbol_table.h"
#include "symbol.h"
#include "gpl_assert.h"
using namespace std;

#include <vector>
#include <algorithm> // for sort algorithm

Symbol_table *Symbol_table::m_instance = 0;

Symbol_table * Symbol_table::instance()
{
  if (!m_instance)
    m_instance = new Symbol_table();
  return m_instance;
}

Symbol_table::Symbol_table(){}

//Destructor to get rid of the symbol table
// and clean up resources
Symbol_table::~Symbol_table()
{
  for (auto& key_value_pair : m_symbols)
  {
    //Clear up the symbol associated
    //with the key
    delete key_value_pair.second;
  }
  //Finally, remove the key-value pairs
  m_symbols.clear();
}


bool Symbol_table::insert(Symbol *symbol)
{
  //if the symbol is already in the table, return false
  string symbol_name = (*symbol).get_name();
  if(m_symbols.find(symbol_name) != m_symbols.end())
    {
        return false;
    }

    m_symbols[symbol_name] = symbol;
    return true;
}

Symbol *Symbol_table::lookup(string name) const
{
    auto iterator = m_symbols.find(name);
    if(iterator == m_symbols.end())
    {
        return nullptr;
    }
    return (*iterator).second;
}

// comparison function for the STL sort algorithm
bool compare_symbols(Symbol *a, Symbol *b) 
{
  string a_name = (*a).get_name();
  string b_name = (*b).get_name();
  return a_name < b_name;
}


void Symbol_table::print(ostream &os) const
{
  vector<Symbol*> sorted_symbols;
  for(auto iterator = m_symbols.begin(); iterator != m_symbols.end(); ++iterator)
  {
    sorted_symbols.push_back((*iterator).second);
  }
  sort(sorted_symbols.begin(), sorted_symbols.end(), compare_symbols);

  for ( auto symbol : sorted_symbols )
  {
    (*symbol).print(os);
  }

}
