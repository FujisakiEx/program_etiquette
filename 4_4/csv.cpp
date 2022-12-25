#include "csv.h"

namespace mycsv{

    CsvReader::CsvReader(std::istream& fin, std::string sep) : fin(fin), field_sep(sep){}

    uint32_t CsvReader::getLine(std::string& str){
        char c;
        for(line = ""; fin.get(c) && !endOfLine(c);){
            line += c;
        }
        split();
        str = line;

        return !fin.eof();
    }

    uint32_t CsvReader::endOfLine(char c){
        uint32_t eol;
        eol = (c == '\r' || c == '\n');

        if(c == '\r'){
            fin.get(c);
            if(!fin.eof() && c != '\n'){
                fin.putback(c);
            }
        }
        return eol;
    }

    uint32_t CsvReader::split(){
        std::string fld;

        n_field = 0;
        if(line.length() == 0) 
            return 0;

        uint32_t i = 0;
        uint32_t j = 0;
        do {
            if (i < line.length() && line[i] == '"'){
                j = advanceQuated(line, fld, ++i);
            }
            else{
                j = advancePlain(line, fld, i);
            }

            if(n_field >= field.size()){
                field.push_back(fld);
            }
            else{
                field[n_field] = fld;
            }

            n_field++;
            i = j + 1;
        } while(j < line.length());
        return n_field;
    }

    uint32_t CsvReader::advanceQuated(const std::string& s, std::string& fld, uint32_t i){
        uint32_t j = 0;
        fld = "";
        for(j = i; j < s.length(); ++j){
            if(s[j] == '"' && s[++j] != '"'){
                uint32_t k = s.find_first_of(field_sep, j);
                if(k > s.length()){
                    k = s.length();
                }

                for(k -= j; k-- > 0;){
                    fld += s[j++];
                }

                break;
            }
            fld += s[j];
        }

        return j;
    }

    uint32_t CsvReader::advancePlain(const std::string& s, std::string& fld, uint32_t i){
        uint32_t j = 0;
        j = s.find_first_of(field_sep, i);
        if(j > s.length()){
            j = s.length();
        }
        fld = std::string(s, i, j - i);
        return j;
    }

    std::string CsvReader:: getField(uint32_t n) const{
        if(n < 0 || n >= n_field){
            return "";
        }
        else{
            return field[n];
        }
    }

    uint32_t CsvReader::getNField() const {
        return n_field;
    }

    std::string CsvReader::operator[](uint32_t i) const{
        return getField(i);
    }

    bool CsvReader::operator==(const CsvReader& other) const{
        if (n_field != other.n_field) return false;
        return field == other.field;
    }

    CsvReaderIterator CsvReader::begin(){
        return CsvReaderIterator(this, 0);
    }

    CsvReaderIterator CsvReader::end(){
        return CsvReaderIterator();
    }

    CsvReaderIterator::CsvReaderIterator(){
        _csvReader = nullptr;
        _index = CsvReader::MAX_FIELD_SIZE;
    }

    CsvReaderIterator::CsvReaderIterator(CsvReader* csvReader, uint32_t index){
        _csvReader = csvReader;
        _index = (index < CsvReader::MAX_FIELD_SIZE ? index : CsvReader::MAX_FIELD_SIZE);
    }

    std::string CsvReaderIterator::operator*() const {
        return (_index != CsvReader::MAX_FIELD_SIZE ? (*_csvReader)[_index] : "");
    }

    CsvReaderIterator& CsvReaderIterator::operator++(){
        _index++;
        if(_index > _csvReader->n_field){
            _index = CsvReader::MAX_FIELD_SIZE;
        }
        return *this;
    }

    CsvReaderIterator CsvReaderIterator::operator++(int){
        auto result = *this;
        _index++;
        if(_index > _csvReader->n_field){
            _index = CsvReader::MAX_FIELD_SIZE;
        }
        return result;
    }

    bool CsvReaderIterator::operator==(const CsvReaderIterator& it) const {
        return this->_index != it._index || this->_csvReader != it._csvReader;
    }


} // namespace mycsv