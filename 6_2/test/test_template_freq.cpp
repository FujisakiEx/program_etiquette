#include "../template_freq.h"
#include <gtest/gtest.h>
#include <cstdio>

using namespace myfreq;

template<typename T>
class FREQ_TEST : public ::testing::Test {};

template<typename T>
struct Traits {};

template<>
struct Traits<char>{
    std::string inputString = "hello,  world\n";
};

template<>
struct Traits<uint32_t>{
    //std::string inputString = "0\n1\n1\n16\n30\n40\n50\n";
    std::string inputString = "1";
};

template<>
struct Traits<double>{
    std::string inputString = "0.0 1.0 1.0 16.0 30.3 40.4 50.5\n";
};

TEST(FREQ_TEST, Basic){
    Freq<char> freq;

    EXPECT_EQ(freq.get_count('h'), 0);
    EXPECT_EQ(freq.get_count('e'), 0);
    EXPECT_EQ(freq.get_count('l'), 0);
    EXPECT_EQ(freq.get_count('o'), 0);
    EXPECT_EQ(freq.get_count(','), 0);
    EXPECT_EQ(freq.get_count(' '), 0);
    EXPECT_EQ(freq.get_count('w'), 0);
    EXPECT_EQ(freq.get_count('r'), 0);
    EXPECT_EQ(freq.get_count('d'), 0);
    EXPECT_EQ(freq.get_count('\n'), 0);

    std::string input_string = "hello, world\n";
    FILE* inputFile = freopen("input.txt", "w", stdin);
    std::fwrite(input_string.c_str(), sizeof(char), input_string.size(), inputFile);
    std::fflush(inputFile);
    std::freopen("input.txt", "r", stdin);

    freq.freq();

    EXPECT_EQ(freq.get_count('h'), 1);
    EXPECT_EQ(freq.get_count('e'), 1);
    EXPECT_EQ(freq.get_count('l'), 3);
    EXPECT_EQ(freq.get_count('o'), 2);
    EXPECT_EQ(freq.get_count(','), 1);
    EXPECT_EQ(freq.get_count(' '), 1);
    EXPECT_EQ(freq.get_count('w'), 1);
    EXPECT_EQ(freq.get_count('r'), 1);
    EXPECT_EQ(freq.get_count('d'), 1);
    EXPECT_EQ(freq.get_count('\n'), 1);
    std::fclose(inputFile);
}

TEST(FREQ_TEST, BasicUInt){
    Freq<uint32_t> freq;

    EXPECT_EQ(freq.get_count(0), 0);
    std::string input_string = "0\n10\n20\n";
    FILE* input_file = freopen("input.txt", "w", stdin);
    std::fwrite(input_string.c_str(), sizeof(char), input_string.size(), input_file);
    std::fflush(input_file);
    std::freopen("input.txt", "r", stdin);

    freq.freq();

    EXPECT_EQ(freq.get_count(0), 1);
    std::fclose(input_file);
}

TEST(FREQ_TEST, AllAscii){
    Freq<char> freq;
    std::string input_string(128, ' ');
    for(uint16_t i = 0; i < 128; ++i){
        input_string[i] = char(i);
    }
    FILE* inputFile = freopen("input.txt", "w", stdin);
    std::fwrite(input_string.c_str(), sizeof(char), input_string.size(), inputFile);
    std::fflush(inputFile);
    std::freopen("input.txt", "r", stdin);

    freq.freq();

    for(uint16_t i = 0; i < 128; ++i){
        EXPECT_EQ(freq.get_count(char(i)), 1);
    }

    freq.reset();

    for(uint16_t i = 0; i < 128; ++i){
        EXPECT_EQ(freq.get_count(char(i)), 0);
    }

    std::fclose(inputFile);
}

TYPED_TEST_CASE_P(FREQ_TEST);

TYPED_TEST_P(FREQ_TEST, Basic){
    Freq<TypeParam> freq;
    freq.reset();
    freq.print_freq();
    EXPECT_EQ(0, freq.get_count(TypeParam()));
}

TYPED_TEST_P(FREQ_TEST, Input){
    Freq<TypeParam> freq;

    Traits<TypeParam> t;

    std::cout << t.inputString.c_str() << " " << t.inputString.size() << std::endl;

    FILE* input_file = freopen("input.txt", "w", stdin);
    std::fwrite(t.inputString.c_str(), sizeof(char), t.inputString.size(), input_file);
    std::fflush(input_file);
    std::freopen("input.txt", "r", stdin);

    EXPECT_EQ(0, freq.get_count(TypeParam(1)));
    freq.freq();
    EXPECT_EQ(2, freq.get_count(TypeParam(1)));
    EXPECT_EQ(1, freq.get_count(TypeParam(16)));
    freq.reset();
    EXPECT_EQ(0, freq.get_count(TypeParam(1)));
    EXPECT_EQ(0, freq.get_count(TypeParam(16)));

    std::fclose(input_file);
}

REGISTER_TYPED_TEST_CASE_P(FREQ_TEST, Basic, Input);

using MyTypes = ::testing::Types<double, char, uint32_t> ;
INSTANTIATE_TYPED_TEST_CASE_P(My, FREQ_TEST, MyTypes);
