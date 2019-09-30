#include "cachelab.h"
#include "csim.h"



int main()
{
    struct cache_t cache;
    
	for(int i = 0; i < setsByAssoc; i++)
	{
		cache.tag[][i] = (unsigned long int) malloc(sizeof(unsigned long int) * setsByAssoc);
	}
	
	getLines()
	
    printSummary(0, 0, 0);
    return 0;
}

int getBits(int first, int second, unsigned long source) 
{
    if(first < 0) //checks for an out of bounds error with the first parameter
    {
        std::cout << "First bit out of bounds, please check getBits";
        return;
    }
    if(second > 63) //checks for an out of bounds error with the second parameter
    {
        std::cout << "Second bit out of bounds, please check getBits";
        return;
    }
    
    int firstShift = 63 - second;
    int secondShift = firstShift + first;

    source = source << firstShift;
    source = source >> secondShift;
    
    return source;
}

void getLines()
{
	char[80] line;
	
	fgets(line, 80, stdin);
	sscanf(line, "% ", 
}
