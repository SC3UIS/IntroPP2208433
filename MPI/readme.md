El codigo en c del Binary short usando MPI funciona de la siguiente manera:

Inicialización:
El programa comienza inicializando MPI usando MPI_Init(&argc, &argv).
Recupera la clasificación del proceso actual (rango) y el número total de procesos (tamaño) usando MPI_Comm_rank() y MPI_Comm_size() respectivamente.

Generación de lista aleatoria:
Si la clasificación es 0, le solicita al usuario que ingrese el tamaño total de la lista y genera una lista aleatoria de números enteros usando la función fill_random().
Luego, la lista generada se imprime.

Tamaño de la lista de transmisión:
El tamaño total de la lista se transmite a todos los procesos mediante MPI_Bcast().

Dispersión de la lista:
La lista se divide en sublistas, cada una de las cuales se asigna a diferentes procesos mediante MPI_Scatter(). Cada proceso recibe una parte de la lista original.

Ordenar sublistas:
Cada proceso ordena su respectiva sublista utilizando el algoritmo de clasificación de burbujas implementado en la función bubble_sort().
Recopilación de sublistas ordenadas:

Las sublistas ordenadas se vuelven a reunir en una única lista ordenada usando MPI_Gather().

Impresión de lista ordenada:
Si el rango es 0, imprime la lista ordenada.

Búsqueda binaria:
Si la clasificación es 0, le solicita al usuario que ingrese un número para buscar en la lista ordenada.
Realiza una búsqueda binaria en la lista ordenada para encontrar el número indicado en la lista.

Imprime el índice del número a buscar y que en efecto fue encontrado, si lo encuentra. De lo contrario, imprime un mensaje indicando que no se encontró el número indicado en la lista.

Terminación:
Finalmente, MPI se finaliza usando MPI_Finalize() antes de que salga del programa.





