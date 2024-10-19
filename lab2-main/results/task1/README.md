A continuación desarrollamos un programa con las especificaciones del enunciado, dónde tenemos que encontrar los valores máximo
y mínimo de un vector de enteros. Para ello desarrollamos una función llamada 'find-vector' en la cual debemos pasarle como parametros: 
1- El puntero que apunta hacía el vector 
2- El tamaño del vector 
3- Dos punteros más para los valores máximo y mínimo del vector

La función se vería tal que:

#include <stdio.h>
#include <time.h>

    void find_vector(int *arr, int size, int *min, int *max) {
        *min = arr[0];
        *max = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] < *min) *min = arr[i];
            if (arr[i] > *max) *max = arr[i];
        }
    }

La función inicializa los valores min y max con el primer elemento de nuestro vector, para posteriormente recorrerlo e ir comparando cada 
elemento con los valores actuales de min y max, si encuentra un elemento menor que min, este se actualiza, y para max igual pero con un valor mayor. 
Así conseguimos que al final del recorrido las variables contengan los valores del vector que necesitamos.

Para la función main, hace falta declarar los valores min y max e inicializar el vector con los valores enteros. 
A continuación utilizaremos la biblioteca '<time.h>' para la medición de tiempos de ejecución. Tomaremos el tiempo antes de la ejecución
con 'clock_t start' luego invocaremos a la funciñon 'find-vector' y tomaremos de nuevo el tiempo pasada la ejecución con 'clock_t end'. 
Finalmente calcularemos el tiempo transcurrido como la diferencia de (end - start) entre 'CLOCKS_PER_SEC'

    int main() {

    int arr[] = {10, 4, 8, 1, 2, 7};
    int min, max;

    clock_t start = clock();
    find_min_max(arr, 6, &min, &max);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC

    printf("El valor min es: %d, y el max: %d\n", min, max);
    printf("Tiempo de ejecución: %f segundos\n", time);

    return 0;
    }

