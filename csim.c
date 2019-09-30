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

int main()
{
    struct cache_t cache;
    
	for(int i = 0; i < cache.sets; i++)
	{
		cache.tag[][i] = malloc(sizeof(unsigned long) * cache.sets);
	}
	
	getLines();
	
    printSummary(0, 0, 0);
    return 0;
}

int getBits(int first, int second, unsigned long source) 
{
    if(first < 0) //checks for an out of bounds error with the first parameter
    {
        printf("%s", "First bit out of bounds, please check getBits");
        return 0;
    }
    if(second > 63) //checks for an out of bounds error with the second parameter
    {
        printf("%s", "Second bit out of bounds, please check getBits");
        return 0;
    }
    
    int firstShift = 63 - second;
    int secondShift = firstShift + first;

    source = source << firstShift;
    source = source >> secondShift;
    
    return source;
}

void getLines()
{
	char line[80];
	
	fgets(line, 80, stdin);
	//sscanf(line, "% ", 
}
