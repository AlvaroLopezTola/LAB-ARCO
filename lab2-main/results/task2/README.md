# Solución Ejercicio 2
En este ejercicio nuestro objetivo es paralelizar el código del archivo "[sumavector.cpp](/src/sumavector.cpp)" , para ello tomaremos medidas
de tiempo para las distintas directivas y distintos tamaños del vector, para así poder comparar los resultados y obtener
una tabla comparativa que nos ofrezca una conclusión.

Comenzamos modificando el programa original para calcular su tiempo de ejecución 

    #include <stdio.h> 
    #include <stdlib.h> 
    #include <time.h> 
    #define N 50 // Probar distintos tamaños de vector 

    int main() 
    { 
    int i, sum = 0; 
    int v[N];    

    // Damos valores aleatorios al vector (entre 0 y 99)
    srand (time(NULL)); // Semilla de números aleatorios
    clock_t start = clock();
    for (i = 0; i < N; i++) v[i] = rand()%100; 

    // Cálculo del sumatorio 
    for (i = 0; i < N; i++) sum += v[i];           

    clock_t end = clock();
    double time = (double)(start - end) / CLOCKS_PER_SEC;
    // Como comprobación, se visualizan los valores del vector y la suma 
    printf("\nVector de números: \n "); 
    for (i = 0; i < N; i++) printf("%d \t",v[i]);
    
	  printf("\n La suma es: %d \n\n", sum);
	  printf("Tiempo de ejecución: %f segundos\n", time);
	 
    }

Hemos modificado la función main a 'int' para poder observar el valor del tiempo que tarda en ejecutarse el programa,
y hemos añadido los 'clock()' para calcular con la diferencia de tiempos el resultado final del programa original.

# Paralelización del programa
A continuación utilizamos la directiva parallel y atomic para ver el comportamiento del programa y cuanto tarda en ejecutar:

    #include <stdio.h> 
    #include <stdlib.h> 
    #include <time.h> 
    #define N 50 // Probar distintos tamaños de vector 

    int main() 
    { 
    int i, sum = 0; 
    int v[N];    

    // Damos valores aleatorios al vector (entre 0 y 99)
    srand (time(NULL)); // Semilla de números aleatorios
    clock_t start = clock();
    for (i = 0; i < N; i++) v[i] = rand()%100; 

    // Cálculo del sumatorio
    #pragma omp parallel
    for (i = 0; i < N; i++) {
    	#pragma omp atomic
    	sum += v[i];
    }    

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    // Como comprobación, se visualizan los valores del vector y la suma 
    printf("\nVector de números: \n "); 
    for (i = 0; i < N; i++) printf("%d \t",v[i]);
    
	  printf("\n La suma es: %d \n\n", sum);
	  printf("Tiempo de ejecución con atomic: %f segundos\n", time);
	 
    }

La ejecución del programa fue minimamente mas rápida que la de la versión original;

	eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/ARCO/lab2-main/src$ ./suma2

	Vector de números: 
	 25 	8 	51 	4 	5 	61 	65 	12 	12 	76 	87 	76 	44 	34 	87 	38 	9 	61 	5 	1 	68 	53 	71 	29 	96 	33 	57 	0 	21 	97 	35 	46 	58 	86 	2 	15 	47 	20 	27 	11 	96 	14 	87 	92 	0 	27 	30 	10 	40 	88 	
	 La suma es: 2117 

	Tiempo de ejecución con atomic: 0.000009 segundos

---------------------------------------------------------------------------------------------------------------------------------

Haremos lo mismo para la directiva 'critical':

    #include <stdio.h> 
    #include <stdlib.h> 
    #include <time.h> 
    #include <omp.h> // Incluir OpenMP

    #define N 50 // Probar distintos tamaños de vector 

    int main() 
    { 
    int i, sum = 0; 
    int v[N];    

    // Damos valores aleatorios al vector (entre 0 y 99)
    srand (time(NULL)); // Semilla de números aleatorios
    clock_t start = clock();
    for (i = 0; i < N; i++) v[i] = rand() % 100; 

    #pragma omp parallel
    {
        int local_sum = 0;
        #pragma omp for
        for (i = 0; i < N; i++) {
            local_sum += v[i];
        }
        #pragma omp critical
        {
            sum = local_sum + sum;
        }
    }

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC; // Corregido

    // Como comprobación, se visualizan los valores del vector y la suma 
    printf("\nVector de números: \n "); 
    for (i = 0; i < N; i++) printf("%d \t", v[i]);
    
    printf("\nLa suma es: %d \n\n", sum);
    printf("Tiempo de ejecución (critical): %f segundos\n", time);
     
    return 0; 
    }

Sorprendentemente hemos logrado reducir el tiempo de ejecución de nuevo:

	eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/ARCO/lab2-main/src$ ./suma3

	Vector de números: 
 	72 	48 	5 	58 	41 	69 	23 	22 	53 	79 	28 	86 	61 	86 	61 	6 	79 	39 	70 	52 	47 	16 	94 	22 	46 	79 	98 	20 	65 	66 	86 	37 	14 	92 	48 	7 	13 	71 	82 	18 	2 	10 	56 	15 	96 	18 	21 	75 	9 	44 	
	La suma es: 2405 

	Tiempo de ejecución con critical: 0.000008 segundos

---------------------------------------------------------------------------------------------------------------------------------

# Modificando el tamaño del vector
Finalmente modificaremos el tamaño del vector para las distintas versiones a N = 100, compilaremos y ejecutaremos de nuevo
así lograremos una tabla comparativa entre directivas y tamaños de vector que puedan influir al tiempo de ejecución:

Tiempo para N = 100 con la versión original
----------------------------------------------
	eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/ARCO/lab2-main/src$ ./sumavector

	Vector de números: 
	 55 	25 	39 	2 	97 	70 	54 	53 	67 	45 	60 	89 	75 	70 	36 	42 	79 	74 	28 	7 	58 	74 	76 	38 	4 	52 	37 	71 	93 	51 	16 	48 	29 	7 	3 	78 	29 	57 	84 	96 	2 	44 	38 	30 	15 	74 	72 	46 	48 	52 	54 	59 	78 	30 	49 	35 	34 	87 	58 	80 	90 	74 	80 	19 	34 	83 	98 	63 	93 	82 	12 	47 	78 	2 	29 	45 	76 	2 	92 	76 	6 	98 	35 	85 	28 	85 	20 	15 	24 	78 	47 	14 	5 	79 	86 	39 	63 	36 	54 	8 	
	 La suma es: 5133 

	Tiempo de ejecución: 0.000013 segundos

---------------------------------------------------------------------------------------------------------------------------------

Tiempo para N = 100 con la directiva atomic
----------------------------------------------
	eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/ARCO/lab2-main/src$ ./suma2

	Vector de números: 
	 59 	45 	59 	85 	11 	1 	66 	32 	39 	10 	81 	81 	28 	66 	87 	79 	14 	3 	62 	33 	85 	93 	31 	59 	88 	21 	79 	28 	14 	94 	54 	26 	39 	65 	11 	50 	18 	29 	82 	10 	40 	15 	91 	20 	81 	30 	51 	48 	85 	14 	81 	70 	59 	12 	82 	47 	85 	13 	27 	52 	7 	82 	78 	98 	99 	41 	0 	18 	71 	35 	28 	63 	50 	71 	35 	32 	2 	86 	32 	87 	52 	13 	10 	11 	78 	44 	11 	15 	57 	38 	67 	17 	72 	45 	15 	72 	39 	16 	42 	10 	
	 La suma es: 4659 

	Tiempo de ejecución con atomic: 0.000012 segundos

---------------------------------------------------------------------------------------------------------------------------------

Tiempo para N = 100 con la directiva critical
----------------------------------------------
	eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/ARCO/lab2-main/src$ ./suma3

	Vector de números: 
	 28 	14 	57 	87 	71 	48 	84 	12 	50 	62 	17 	64 	33 	90 	42 	58 	64 	83 	50 	8 	13 	15 	24 	58 	98 	22 	72 	44 	61 	43 	86 	89 	57 	96 	77 	29 	44 	13 	41 	47 	27 	11 	11 	60 	1 	5 	18 	17 	89 	21 	25 	2 	88 	2 	13 	38 	76 	85 	83 	89 	28 	21 	79 	37 	17 	8 	66 	14 	21 	60 	61 	48 	71 	72 	60 	24 	77 	31 	41 	66 	4 	18 	21 	92 	72 	34 	83 	0 	71 	18 	90 	51 	39 	69 	88 	9 	77 	7 	23 	50 	
	La suma es: 4630 

	Tiempo de ejecución con critical: 0.000012 segundos

Finalmente exponemos la tabla para los resultados obtenidos :

|     Directiva             |  Tamaño Vector | Tiempo (s) |
| ------------------------  | -------------  | ---------- |
|  Secuencial               |      50        | 0.000010 s |
| Parallel Atomic           |      50        | 0.000009 s |
| Parallel Critical         |      50        | 0.000008 s |
| Secuencial                |      100       | 0.000013 s |
| Parallel Atomic           |      100       | 0.000012 s |
| Parallel Critical         |      100       | 0.000012 s |


# Conclusión
Los tiempos de ejecución mostrados en la tabla indican que las versiones paralelizadas del programa, 
ya sea utilizando la directiva atomic o critical, ofrecen tiempos de ejecución similares y ligeramente 
más rápidos que la versión secuencial para ambos tamaños de vector (50 y 100).





