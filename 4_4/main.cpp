#include "csv.h"

int main(){
    std::string line;
    mycsv::CsvReader csvReader;
    while(csvReader.getLine(line) != 0){
        std::cout << "line = " << line << "\n";
        for(uint32_t i = 0; i < csvReader.getNField(); ++i){
            std::cout << "field[" << i << "] = " << csvReader.getField(i) << "\n";
        }
    }
    return 0;
}