#ifndef _H_FUJISAKI_MYFREQ
#define _H_FUJISAKI_MYFREQ

#include <iostream>
#include <climits>
#include <map>

namespace myfreq{

template<typename T>
class Freq{

public:
    Freq(){
        reset();
    }
    void freq(){
        T c;

        while(1){
            std::cin >> c;
            if(std::cin.eof()) break;
            _count[T(c)]++;
        }
    }

    void print_freq(){
        for(auto i: _count){
            std::cout << i.first << " " << i.second << std::endl;
        }
    }

    void reset(){
        _count.clear();
    }

    uint32_t get_count(T index){
        if(_count.count(index) == 1)
            return _count[index];
        return 0;
    }
private:
    std::map<T, uint32_t> _count;
};

template<>
class Freq<char>{
public:
    Freq(){
        reset();
    }

    void freq(){
        char c;

        while((c = getchar()) != EOF){
            _count[c]++;
        }
    }

    void print_freq(){
        for(uint32_t c = 0; c <= UCHAR_MAX; c++){
            if(_count[c] != 0)
                printf("%.2x %c %lu\n", c, isprint(c) ? c : '-', _count[c]);
        }
    }

    void reset(){
        for(uint32_t c = 0; c <= UCHAR_MAX; c++){
            _count[c] = 0;
        }
    }

    uint32_t get_count(char index){
        return _count[index];
    }

    unsigned long _count[UCHAR_MAX + 1];

};

}


#endif