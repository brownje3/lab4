#include <stdio.h>
    struct cache_t{
        int sets;
        int setIndexBits;
        int associativity;
        int blockBits;
        int blockSize;
        unsigned long tag[200][200];
    };

     
    int main(int argc, char * argv[]);
    int getBits(int first, int second, unsigned long source);
    void cline(int argc, char * argv[], char * fn);    
