#ifndef _H_FUJISAKI_MYMARKOV
#define _H_FUJISAKI_MYMARKOV

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>

namespace mymarkov{

#define problem_3_2

#ifdef problem_3_2
using Prefix = std::deque<uint32_t>;
#else
using Prefix = std::deque<std::string>;
#endif

const uint32_t NUMBER_OF_PREFIX = 2;
const uint32_t NUMBER_OF_HASH = 4093;
const std::string NONWORD = "\n";

void reset();
void add(Prefix&, const std::string&);
void build(Prefix&, std::istream&);
void generate(uint32_t);

} // mymarkov
#endif //_H_FUJISAKI_MYMARKOV