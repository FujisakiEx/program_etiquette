#include "markov.h"

namespace mymarkov{

std::map<Prefix, std::vector<std::string>> stateTab;

constexpr uint32_t HASH_COUNT = 1000;
constexpr uint32_t HASH_MULTIPLIER = 37;
uint32_t hash(std::string str){
    uint32_t h = 0;
    for(uint32_t i = 0; i < str.length(); ++i){
        h = HASH_MULTIPLIER * h + str[i];
    }

    return h % HASH_COUNT;
}

void reset(){
    stateTab.clear();
}

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
#ifdef problem_3_2
    prefix.push_back(hash(s));
#else
    prefix.push_back(s);
#endif
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
#ifdef problem_3_2
        prefix.push_back(hash(w));
#else
        prefix.push_back(w);
#endif
    }
    std::cout << std::endl;
}

}