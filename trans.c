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
#include <stdbool.h>
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
    bool diag; //true if number is on the diagonal
    if(M == N)//sees if the dimensions will be a perfect square
    {
        if(M == 32)//checks the sizes to set the appropriate iterator
        {
            iter = 8;
        }
        else
        {
            iter = 4;//tested this with a bunch of different values and found that 4 produced the least amount of misses, not entirely sure why though
        }

        for(int i = 0; i < M; i += iter)//row for loop
        {
            for(int j = 0; j < M; j += iter)//col for loop
             {
                for(int k = i; k < i + iter; k++)//block length
                {
                    for(int p = j; p < j + iter; p++)//block width
                    {
                        if(k != p)//transposes
                        {
                            B[p][k] = A[k][p];
                        }
                        else //element is on diagonal; places A[k][p] into temp for later and dc as a reference
                        {
                           diag = true;
                           temp = A[k][p];
                           dc = k;
                        }
                    }
                    if(diag)//sets the diagonal from temp sets diag back to false
                    {
                      B[dc][dc] = temp;
                      diag = false;
                    }
                }
             }
        }
    }
    else
    {
        iter = 16;//arbitrary number, may change later
        for(int i = 0; i < M; i += iter)//row for loop
        {
            for(int j = 0; j < N; j += iter)//col for loop
            {
              for(int k = j; k < j + iter && k < N; k++)//checks for 2 different bounds, if greater than size and also if greater than the iter + j 
               {
                   for(int p = i; p < i + iter && p < M; p++)//same as previous loop only checks with i and M
                     {
                         if(k != p)//works the same way as above
                         {
                            B[p][k] = A[k][p];
                         }
                         else
                         {
                            diag = true;
                            temp = A[k][p];
                            dc = k;
                         }
                     }
                     if(diag)
                     {
                        B[dc][dc] = temp;
                        diag = false;
                     }
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
