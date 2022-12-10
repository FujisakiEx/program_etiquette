#ifndef _H_FUJISAKI_MYHASH
#define _H_FUJISAKI_MYHASH

#include <string>
#include<iostream>
#include<vector>
#include<set>

namespace myhash{

struct Nameval;

constexpr uint32_t HASH_COUNT = 1000;
constexpr uint32_t MULTIPLIER = 37;
constexpr float ALLOW_AVERAGE_LIST_LENGTH = 4.0;
constexpr uint32_t REMAKE_HASH_SIZE = 2;

uint32_t hash(std::string str);

// for debug
void init_hash_table();
void printNameval(const Nameval* nameval);
Nameval* lookup(std::string name, bool create,  int value);
bool check_average_bucketsize();
void recreate_hash_table();
void printAll();
} // myhash

#endif //_H_FUJISAKI_MYHASH