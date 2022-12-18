#include "../markov.cpp"
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
#ifdef problem_3_2
        EXPECT_EQ(prefix.front(), hash(NONWORD));
#else
        EXPECT_EQ(prefix.front(), NONWORD);
#endif
        prefix.pop_front();
    }

}

TEST(MARKOV_TEST, build){
    Prefix prefix;
    reset();
    std::string s;

    std::ifstream is0("test_case0.txt");

    build(prefix, is0);
#ifdef problem_3_2
    EXPECT_EQ(prefix.front(), hash("pitch"));
#else
    EXPECT_EQ(prefix.front(), "pitch");
#endif
    prefix.pop_front();
#ifdef problem_3_2
    EXPECT_EQ(prefix.front(), hash("sine"));
#else
    EXPECT_EQ(prefix.front(), "sine");
#endif
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

TEST(MARKOV_TEST, define){
#ifdef problem_3_2
    std::cout << "ver 3_2" << std::endl;
#else
    std::cout << "ver default" << std::endl;
#endif

}