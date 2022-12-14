#include "hash.h"

namespace myhash{

uint32_t recreate_table_count = 1;

std::vector<std::string> keyList(0);
std::set<uint32_t> hashSet;
Nameval **symtab = nullptr;

uint32_t hash(std::string str){
    uint32_t h = 0;
    for(uint32_t i = 0; i < str.length(); ++i){
        h = HASH_MULTIPLIER * h + str[i];
    }

    return h % (HASH_COUNT * recreate_table_count);
}


// for debug
void print_nameval(const Nameval* nameval){
    std::cout << nameval->name << " " << nameval->value << " " << nameval->next << std::endl;
}

void init_hash_table(){
    keyList.clear();
    hashSet.clear();
    uint32_t size = HASH_COUNT * recreate_table_count * ALLOW_AVERAGE_LIST_LENGTH;
    symtab = new Nameval*[size];
    for(uint32_t i = 0; i < size; ++i){
        symtab[i] = nullptr;
    }
}

Nameval* lookup(std::string name, bool create,  int value){
    if (symtab == nullptr){
        return nullptr;
    }
    uint32_t h;
    Nameval* sym;

    h = hash(name);

    for(sym = symtab[h]; sym != nullptr; sym = sym->next){
        if (name == sym->name){
            return sym;
        }
    }

    if(create){
        sym = new Nameval();
        sym->name = name;
        sym->value = value;
        sym->next = symtab[h];
        symtab[h] =sym;
        keyList.push_back(name);
        hashSet.insert(h);
    }
    if(check_average_bucketsize()){
        recreate_hash_table();
    }
    return sym;
}

bool check_average_bucketsize(){
    Nameval* sym;

    uint32_t length = 0;
    for(const auto& h : hashSet){
        for(sym = symtab[h]; sym != nullptr; sym = sym->next){
            length++;
        }
    }

    return (length * 1.0 / hashSet.size()) > ALLOW_AVERAGE_LIST_LENGTH;
}

void recreate_hash_table(){
    // list up current table
    std::vector<std::pair<std::string, int>> values;
    for(const auto& name: keyList){
        auto nameVal = lookup(name, false, 0);
        values.push_back(std::make_pair(name, nameVal->value));
    }

    // delete all elements
    for(const auto& h : hashSet){
        Nameval* sym;
        for(sym = symtab[h]; sym != nullptr; ){
            auto next = sym->next;
            delete sym;
            sym = next;
            if(sym == nullptr)
                break;
        }
    }

    // delete table
    delete[] symtab;
    recreate_table_count++;
    init_hash_table();
    for(const auto& v : values){
        lookup(v.first, true, v.second);
    }
}

void print_all(){
    Nameval* sym;

    for(const auto& name : keyList){
        uint32_t h = hash(name);

        for(sym = symtab[h]; sym != nullptr; sym = sym->next){
            print_nameval(sym);
        }
    }
}

uint32_t get_recreate_count(){
    return recreate_table_count;
}
} // myhash
