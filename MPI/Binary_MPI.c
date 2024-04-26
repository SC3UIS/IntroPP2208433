#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void fill_random(int array[], int length, int max);
void bubble_sort(int [], int);

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv); // Inicializa MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtiene el rango del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el tamaño del comunicador

    srand(time(NULL) + rank); // Establece la semilla para la generación de números aleatorios

    int key, total_size;
    int list[25]; // Arreglo de tamaño fijo

    if (rank == 0) { // Si el proceso tiene rango 0
        printf("Enter total size of the list: ");
        scanf("%d", &total_size); // Lee el tamaño total de la lista desde la entrada estándar

        fill_random(list, total_size, 200); // Llena el arreglo con números aleatorios

        printf("Unsorted list:\n");
        for (int i = 0; i < total_size; i++) {
            printf("list[%d] = %d\n", i, list[i]); // Imprime la lista desordenada
        }
    }

    MPI_Bcast(&total_size, 1, MPI_INT, 0, MPI_COMM_WORLD); // Transmite el tamaño total de la lista a todos los procesos

    int sublist[total_size / size]; // Sublista que contendrá una parte de la lista total
    MPI_Scatter(list, total_size / size, MPI_INT, sublist, total_size / size, MPI_INT, 0, MPI_COMM_WORLD); // Distribuye la lista entre los procesos

    bubble_sort(sublist, total_size / size); // Ordena la sublista usando el algoritmo de ordenamiento de burbuja

    int sorted_list[total_size]; // Arreglo para almacenar la lista ordenada
    MPI_Gather(sublist, total_size / size, MPI_INT, sorted_list, total_size / size, MPI_INT, 0, MPI_COMM_WORLD); // Recopila las sublistas ordenadas en un solo arreglo

    if (rank == 0) { // Si el proceso tiene rango 0
        printf("\nSorted list:\n");
        for (int i = 0; i < total_size; i++) {
            printf("list[%d] = %d\n", i, sorted_list[i]); // Imprime la lista ordenada
        }

        printf("Enter key to search: ");
        scanf("%d", &key); // Lee la clave a buscar desde la entrada estándar

        int lo = 0, hi = total_size - 1;
        while (lo <= hi) { // Búsqueda binaria en la lista ordenada
            int mid = (lo + hi) / 2;
            if (sorted_list[mid] == key) {
                printf("Key found at index %d\n", mid);
                break;
            } else if (sorted_list[mid] < key) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (lo > hi) {
            printf("Key not found\n");
        }
    }

    MPI_Finalize(); // Finaliza MPI
    return 0;
}

void bubble_sort(int list[], int size) {
    int temp, i, j;
    for (i = 0; i < size; i++) {
        for (j = i; j < size; j++) { // Algoritmo de ordenamiento de burbuja
            if (list[i] > list[j]) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void fill_random(int array[], int length, int max) {
    for (int i = 0; i < length; i++)
        array[i] = (rand() % max) + 1; // Llena el arreglo con números aleatorios dentro de un rango máximo
}
