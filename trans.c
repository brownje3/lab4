/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

bool checkBounds(int start, int size, int steps);

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int temp;//temporary variable
    int dc;//variable found on diagonal of matrix; short for don't change
    int iter;//iterators for row and column, basically the dimensions of the block; chance they may change for the third case, same for the first 2

    if(M == N)//sees if the dimensions will be a perfect square
    {
        if(M == 32)//checks the sizes to set the appropriate iterator
        {
            iter = 8;
        }
        else
        {
            iter = 16;
        }

        for(int i = 0; i < M; i = i += iter)//row for loop
        {
            for(int j = 0; j < M; j += iter)//col for loop
             {
                for(int k = i; k < i += iter; k++)//block length
                {
                    for(int p = j; p < j += iter; p++)//block width
                    {
                        if(k == p)//checks to see if the element is on the diagonal; places A[k][k] into temp for later and dc as a reference for when i and j are the same
                        {
                            temp = A[k][k];
                            dc = k;
                        }
                        else //element is not on diagonal
                        {
                            B[p][k] = A[k][p];
                        }
                    }
                    if(i == j)//sets the diagonal from temp
                    {
                        B[dc][dc] = temp;
                    }
                }
             }
        }
    }
    else
    {
        iter = 8;//arbitrary number, may change later
        for(int i = 0; i < M; i += iterRow)//row for loop
        {
            for(int j = 0; j < N; j += iterCol)//col for loop
            {
                 int k = i;//sets k
                 int p = j;//sets p
                 while(checkBounds(k, N, iterRow))//checks if k is within bounds of the block and array
                 {
                     while(checkBounds(p, M, iterCol))//checks if p is within bounds of the block and array
                     {
                         if(k == p)//functions the same as earlier, checks for the diagonal
                         {
                             temp = A[k][k];
                             dc = k;
                         }
                         else
                         {
                             B[p][k] = A[k][p];
                         }
                         p++;
                     }
                     k++;
                 }
                 if(i == j)
                 {
                     B[dc][dc] = temp;
                 }
              }
          }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

bool checkBounds(int start, int size, int steps)
{
    if(start > size || start > (size + steps))
    {
        return false;
    }
    return true;
}
