#ifndef _H_FUJISAKI_MYFREQ
#define _H_FUJISAKI_MYFREQ

#include <iostream>
#include <climits>

namespace myfreq{

unsigned long count[UCHAR_MAX + 1];

void freq(){
    uint32_t c;

    while((c = getchar()) != EOF){
        count[c]++;
    }
}

void print_freq(){
    for(uint32_t c = 0; c <= UCHAR_MAX; c++){
        if(count[c] != 0)
            printf("%.2x %c %lu\n", c, isprint(c) ? c : '-', count[c]);
    }
}

void reset(){
    for(uint32_t c = 0; c <= UCHAR_MAX; c++){
        count[c] = 0;
    }
}

}


#endif