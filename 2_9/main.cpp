#include "hash.h"

using namespace myhash;

int main(){
    init_hash_table();
    auto sym0 = lookup("hello", true, 10);
    auto sym1 = lookup("hellohello", true, 10);
    auto sym2 = lookup("hello", true, 12);

    printAll();
}