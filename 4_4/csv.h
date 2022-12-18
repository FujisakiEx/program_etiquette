#ifndef _H_FUJISAKI_MYCSV
#define _H_FUJISAKI_MYCSV

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>

namespace mycsv{

class CsvReader{
public:
    CsvReader(std::istream& fin=std::cin, std::string sep = ",");
    uint32_t getLine(std::string&);
    std::string getField(uint32_t n) const;
    uint32_t getNField() const;
    std::string operator[](uint32_t i) const;
private:
    std::istream& fin;
    std::string line;
    std::vector<std::string> field;
    uint32_t n_field;
    std::string field_sep;
    uint32_t split();
    uint32_t endOfLine(char);
    uint32_t advancePlain(const std::string& line, std::string& fld, uint32_t);
    uint32_t advanceQuated(const std::string& line, std::string& fld, uint32_t);
};

} // mycsv

#endif