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
| Secuencial | 10,000               | 3.1415926544232282    | 0.0000000008334351 | 0.0000640000                   |
| Parallel   | 10,000               | 3.1415926544231274  | 0.0000000008333347| 0.0157797820                  |
| Critical   | 10,000               | 3.1415926544231270   | 0.0000000008333338 |0.0008599570                |
| Atomic     | 10,000               | 3.1415926544231274   | 0.0000000008333343 | 0.0008669500                 |


# Conclusiones 

1. **Precisión**:
   - Todas las versiones (`secuencial`, `parallel`, `critical`, `atomic`) producen un valor similar de π con errores mínimos , indicando que la precisión no se ve comprometida por la paralelización.

2. **Análisis de Rendimiento**:
   - La versión secuencial es más rápida para pocos intervalos (10,000) debido al bajo coste computacional en comparación con la sobrecarga de gestionar hilos.
   - Las versiones `critical` y `atomic` presentan cierta sobrecarga por la sincronización. La versión `critical` es ligeramente más rápida en este caso, aunque `atomic` suele ser más eficiente con mayores tamaños de problema.
   - La versión `parallel` sin sincronización tiene el mayor tiempo de ejecución, posiblemente debido a condiciones de carrera en la acumulación de resultados.

3. **Escalabilidad**:
   - A medida que aumentan los intervalos, los beneficios de la paralelización deberían ser más evidentes, especialmente para la versión `atomic`, ya que los costes de sincronización se amortizan con más trabajo computacional.
   - Para tareas de mayor envergadura, `atomic` es preferible por su menor sobrecarga en comparación con `critical`.

4. **Elección de Directivas**:
   - La elección entre `critical` y `atomic` depende de la naturaleza del trabajo y la arquitectura. Para cargas ligeras, la paralelización puede no ser beneficiosa debido a los costes de sincronización.
   - En problemas más complejos, `atomic` ofrece un mejor equilibrio entre rendimiento y seguridad de los hilos.

En resumen, aunque las versiones paralelas introducen cierta sobrecarga para problemas pequeños, `atomic` podría ser la opción más adecuada para grandes cantidades de trabajo.


