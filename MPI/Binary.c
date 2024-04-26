#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>



void fill_random( int array[], int length, int max); 
void binary_search(int [], int, int, int); 
void bubble_sort(int [], int);
 
int main() 
{

    srand( time(NULL) ); 
    int key, size, i; 
    int list[25];
 
    printf("Enter size of a list: "); 
    scanf("%d", &size);
   
    fill_random(list, size, 200);

    
    for(i = 0; i < size; i++) {
        printf("list[%d]=%d\n", i, list[i]);
    }
        
    bubble_sort(list, size); 
    printf("\n"); 
    printf("Enter key to search\n"); 
    scanf("%d", &key); 
    binary_search(list, 0, size, key);
    
 return 0;
}
 
void bubble_sort(int list[], int size) 
{
    int temp, i, j; 
    for (i = 0; i < size; i++) 
    {
        for (j = i; j < size; j++) 
        {
            if (list[i] > list[j]) 
            {
                temp = list[i]; 
                list[i] = list[j]; 
                list[j] = temp;
            }
        }
    }
}
 
void binary_search(int list[], int lo, int hi, int key) 
{
    int mid;
 
    if (lo > hi) 
    {
        printf("Key not found\n"); 
        return;
    }
    mid = (lo + hi) / 2; 
    if (list[mid] == key) 
    {
        printf("Key found\n");
    }
    else if (list[mid] > key) 
    {
        binary_search(list, lo, mid - 1, key);
    }
    else if (list[mid] < key) 
    {
        binary_search(list, mid + 1, hi, key);
    }
}
void fill_random( int array[], int length, int max) 
{
    for (int i=0; i<length; i++) 
    array[i]=(rand() % max)+1;
}
