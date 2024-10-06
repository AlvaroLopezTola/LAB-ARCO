# ORDENADOR 1 ÁLVARO
#ICPX
En cuánto a la compilación del programa con icpx el tiempo transcurrido fue de 0,11s, utilizando la notación adecuada en cuánto a compilación.
El tiempo de CPU fue de 0,10s al igual que el tiempo en código escalar

Mayores tiempos de consumo de bucles:
- Línea 72: tiempo propio: 0.100s	tiempo total: 0.100s	
- Linea 67: tiempo propio: <0.001s	tiempo total: 0.100s	
- Linea 69: tiempo propio: <0.001s	tiempo total: 0.100s

# ORDENADOR 1 ÁLVARO
# G++
En cuánto a la compilación con g++ el tiempo transcurrido hasta que ejecutó el programa fu de 0,11s, y notamos que no estamos utilizando el tipo de compilador adecuado.
CPU TIME: 0,11s
TIME IN SCALAR CODE: 0,11s
Notamos también en estos tiempos que podemos tener un menor tiempo utilizando la compilación adecuada

Consumo en bucles:
- Línea 72: tiempo propio: 0.110s	tiempo total: 0.110s	
- Linea 67: tiempo propio: <0.001s	tiempo total: 0.100s	
- Linea 69: tiempo propio: <0.001s	tiempo total: 0.100s	


# ORDENADOR 2 EDU
# ICPX
Referente a la ejecución del programa matmul con icpx podemos observar en las métricas del programa que el tiempo de ejecución fue de 0.11s, nos da información de que la arquitectura del conjunto de instrucciones es la más alta, esto se debe a que utilizamos el compilador adecuado.
En cuanto a los tiempos de CPU y código escalar fueron ambos de 0.10s. 
 
Tiempo de consumo de los bucles escalares:
- Línea 72: tiempo propio: 0.100s	tiempo total: 0.100s	numero de ejecuciones: 301
- Linea 67: tiempo propio: <0.001s	tiempo total: 0.100s	numero de ejecuciones: 300
- Linea 69: tiempo propio: <0.001s	tiempo total: 0.100s	numero de ejecuciones: 300

En recomendaciones encontramos que nuestra aplicación ha sido compilada con el conjunto de instrucciones escalar, el cual es menor que AVX2, pero al ejecutar con -xCORE-AVX2 nos da error y no nos crea el binario del programa para poder analizarlo de nuevo en advisor-gui, esta recomendación nos la da para el bucle de la línea 72 del programa, un bucle escalar.

# ORDENADOR 2 EDU
# G++
En cuanto al analisis del programa compilado con g++ notamos que los tiempos de ejecución son similares, 0.11s, el tiempo para operaciones de punto flotante ha sido 0.52 y para los bucles redundantes (GINTOPS) 2,60s.
Los tiempos de CPU y código escalar fueron también de 0.10s.

Los mayores tiempo de consumo en bucles fueron:
- Línea 72: tiempo propio: 0.100s	tiempo total: 0.100s	numero de ejecuciones: 301
- Linea 67: tiempo propio: <0.001s	tiempo total: 0.100s	numero de ejecuciones: 300
- Linea 69: tiempo propio: <0.001s	tiempo total: 0.100s	numero de ejecuciones: 300


El Ordenador 2 tiene una ventaja clara en cuanto a frecuencia del procesador (2.40 GHz frente a
1.60 GHz). Esta mayor frecuencia le permite ejecutar más operaciones por segundo, por lo cual los
tiempos de ejecución son menores en los bucles redundantes, especialmente con el compilador icpx,
que está optimizado para extraer mejor rendimiento de la CPU:
Por ejemplo en el bucle de la linea 72 el Ordenador 1 tuvo un tiempo de 9,998ms frente a 29,990ms
del ordenador 2

El compilador icpx demuestra un mejor rendimiento en ambos sistemas, con una reducción clara del
tiempo de ejecución respecto a g++. La ventaja del Ordenador 2 en frecuencia de CPU le
permite obtener un tiempo mucho menor con icpx, en general el compilador icpx proporciona un
rendimiento notablemente mejor en ambos sistemas, especialmente en el Ordenador 2, donde el
procesador de mayor frecuencia y el mayor tamaño de RAM permiten un salto significativo en los
GFLOPS alcanzados, resaltando la importancia de la combinación entre hardware optimizado y un
compilador eficiente.

Ambos sistemas cuentan con el mismo tipo de procesador, el Ordenador 2 tiene 16 GB de RAM, el doble de la memoria del Ordenador 1 con 8 GB. Esto no solo le permite manejar mejor las
operaciones en memoria, sino que reduce las operaciones en la caché, lo que se traduce en un menor
uso de memoria durante la ejecución del programa.

Este informe refleja cómo la frecuencia del procesador, la cantidad de RAM y la optimización del
compilador impactan directamente en el rendimiento de programas de cómputo intensivo. Una mayor
frecuencia de CPU permite ejecutar más operaciones en paralelo, mientras que más memoria RAM reduce
la necesidad de acceder a la memoria secundaria o que mejora la eficiencia general del sistema.
