#include "markov.h"

using namespace mymarkov;

int main(){
    uint32_t nwords = 20;
    Prefix prefix;
    std::string url;
    std:: cin >> url;

    for(uint32_t i = 0; i < NUMBER_OF_PREFIX; ++i){
        add(prefix, NONWORD);
    }
    build(prefix, std::cin);
    add(prefix, NONWORD);

    generate(nwords);

    return 0;
}