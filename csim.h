typedef struct{
    int sets;
    int setIndexBits;
    int associativity;
    int blockBits;
    int blockSize;
    unsigned long int tag[][];
}cache_t;


public:
	int main();
	int getBits(int first, int second, unsigned long source);
	void getLines();