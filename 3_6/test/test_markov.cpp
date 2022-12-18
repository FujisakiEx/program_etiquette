#include "../markov.cpp"
#include <map>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>
#include <fstream>

#include <gtest/gtest.h>

using namespace mymarkov;

class MARKOV_TEST: public ::testing::TestWithParam<const char*>{
};

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
#elif defined(problem_3_3)
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
    prefix.pop_front();
    EXPECT_EQ(prefix.front(), hash("sine"));
#elif defined(problem_3_3)
    EXPECT_EQ(prefix.front(), hash("pitch"));
    prefix.pop_front();
    EXPECT_EQ(prefix.front(), hash("sine"));
#else
    EXPECT_EQ(prefix.front(), "sine");
    prefix.pop_front();
    EXPECT_EQ(prefix.front(), "pitch");
#endif
    prefix.pop_front();

    EXPECT_EQ(prefix.size(), 0);
}

TEST_P(MARKOV_TEST, generate){
    uint32_t nwords = 20;
    Prefix prefix;
    reset();
    std::ifstream is0(GetParam());

    for(uint32_t i = 0; i < NUMBER_OF_PREFIX; ++i){
        add(prefix, NONWORD);
    }
    build(prefix, is0);
    add(prefix, NONWORD);

    generate(nwords);
    
    EXPECT_EQ(prefix.size(), NUMBER_OF_PREFIX);
}

INSTANTIATE_TEST_SUITE_P(INPUT_TEST, MARKOV_TEST, ::testing::Values("test_case0.txt", "test_case1.txt"));

TEST(MARKOV_TEST, define){
#ifdef problem_3_2
    std::cout << "ver 3_2" << std::endl;
#elif defined(problem_3_3)
    std::cout << "ver 3_3" << std::endl;
#else
    std::cout << "ver default" << std::endl;
#endif

}