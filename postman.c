/* 
 * C Program to Implement Postman Sort Algorithm

Purpose:

    TRANSFORM is an example of a transformation of an EDP using some parameters for Intro PP Students.

  Example:

    22 March 2024 00:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    22 March 2024

  Author:
  Henry Lizcano
  OpenMP Modification:
  22 March 2024 by Henry Lizcano, Universidad Industrial de Santander                    
  This OpenMP Modification makes a parallelization of the original Code...  


 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <omp.h>




void arrange(int,int);
int array[100], array1[100]; 
int i, j, temp, max, count, maxdigits = 0, c = 0;
double start, end;

 
void main()
{

start = omp_get_wtime(); 
    int t1, t2, k, t, n = 1;
    int chunk=5;
    printf("Enter size of array :");
    scanf("%d", &count);
       



    // seed the random number generator with a different value (the current time)
  // each time the program runs to ensure we get different random numbers each
  // time the program runs
  srand( time(NULL) );
  
  // create an int array of length 100
//  int a[count];

  // fill the array a with random integers between 1-200
  fill_random(array, count, 200);
  
  // output the numbers in the array to verify correctness

#pragma omp parallel
  for (int i = 0; i < count; i++) {
    array[i]=array[i];
    array1[i]=array[i];
 
    printf("array[%d]=%d\n", i, array1[i]);
    }
        

    for (i = 0; i < count; i++)
    {
        t = array[i];        /*first element in t */
#pragma omp parallel
        while(t > 0)
        {
            c++;
            t = t / 10;        /* Find MSB */
        }
        if (maxdigits < c) 
            maxdigits = c;   /* number of digits of a each number */
        c = 0;
    }
    while(--maxdigits) 
        n = n * 10;      
 
    for (i = 0; i < count; i++)
    {
        max = array[i] / n;        /* MSB - Dividnng by perticular base */
        t = i;
#pragma omp for schedule (static, chunk)        
for (j = i + 1; j < count;j++)    
        {
            if (max > (array[j] / n))
            {
                max = array[j] / n;   /* greatest MSB */
                t = j;
            }
        }
        temp = array1[t];
        array1[t] = array1[i];
        array1[i] = temp;
        temp = array[t];
        array[t] = array[i];
        array[i] = temp;
    }
 
 while (n >= 1)
    {
        for (i = 0; i < count;)
        {
            t1 = array[i] / n;

for (j = i + 1; t1 == (array[j] / n); j++);
                arrange(i, j);
            i = j;
        }
        n = n / 10;
    } 
    printf("\nSorted Array (Postman sort) :");    
    for (i = 0; i < count; i++)
        printf("%d ", array1[i]);
    printf("\n");


end = omp_get_wtime();
    printf("Work took %f seconds\n", end - start);


}
 
/* Function to arrange the of sequence having same base*/ 
void arrange(int k,int n)
{
int chunk=2;

    for (i = k; i < n - 1; i++)
    {
#pragma omp for schedule (static, chunk)
        for (j = i + 1; j < n; j++)
        {
            if (array1[i] > array1[j])
            {
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
                temp = (array[i] % 10);
                array[i] = (array[j] % 10);
                array[j] = temp;
            }
        }
    }
}


// fills the array of the given length with random integers between 1 - max
void fill_random(int array[], int length, int max)
{
  // loop through each index of the array... rand() % max will produce a 
  // random number between 0 - (max-1), adding 1 will shift it to 1 - max
  for (int i = 0; i < length; i++)
    array[i] = (rand() % max) + 1;
}
