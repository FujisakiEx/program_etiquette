#include "../csv.cpp"

#include <fstream>
#include <gtest/gtest.h>

using namespace mycsv;

std::string inputs[2] = {"\"LU\", 86. 25,\" 11/ 4/ 1998\",\" 2: 19 PM\",+ 4. 0625", "hello world orb,10 end torn ,, set  two-space"};

struct CsvTestParam{
    std::string fileName;
    std::string sep;
    CsvTestParam(const std::string fileName, const std::string& sep=","): fileName(fileName), sep(sep){}
};

class CSV_TEST: public ::testing::TestWithParam<CsvTestParam>{};

TEST_P(CSV_TEST, basic){
    const auto p = GetParam();
    std::ifstream ifs(p.fileName);
    CsvReader csvReader(ifs, p.sep);
    std::string line;
    uint32_t i = 0;
    while(csvReader.getLine(line) != 0){
        EXPECT_EQ(line, inputs[i]);
        ++i;
    }
}

TEST(CSV_TEST, case_commma){
    std::ifstream ifs("test_case1.csv");
    CsvReader csvReader(ifs, ",");
    std::string line;
    csvReader.getLine(line);
    EXPECT_EQ(5, csvReader.getNField());
    EXPECT_EQ("LU", csvReader[0]);
    EXPECT_EQ(" 86. 25", csvReader[1]);
    EXPECT_EQ(" 11/ 4/ 1998", csvReader[2]);
    EXPECT_EQ(" 2: 19 PM", csvReader[3]);
    EXPECT_EQ("+ 4. 0625", csvReader[4]);
    csvReader.getLine(line);
    EXPECT_EQ(4, csvReader.getNField());
    EXPECT_EQ("hello world orb", csvReader[0]);
    EXPECT_EQ("10 end torn ", csvReader[1]);
    EXPECT_EQ("", csvReader[2]);
    EXPECT_EQ(" set  two-space", csvReader[3]);
}

TEST(CSV_TEST, case_space){
    std::ifstream ifs("test_case1.csv");
    CsvReader csvReader(ifs, " ");
    std::string line;
    csvReader.getLine(line);
    EXPECT_EQ(11, csvReader.getNField());
    EXPECT_EQ("LU,", csvReader[0]);
    EXPECT_EQ("86.", csvReader[1]);
    EXPECT_EQ("25,\"", csvReader[2]);
    EXPECT_EQ("11/", csvReader[3]);
    EXPECT_EQ("4/", csvReader[4]);
    EXPECT_EQ("1998\",\"", csvReader[5]);
    EXPECT_EQ("2:", csvReader[6]);
    EXPECT_EQ("19", csvReader[7]);
    EXPECT_EQ("PM\",+", csvReader[8]);
    EXPECT_EQ("4.", csvReader[9]);
    EXPECT_EQ("0625", csvReader[10]);
    csvReader.getLine(line);
    EXPECT_EQ(9, csvReader.getNField());
    EXPECT_EQ("hello", csvReader[0]);
    EXPECT_EQ("world", csvReader[1]);
    EXPECT_EQ("orb,10", csvReader[2]);
    EXPECT_EQ("end", csvReader[3]);
    EXPECT_EQ("torn", csvReader[4]);
    EXPECT_EQ(",,", csvReader[5]);
    EXPECT_EQ("set", csvReader[6]);
    EXPECT_EQ("", csvReader[7]);
    EXPECT_EQ("two-space", csvReader[8]);
}

INSTANTIATE_TEST_SUITE_P(INPUT_TEST, CSV_TEST, ::testing::Values(
    CsvTestParam("test_case0.csv", ","),
    CsvTestParam("test_case0.csv", " "),
    CsvTestParam("test_case1.csv", ","),
    CsvTestParam("test_case1.csv", " ")
    ));