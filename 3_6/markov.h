#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>

namespace mymarkov{

using Prefix = std::deque<std::string>;

const uint32_t NUMBER_OF_PREFIX = 2;
const uint32_t NUMBER_OF_HASH = 4093;
const std::string NONWORD = "\n";

void reset();
void add(Prefix&, const std::string&);
void build(Prefix&, std::istream&);
void generate(uint32_t);

} // mymarkov