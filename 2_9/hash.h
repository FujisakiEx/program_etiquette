#include <string>


struct Nameval {
    std::string name;
    int value;
    Nameval* next;
};

constexpr uint32_t HASH_COUNT = 1e6+7;
constexpr uint32_t MULTIPLIER = 31;

uint32_t hash(std::string str){
    uint32_t h = 0;
    for(uint32_t i = 0; i < str.length(); ++i){
        h = MULTIPLIER * h + str[i];
    }

    return h % HASH_COUNT;
}

Nameval *symtab[HASH_COUNT];

Nameval* lookup(std::string name, bool create,  int value){
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
    }
    return sym;
}