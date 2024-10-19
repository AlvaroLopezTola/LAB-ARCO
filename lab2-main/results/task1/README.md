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
    find_vector(arr, 6, &min, &max);
    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC

    printf("El valor min es: %d, y el max: %d\n", min, max);
    printf("Tiempo de ejecución: %f segundos\n", time);

    return 0;
    }

A continuación abordamos la paralelización del programa, para la cual modificaremos también el número de hilos.
Así quedaría nuestro programa paralelizado con las directivas 'parallel' 'critical' y 'atomic' y el numero de hilos a 2:

    #include <stdio.h>
    #include <omp.h>
    #include <time.h>

    void find_vector(int *arr, int size, int *min, int *max) {
    int local_min = arr[0];
    int local_max = arr[0];

    #pragma omp parallel num_threads(2)
    {
        int thread_min = arr[0];
        int thread_max = arr[0];
        
        #pragma omp for
        for (int i = 0; i < size; i++) {
            if (arr[i] < thread_min) thread_min = arr[i];
            if (arr[i] > thread_max) thread_max = arr[i];
        }
        
        #pragma omp critical
        {
            if (thread_min < local_min) local_min = thread_min;
            if (thread_max > local_max) local_max = thread_max;
        }

        #pragma omp atomic
        if (thread_min < *min) *min = thread_min;

        #pragma omp atomic
        if (thread_max > *max) *max = thread_max;
    }

    *min = local_min;
    *max = local_max;
    }

La función main será igual a la anterior, la cual nos retorna los valores min y max, y el tiempo de ejecución del programa.
En este punto del informe, antes de compilar y ejecutar el programa paralelizado, pensamos que el tiempo de ejecución será menor
para la nueva función paralelizada; compilando y ejecutando notamos que estamos en lo cierto, el tiempo se ha reducido gracias a la paralelización.

Por último modificaremos el número de hilos para la nueva versión a 4, para ver que influencia tiene sobre el tiempo de ejecución y si este puede
reducirse aún más.

    #include <stdio.h>
    #include <omp.h>
    #include <time.h>

    void find_vector(int *arr, int size, int *min, int *max) {
    int local_min = arr[0];
    int local_max = arr[0];

    #pragma omp parallel num_threads(4)
    {
        int thread_min = arr[0];
        int thread_max = arr[0];
        
        #pragma omp for
        for (int i = 0; i < size; i++) {
            if (arr[i] < thread_min) thread_min = arr[i];
            if (arr[i] > thread_max) thread_max = arr[i];
        }
        
        #pragma omp critical
        {
            if (thread_min < local_min) local_min = thread_min;
            if (thread_max > local_max) local_max = thread_max;
        }

        #pragma omp atomic
        if (thread_min < *min) *min = thread_min;

        #pragma omp atomic
        if (thread_max > *max) *max = thread_max;
    }

    *min = local_min;
    *max = local_max;
    }

