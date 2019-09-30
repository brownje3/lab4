#include <stdio.h>
#include <stdlib.h>
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
	
	char line[80];
    char * filename = "";
    int hit_count, miss_count, eviction_count;

    hit_count = 0;
    miss_count = 0;
    eviction_count = 0;

    cline(argc, argv, filename);
	
	fgets(line, 80, stdin);
    //sscanf(line, "%x %lu", &cache);
    
	for(int i = 0; i < cache.sets; i++)
	{
		for(int j = 0; j < cache.associativity; j++)
		{
			cache.tag[i][j] = (unsigned long int) malloc(sizeof(unsigned long int) * cache.sets);
		}
	}
	
	
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

void cline(int argc, char * argv[], char * fn)
{
   if (argc != 4 || argc != 5) {
        printf("%s", argv[0]);
        printf("check\n");
        exit(1);
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

