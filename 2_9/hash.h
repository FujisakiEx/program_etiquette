#ifndef _H_FUJISAKI_MYHASH
#define _H_FUJISAKI_MYHASH

#include <string>
#include<iostream>
#include<vector>
#include<set>

namespace myhash{

struct Nameval {
    std::string name;
    int value;
    Nameval* next;
};

constexpr uint32_t HASH_COUNT = 1000;
constexpr uint32_t HASH_MULTIPLIER = 37;
constexpr float ALLOW_AVERAGE_LIST_LENGTH = 2;
constexpr uint32_t REMAKE_HASH_SIZE = 2;

uint32_t hash(std::string str);

// for debug
void init_hash_table();
void print_nameval(const Nameval* nameval);
Nameval* lookup(std::string name, bool create,  int value);
bool check_average_bucketsize();
void recreate_hash_table();
void print_all();
uint32_t get_recreate_count();
} // myhash

#endif //_H_FUJISAKI_MYHASH