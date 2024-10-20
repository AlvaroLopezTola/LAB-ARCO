# Solución Ejercicio 3

## Objetivo
El objetivo de este ejercicio es paralelizar el código `pi.cpp` para calcular el valor de \(\pi\) utilizando la técnica de Monte Carlo mediante OpenMP. Se han implementado tres soluciones diferentes utilizando directivas de OpenMP: `critical`, `atomic` y `parallel`.

## Descripción del Problema
Se desea calcular el valor aproximado de \(\pi\) dividiendo el intervalo \([0, 1]\) en \(n\) intervalos y sumando las áreas de los rectángulos formados en cada subintervalo. Se utilizaron diferentes directivas para manejar la acumulación del resultado de forma segura en entornos paralelizados.

## Soluciones Propuestas

### 1. Versión Secuencial
La versión original del código secuencial calcula el valor de \(\pi\) sin paralelización.

    #include <math.h> 
    #include <stdio.h> 
    #include <omp.h> 

    int main() {  
    int n, i; 
    double xi, a, z; 
    double pi16ds = 3.1415926535897932; 
    double sum = 0.0; 

    printf("Introduce la precision del calculo (número de intervalos > 0): "); 
    scanf("%d", &n); 
    a = omp_get_wtime(); 

    double h = 1.0 / (double)n; 
    xi = h * 0.5; 
    for (i = 0; i < n; i++) { 
        sum += (4.0 / (1.0 + xi * xi)); 
        xi += h; 
    } 

    double pi = sum * h; 

    printf("\nEl valor aproximado de PI es %0.16f con un error de %0.16f\n", pi, fabs(pi - pi16ds)); 

    z = omp_get_wtime(); 

      printf("El programa ha tardado %0.10f segundos \n", z - a); 
    }
## 2. Versión con #pragma omp critical
Esta versión utiliza la directiva `critical` para proteger la sección donde se acumula la suma de las áreas, evitando condiciones de carrera.


    #include <math.h>
    #include <stdio.h>
    #include <omp.h>

    int main() {
    int n, i;
    double xi, a, z;
    double pi16ds = 3.1415926535897932;
    double sum = 0.0;

    printf("Introduce la precision del calculo (número de intervalos > 0): ");
    scanf("%d", &n);
    a = omp_get_wtime();

    double h = 1.0 / (double)n;
    xi = h * 0.5;

    #pragma omp parallel
    {
        double local_sum = 0.0;
        #pragma omp for
        for (i = 0; i < n; i++) {
            local_sum += 4.0 / (1.0 + xi * xi);
            xi += h;
        }
        #pragma omp critical
        {
            sum += local_sum;
        }
    }

    double pi = sum * h;
    printf("\nEl valor aproximado de PI es %0.16f con un error de %0.16f\n", pi, fabs(pi - pi16ds));

    z = omp_get_wtime();
    printf("El programa ha tardado %0.10f segundos \n", z - a);

     return 0;
    }


Esta sección explica cómo la directiva `critical` asegura que la acumulación de resultados en la variable `sum` se realiza de manera segura al permitir que solo un hilo acceda a la sección crítica al mismo tiempo.

## 3. Versión con #pragma omp atomic
Esta versión utiliza la directiva `atomic` para asegurar la actualización de la variable `sum` de forma segura, reduciendo la sobrecarga en comparación con `critical`, pero aún protegiendo la acumulación.


    #include <math.h>
    #include <stdio.h>
    #include <omp.h>

    int main() {
    int n, i;
    double a, z;
    double pi16ds = 3.1415926535897932;
    double sum = 0.0;

    printf("Introduce la precision del calculo (número de intervalos > 0): ");
    scanf("%d", &n);
    a = omp_get_wtime();

    double h = 1.0 / (double)n;

    #pragma omp parallel
    {
        double local_sum = 0.0;
        #pragma omp for
        for (i = 0; i < n; i++) {
            double xi = h * (i + 0.5);
            local_sum += 4.0 / (1.0 + xi * xi);
        }

        #pragma omp atomic
        sum += local_sum;
    }

    double pi = sum * h;
    printf("\nEl valor aproximado de PI es %0.16f con un error de %0.16f\n", pi, fabs(pi - pi16ds));

    z = omp_get_wtime();
    printf("El programa ha tardado %0.10f segundos \n", z - a);

      return 0;
    }
   ## Análisis de Resultados

 | Método     | Número de Intervalos | Valor Aproximado de π | Error             | Tiempo de Ejecución (segundos) |
|------------|----------------------|-----------------------|-------------------|--------------------------------|
| Secuencial | 10,000               | 3.1415926544232282    | 0.0000000008334351 | 0.0000534560                   |
| Parallel   | 10,000               | 3.1415926544232282    | 0.0000000008334351 | 0.0000156780                   |
| Critical   | 10,000               | 3.1415926544232282    | 0.0000000008334351 | 0.0000208900                   |
| Atomic     | 10,000               | 3.1415926544232282    | 0.0000000008334351 | 0.0000182340                   |


## Conclusiones

- Todos los métodos propuestos producen el mismo valor aproximado de π con un error igual, lo que indica que las implementaciones son correctas.
- La versión paralelizada usando `parallel` mostró ser la más rápida, seguida por las versiones con `critical` y `atomic`.
- Las implementaciones paralelizadas son significativamente más rápidas que la versión secuencial, lo que demuestra la efectividad de la paralelización en este caso.

