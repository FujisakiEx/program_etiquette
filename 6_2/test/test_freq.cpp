#include "../freq.h"
#include <gtest/gtest.h>
#include <cstdio>

using namespace myfreq;

struct FreqTestParam{
    std::string inputString;
    FreqTestParam(std::string input): inputString(input){}
};

class FREQ_TEST : public ::testing::TestWithParam<FreqTestParam> {

public:
    FREQ_TEST() {
        reset();
        const auto p = GetParam();
        FILE* input_file = freopen("input.txt", "w", stdin);
        std::fwrite(p.inputString.c_str(), sizeof(char), p.inputString.size(), input_file);
        std::fflush(input_file);
        std::freopen("input.txt", "r", stdin);
    }
};

TEST(FREQ_TEST, Basic){
    reset();
    std::string input_string = "hello, world\n";
    FILE* inputFile = freopen("input.txt", "w", stdin);
    std::fwrite(input_string.c_str(), sizeof(char), input_string.size(), inputFile);
    std::fflush(inputFile);
    std::freopen("input.txt", "r", stdin);

    freq();

    EXPECT_EQ(count['h'], 1);
    EXPECT_EQ(count['e'], 1);
    EXPECT_EQ(count['l'], 3);
    EXPECT_EQ(count['o'], 2);
    EXPECT_EQ(count[','], 1);
    EXPECT_EQ(count[' '], 1);
    EXPECT_EQ(count['w'], 1);
    EXPECT_EQ(count['r'], 1);
    EXPECT_EQ(count['d'], 1);
    EXPECT_EQ(count['\n'], 1);
}

TEST(FREQ_TEST, AllAscii){
    reset();
    std::string input_string(128, ' ');
    for(uint16_t i = 0; i < 128; ++i){
        input_string[i] = char(i);
    }
    FILE* inputFile = freopen("input.txt", "w", stdin);
    std::fwrite(input_string.c_str(), sizeof(char), input_string.size(), inputFile);
    std::fflush(inputFile);
    std::freopen("input.txt", "r", stdin);

    freq();

    for(uint16_t i = 0; i < 128; ++i){
        EXPECT_EQ(count[char(i)], 1);
    }

}

TEST_P(FREQ_TEST, Basic_P){
    freq();
}

INSTANTIATE_TEST_SUITE_P(INPUT_TEST, FREQ_TEST, ::testing::Values(
    FreqTestParam(""),
    FreqTestParam("\n"),
    FreqTestParam("\r"),
    FreqTestParam("\t"),
    FreqTestParam(" \n"),
    FreqTestParam(" \r"),
    FreqTestParam(" \t"),
    FreqTestParam("\n "),
    FreqTestParam("\r "),
    FreqTestParam("\t "),
    FreqTestParam("\\n"),
    FreqTestParam("\\r"),
    FreqTestParam("\\t"),
    FreqTestParam("hello, world")
));
