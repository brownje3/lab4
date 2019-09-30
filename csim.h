#include <stdio.h>
    struct cache_t{
        int sets;
        int setIndexBits;
        int associativity;
        int blockBits;
        int blockSize;
        unsigned long tag[200][200];
    };

     
    int main();
    int getBits(int first, int second, unsigned long source);
        
