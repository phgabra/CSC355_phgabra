#include "symbol_table.h"
#include "symbol.h"
#include "gpl_assert.h"
using namespace std;

#include <vector>
#include <algorithm> // for sort algorithm

/* static */ Symbol_table *Symbol_table::m_instance = 0;

/* static */ Symbol_table * Symbol_table::instance()
{
  if (!m_instance)
    m_instance = new Symbol_table();
  return m_instance;
}

Symbol_table::Symbol_table(){}

Symbol_table::~Symbol_table()
{
  cerr << "~Symbol_table()... not implemented..." << endl;
}


bool Symbol_table::insert(Symbol *symbol)
{
    auto result = m_symbols.emplace(symbol->get_name(), symbol);
    if (!result.second)
    {
        return false;
    }
    return true;
}

Symbol *Symbol_table::lookup(string name) const
{
    auto iterator = m_symbols.find(name);
    if (iterator == m_symbols.end())
    {
        return nullptr;
    }
    else
    {
        return iterator->second;
    }
}

// comparison function for the STL sort algorithm
bool compare_symbols(Symbol *a, Symbol *b) 
{
    return a->get_name() < b->get_name();
}


void Symbol_table::print(ostream &os) const
{
  vector<Symbol *> symbols;

  // (1) add all symbols in the table into a vector.
  for (const auto &pair : m_symbols)
        symbols.push_back(pair.second);

  // (2) sort the vector.
  sort(symbols.begin(), symbols.end(), compare_symbols);

  // (3) print the elements (symbols) in the vector.
  for (const auto &symbol : symbols)
        symbol->print(os);
}
