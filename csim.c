#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cachelab.h"
#include "csim.h"


/**
 *  
 *  James Brown, Connor Hamilton
 *
 *  brownje3, hamiltonc
 *  
 */

int main(int argc, char * argv[])
{
    struct cache_t cache;	
    //bool verbose = false;
    char line[80];
    //char address[15];
    char filename[80]; //added an address to be read
    int hit_count, miss_count, eviction_count;

    hit_count = 0;
    miss_count = 0;
    eviction_count = 0;

    cline(argc, argv, filename, &cache);
	
	
	fgets(line, 80, stdin);
    //sscanf(line, "%x %lu", &address, &cache, );
    
	/**for(int i = 0; i < cache.sets; i++)
	{
		for(int j = 0; j < cache.associativity; j++)
		{
			cache.tag[i][j] = (unsigned long int) malloc(sizeof(unsigned long int) * cache.sets);
		}
	}*/
	
	
    //checks the first char of the line for 'I'
    if(line[0] == 'I'){}
    else //if the first character isn't 'I'
    {
	    
    }
	
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

void cline(int argc, char * argv[], char * fn, struct cache_t * cache)
{
   int cap = 0;

   for(int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-v", 2) == 0){
            cap++;
        }
        else if (strncmp(argv[i], "-h", 2) == 0) {
            printHelp();    
        }
        else if (strncmp(argv[i], "-s", 2) == 0) {
            cap++;
        }
        else if (strncmp(argv[i], "-E", 2) == 0) {
            cap++;
        }
        else if (strncmp(argv[i], "-b", 2) == 0) {
            cap++;
        }
        else if (strncmp(argv[i], "-t", 2) == 0) {
            cap++;
        }

        if (cap < 4) {printHelp();}
   }


   exit(1);
}

int getBits(int first, int second, unsigned long source) 
{
    if(first < 0 || first > second) //checks for an out of bounds error with the first parameter
    {
        printf("Error in first bit of getBits, doesn't meet bounds");
        exit(EXIT_FAILURE);
    }
    else if(second > 63 || second < first) //checks for an out of bounds error with the second parameter
    {
        printf("Second bit out of bounds, please check getBits");
        exit(EXIT_FAILURE);
    }
    
    int firstShift = 63 - second;
    int secondShift = firstShift + first;

    source = source << firstShift;
    source = source >> secondShift;
    
    return source;
}

void printHelp(){
        
    printf("csim: Missing required command line argument \
        Usage: ./csim [-hv -s <num> -E <num> -b <num> -t <file> \
        Options \
          -h         Print this help message. \
          -v         Optional verbose flag. \
          -s <num>   Number of set index bits.\
          -E <num>   Number of lines per set.\
          -b <num>   Number of block offset bits.\
          -t <file>  Trace file.\
\
        Examples:\
        linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\
        linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace");

    exit(1);
}

