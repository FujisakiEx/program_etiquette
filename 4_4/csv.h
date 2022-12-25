#ifndef _H_FUJISAKI_MYCSV
#define _H_FUJISAKI_MYCSV

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <iterator>
#include <compare>

namespace mycsv{

class CsvReaderIterator;

class CsvReader{
friend CsvReaderIterator;
using iterator = CsvReaderIterator;
public:
    CsvReader(std::istream& fin=std::cin, std::string sep = ",");
    uint32_t getLine(std::string&);
    std::string getField(uint32_t n) const;
    uint32_t getNField() const;
    std::string operator[](uint32_t i) const;
    bool operator==(const CsvReader&) const;
    iterator begin();
    iterator end();
    static const uint32_t MAX_FIELD_SIZE = 1000;
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

class CsvReaderIterator : public std::iterator<std::forward_iterator_tag, int>{
friend CsvReader;
private:
    CsvReaderIterator();
    CsvReaderIterator(CsvReader*, uint32_t);
    CsvReaderIterator(const CsvReaderIterator&) = default;

    uint32_t _index;
    CsvReader* _csvReader;
public:
    CsvReaderIterator& operator++();
    CsvReaderIterator operator++(int);
    std::string operator*() const;
    std::string operator->() const;
    bool operator==(const CsvReaderIterator&) const;
};

} // mycsv

#endif