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


int digitNum(unsigned long number);

int main(int argc, char * argv[])
{
    struct cache_t cache;	
    bool verbose = false;
    char line[80];
    char instruction;
    int size;//, setNum, associativity;
    unsigned long address;
    char filename[80]; //added an address to be read
    int hit_count, miss_count, eviction_count;
    bool hit, miss, evic;//keeps track as to whether a hit, miss, or eviction is needed
    FILE *trace;
    


    hit_count = 0;
    miss_count = 0;
    eviction_count = 0;

    verbose = cline(argc, argv, filename, &cache);
    
    trace = fopen(filename, "r");
    //checks to see if the file has been found
    if(trace == NULL)
    {
        printf("No file found");
        exit(0);
    }
    

    while(fgets(line, 80, trace) != NULL)
    {
        sscanf(line, " %c %lu,%d", &instruction, &address, &size);
        
        if (verbose) {
            printf("%c %lu,%d ", instruction, address, size);
        }

        
        //checks for errors in the instruction
        if(!strcmp(&instruction, "I") || !strcmp(&instruction, "M") 
            || !strcmp(&instruction, "L") || !strcmp(&instruction, "S"))
        {
            printf("Error in instruction");
            exit(0);
        }
        
        //sets the boolean values as 0 at the beginning of each loop
        hit = miss = evic = 0;

        //gets the tag from the address
        //int tagLimit = 64 - (cache.setIndexBits - cache.blockBits);
        //unsigned long tag = getBits(0, tagLimit, address);
        
        //places the tag into the cache
        //cache.tag[setNum][associativity -1] = tag;
       
        //update the LRU here
        //still need to update the booleans for the switch

        //switch that handles the various counts
        switch(instruction)
        {
            case 'M':
                    if(hit)
                    {
                        hit_count = hit_count + 2;
                        if(verbose)
                        {
                            printf("hit hit \n");
                        }
                    }
                    else if(miss)
                    {
                        hit_count++;
                        miss_count++;
                        if(verbose)
                        {
                            printf("miss hit \n");
                        }
                    }
                    else
                    {
                        miss_count++;
                        eviction_count++;
                        hit_count++;
                        if(verbose)
                        {
                            printf("miss eviction hit \n");
                        }
                    }
                    break;
            case 'L':
            case 'S':
                    if(hit)
                    {
                        hit_count++;;
                        if(verbose)
                        {
                            printf("hit \n");
                        }
                    }
                    else if(miss)
                    {
                        miss_count++;
                        if(verbose)
                        {
                            printf("miss \n");
                        }
                    }
                    else
                    {
                        miss_count++;
                        eviction_count++;
                        if(verbose)
                        {
                            printf("miss eviction \n");
                        }
                    }
                    break;
        }

    }
	
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

bool cline(int argc, char * argv[], char * fn, struct cache_t * cache)
{
   int cap = 0;
   bool ret = false;

   for(int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-v", 2) == 0){
            cap++;
            ret = true;
        }
        else if (strncmp(argv[i], "-h", 2) == 0) {
            printHelp(); 
        }
        else if (strncmp(argv[i], "-s", 2) == 0) {
            cap++;
            cache->sets = atoi(argv[i+1]) << 2;
            cache->setIndexBits = atoi(argv[i+1]);
        }
        else if (strncmp(argv[i], "-E", 2) == 0) {
            cache->associativity = atoi(argv[i+1]);
            cap++;
        }
        else if (strncmp(argv[i], "-b", 2) == 0) {
            cache->blockBits = atoi(argv[i+1]);
            cache->blockSize = atoi(argv[i+1]) << 2;
            cap++;
        }
        else if (strncmp(argv[i], "-t", 2) == 0) {
            strcpy(fn, argv[i+1]);
            cap++;
        }
    
    }

   cache->tag = (long unsigned int **)malloc(cache->associativity * sizeof(unsigned long int));
   
   for(int i = 0; i < cache->associativity; i++) {
        cache->tag[i] = (long unsigned int *)malloc(cache->sets * sizeof(unsigned long int));
   }

   if (cap < 4) {printHelp();}

   return ret;
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
        
    printf("csim: Missing required command line argument\n");
    printf("Usage: ./csim [-h] [-v] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n          -h         Print this help message.\n");
    printf("          -v         Optional verbose flag.\n          -s <num>   Number of set index bits.\n");
    printf("          -E <num>   Number of lines per set.\n          -b <num>   Number of block offset bits.\n");
    printf("          -t <file>  Trace file.\nExamples:\n");
    printf("        linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("        linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace");

    exit(1);
}
//checks the number of digits in a long
int digitNum(unsigned long number)
{
        char testString[20];
        sprintf(testString, "%lu", number);
        return strlen(testString);
}
