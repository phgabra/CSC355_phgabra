#include "symbol_table.h"
#include "symbol.h"
#include "gpl_assert.h"
using namespace std;

#include <vector>
#include <algorithm> // for sort algorithm
#include <set>

Symbol_table *Symbol_table::m_instance = 0;

Symbol_table * Symbol_table::instance()
{
  if (!m_instance)
  {  
    m_instance = new Symbol_table();
    m_instance->initialize_reserved_variables();
  }
  
  return m_instance;
}

Symbol_table::Symbol_table(){
    reserved_variables = {"window_x", "window_y", "window_w", "window_h"};
}


void Symbol_table::initialize_reserved_variables()
{
    // Default values for reserved variables
    insert(new Symbol("window_x", 0)); 
    insert(new Symbol("window_y", 0));
    insert(new Symbol("window_w", 800));
    insert(new Symbol("window_h", 600)); 
}

//Destructor to get rid of the symbol table
// and clean up resources
Symbol_table::~Symbol_table()
{
  for (auto& key_value_pair : m_symbols)
  {

    delete key_value_pair.second;
  }
  //remove the key-value pairs
  m_symbols.clear();
}


bool Symbol_table::insert(Symbol* symbol)
{
    string symbol_name = symbol->get_name();
    if(is_reserved_variable(symbol_name) && m_symbols.find(symbol_name) != m_symbols.end())
    {
        Symbol* symbol_in_table = lookup(symbol_name);
        // symbol_in_table->set_value(symbol->get_int_value());
        symbol_in_table->set_data_void_ptr(symbol->get_data_void_ptr());
        reserved_variables.erase(symbol_name);
        return true;
    }
    if (m_symbols.find(symbol_name) != m_symbols.end())
    {
        return false;
    }

    m_symbols[symbol_name] = symbol;
    return true;
}

Symbol* Symbol_table::lookup(string name) const
{
    auto iterator = m_symbols.find(name);
    if (iterator == m_symbols.end())
    {
        if (is_reserved_variable(name))
        {
            std::cerr << "Error: Reserved variable not initialized: " << name << std::endl;
        }
        return nullptr;
    }
    return iterator->second;
}

bool Symbol_table::is_reserved_variable(const std::string& name) const
{
    return reserved_variables.find(name) != reserved_variables.end();
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

    for (auto iterator = m_symbols.begin(); iterator != m_symbols.end(); ++iterator)
    {
        if (!is_reserved_variable(iterator->first)) // skip reserved variables
        {
            sorted_symbols.push_back(iterator->second);
        }
    }

    // Sort the remaining symbols alphabetically by name
    sort(sorted_symbols.begin(), sorted_symbols.end(), compare_symbols);

    // Print the non-reserved symbols
    for (auto symbol : sorted_symbols)
    {
        symbol->print(os);
    }
}
