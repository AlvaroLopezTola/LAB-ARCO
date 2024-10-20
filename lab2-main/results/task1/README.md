# Solución Ejercicio 1
Comenzamos desarrollando un programa con las especificaciones del enunciado, dónde tenemos que encontrar los valores máximo
y mínimo de un vector de enteros. Para ello desarrollamos una función llamada 'find-vector' en la cual introducimos como parametros: 
- El puntero que apunta hacía el vector 
- El tamaño del vector 
- Dos punteros más para los valores máximo y mínimo del vector

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

# Paralelización del programa
Abordamos la paralelización del programa con las directivas de OpenMP, en la cual modificaremos también el número de hilos.
Así quedaría nuestro programa paralelizado con las directivas 'parallel' 'critical' y 'atomic' y el numero de hilos a 2:
Para ello hemos hecho dos versiones, en la que anotamos los tiempos de ejecución para cada directiva.
Con la directiva 'critical'

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

    }

    *min = local_min;
    *max = local_max;
    }

A continuación mostramos la versión con la directiva 'atomic'

    #include <stdio.h>
    #include <omp.h>
    #include <time.h>

    void find_vector(int *arr, int size, int *min, int *max) {
    #pragma omp parallel num_threads(2) // Cambia a 4 para la otra versión
    {
        int thread_min = arr[0];
        int thread_max = arr[0];

        #pragma omp for
        for (int i = 0; i < size; i++) {
            if (arr[i] < thread_min) thread_min = arr[i];
            if (arr[i] > thread_max) thread_max = arr[i];
        }

        #pragma omp atomic
        if (thread_min < *min) *min = thread_min;

        #pragma omp atomic
        if (thread_max > *max) *max = thread_max;
    }
    }

La función main será igual a la anterior, la cual nos retorna los valores min y max, y el tiempo de ejecución del programa, con la directiva utilizada.
En este punto del informe, antes de compilar y ejecutar el programa paralelizado, pensamos que el tiempo de ejecución será menor
para la nueva función paralelizada; compilando y ejecutando notamos que estamos en lo cierto, el tiempo se ha reducido gracias a la paralelización:

    eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/lab2-main/results/task1$ ./critical
    Critical - Min: 1, Max: 10, Tiempo: 0.000005 segundos

    eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/lab2-main/results/task1$ ./atomic
    Atomic - Min: 1, Max: 10, Tiempo: 0.000004 segundos

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

    }
    }

    ------------------------------------------------------------------------
    
    #include <stdio.h>
    #include <omp.h>
    #include <time.h>

    void find_vector(int *arr, int size, int *min, int *max) {
    #pragma omp parallel num_threads(4) // Cambia a 4 para la otra versión
    {
        int thread_min = arr[0];
        int thread_max = arr[0];

        #pragma omp for
        for (int i = 0; i < size; i++) {
            if (arr[i] < thread_min) thread_min = arr[i];
            if (arr[i] > thread_max) thread_max = arr[i];
        }

        #pragma omp atomic
        if (thread_min < *min) *min = thread_min;

        #pragma omp atomic
        if (thread_max > *max) *max = thread_max;
    }
    }

Como resultado mostramos una tabla dónde indicamos las directivas utilizadas, el nº de hilos, y el tiempo de ejecución que ha tenido cada versión del programa.
Para ellos llamaremos a las versiones 'vector1' 'vector2' y 'vector3' según el orden en el que aparecen en el informe.
|  Nombre Versión   |     Directiva             |  Nº de hilos  | Tiempo (s) |
|  ---------------  | ------------------------  | ------------- | ---------- |
|      Vector1      |  Secuencial               |      1        | 0.000006 s |
|      Vector2      | Parallel Atomic           |      2        | 0.000004 s |
|      Vector2.1    | Parallel Critical         |      2        | 0.000004-0.000005 s |
|      Vector3      | Parallel Atomic           |      4        | 0.000005 s |
|      Vector3.1    | Parallel Critical         |      4        | 0.000005 s |

Conclusion: La implementación de la paralelización con OpenMP demostró ser efectiva al reducir el tiempo de ejecución del programa. 
Al comparar los tiempos con diferentes configuraciones de hilos, observamos que el rendimiento mejoró al aumentar el número de hilos, aunque con una reducción menos pronunciada al pasar de 2 a 4 hilos. 
Esto sugiere que hay un punto de saturación en la que la sobrecarga de gestionar más hilos puede contrarrestar las ganancias de paralelización.
