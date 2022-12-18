#include "markov.h"

using namespace mymarkov;

int main(){
    uint32_t nwords = 20;
    Prefix prefix;
    std::string url;
    std:: cin >> url;

#ifndef problem_3_3
    for(uint32_t i = 0; i < NUMBER_OF_PREFIX; ++i){
        add(prefix, NONWORD);
    }
#endif
    build(prefix, std::cin);
#ifndef problem_3_3
    add(prefix, NONWORD);
#endif

    generate(nwords);

    return 0;
}