#include "markov.h"

namespace mymarkov{

std::map<Prefix, std::vector<std::string>> stateTab;

void build(Prefix& prefix, std::istream& in){
    std::string buf;
    while(in >> buf){
        add(prefix, buf);
    }
}

void add(Prefix& prefix, const std::string& s){
    if (prefix.size() == NUMBER_OF_PREFIX){
        stateTab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

void generate(uint32_t number_of_words){
    Prefix prefix;
    for(uint32_t i = 0; i < NUMBER_OF_PREFIX; ++i){
        add(prefix, NONWORD);
    }
    for(uint32_t i = 0; i < number_of_words; ++i){
        std::vector<std::string>& suf = stateTab[prefix];
        const std::string& w = suf[rand() % suf.size()];
        if(w == NONWORD)
            break;
        
        std::cout << w << "\n";
        prefix.pop_front();
        prefix.push_back(w);
    }
    std::cout << std::endl;
}

}