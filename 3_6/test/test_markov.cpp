#include "../markov.h"
#include <map>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>
#include <fstream>

#include <gtest/gtest.h>

using namespace mymarkov;

TEST(MARKOV_TEST, add){
    Prefix prefix;
    reset();

    for(uint32_t i = 0; i < NUMBER_OF_PREFIX; ++i){
        add(prefix, NONWORD);
    }

    EXPECT_EQ(prefix.size(), NUMBER_OF_PREFIX);

    for(uint32_t i = 0; i < NUMBER_OF_PREFIX; ++i){
        EXPECT_EQ(prefix.front(), NONWORD);
        prefix.pop_front();
    }

}

TEST(MARKOV_TEST, build){
    Prefix prefix;
    reset();
    std::string s;

    std::ifstream is0("test_case0.txt");

    build(prefix, is0);
    EXPECT_EQ(prefix.front(), "pitch");
    prefix.pop_front();
    EXPECT_EQ(prefix.front(), "sine");
    prefix.pop_front();

    EXPECT_EQ(prefix.size(), 0);
}

TEST(MARKOV_TEST, generate){
    uint32_t nwords = 20;
    Prefix prefix;
    reset();
    std::ifstream is0("test_case0.txt");

    for(uint32_t i = 0; i < NUMBER_OF_PREFIX; ++i){
        add(prefix, NONWORD);
    }
    build(prefix, is0);
    add(prefix, NONWORD);

    generate(nwords);
    
    EXPECT_EQ(prefix.size(), NUMBER_OF_PREFIX);

}