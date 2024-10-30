# Tarea 3: Vectorización

## Preguntas
* Antes de comenzar la vectorización es importante conocer cuáles son las características de tu máquina ¿Cuáles son las extensiones multimedia SIMD con las que cuenta tu arquitectura?

* Observa el análisis que has realizado al programa complexmul.cpp. El propio Intel Advisor debe haber detectado que hay una infrautilización de instrucciones, esto está directamente relacionado con la vectorización, ya que lo que pretende reflejar es que tienes disponibles las extensiones SIMD y no las estás utilizando. Para vectorizar el algoritmo, el propio programa Intel Advisor te aconseja como hacerlo ¿Qué has hecho para vectorizar el bucle? Ten en cuenta que debes vectorizar lo máximo que te permita tu arquitectura.

* Una vez vectorizado el programa realiza un análisis y guárdalo con el nombre task3:
    * ¿Cual es el valor del campo Vector Length? ¿Es este el valor esperado teniendo en cuenta las extensiones que estás utilizando y que el programa utiliza floats de 32 bits? Tanto si la respuesta es afirmativa como negativa justifica cual es el valor que esperabas.
    * ¿Cuál ha sido la ganancia? Explica si es el resultado esperado, si no lo es, explica cuál crees que es la razón (Pista: Intel Advisor puede darte indicios de cuál es el problema).

## Respuestas
* Conocemos en primer lugar las caracteristicas de la máquina de Eduardo, para ello ejecutamos el comando:

      eduardo@eduardo-GF65-Thin-9SEXR:~$ lscpu
   

   Cuenta con un modelo de CPU Intel Core i5-9300H, una Arquitectura x86_64 (64 bits) con 4 núcleos y 8 hilos        gracias a Hyper-Threading, por último las extensiones multimedia soportadas son varias: AVX, AVX2, MME, SSE,       SSE2, SSE3, SSE4_1, SSE4_2, MMX, 3DNow.

  En el caso de Álvaro usamos el mismo comando lscup. 
  Obtenemos estos resultados : modelo de CPU AMD Ryzen 7 6800HS, una Arquitectura x86_64 (64 bits) con 8 núcleos    y 16 hilos gracias a SMT (Simultaneous Multithreading). Las extensiones 
  multimedia soportadas son varias: AVX, AVX2, FMA, SSE, SSE2, SSE4_1, SSE4_2, MMX y 3DNow!.

  *Hemos analizado el rendimiento del  programa complexmul.cpp utilizando Intel Advisor, que detecta una infrautilización de instrucciones, indicando que el algoritmo no estaba aprovechando al 
   máximo las capacidades de vectorización de la arquitectura SIMD disponible en la CPU. Para abordar este problema, hemos vectorizado el bucle de multiplicación de números complejos utilizando 
   las extensiones AVX2.
  ##Cambios realizados para la vectorización
   1.Uso de intrínsecos AVX2: 
     Reemplazamos las operaciones de multiplicación y suma de números complejos en el bucle anidado por instrucciones intrínsecas de AVX2, como _mm256_fmsub_ps y _mm256_fmadd_ps. Estas 
     funciones permiten realizar operaciones en paralelo sobre múltiples elementos de un vector en una sola instrucción, aprovechando así la capacidad de procesamiento vectorial de la CPU.
   2.Carga y almacenamiento en registros:
     Implementamos la carga de los datos de los array a y b directamente en registros de 256 bits, utilizando _mm256_loadu_ps, para manipular varios elementos de manera simultánea. Luego, 
     guardamos los resultados en el array c usando _mm256_storeu_ps.
   3.Paralelización con OpenMP:
     Utilizamos directivas de OpenMP para paralelizar el bucle exterior, permitiendo que múltiples hilos procesaran diferentes filas del resultado simultáneamente. Esto no solo mejora el 
     rendimiento a través de la vectorización, sino que también aprovecha la capacidad de múltiples núcleos de la CPU.
   4.Configuración de compilación:
     Compilamos el programa con las opciones -mavx2 y -march=native para habilitar las instrucciones AVX2 y optimizar el código para nuestra arquitectura.

     Estos cambios permiten que el bucle de multiplicación de números complejos se vectorice, utilizando las capacidades SIMD de la CPU y mejorando significativamente el rendimiento del 
     programa. Al ejecutar el programa después de aplicar estas optimizaciones, vemos una reducción considerable en el tiempo de ejecución, lo que indica que la vectorización fue efectiva

  *Después de vectorizar el programa complexmul.cpp y ejecutarlo en Intel Advisor, el valor del campo Vector Length fue 8. Este valor corresponde a la longitud del vector en operaciones SIMD,
   que, en este caso, indica cuántos elementos de tipo float de 32 bits se pueden procesar simultáneamente.
   Dado que estamos utilizando instrucciones AVX2, que operan sobre registros de 256 bits, el valor esperado para el campo Vector Length es 8, ya que cada float ocupa 32 bits. La operación de 
   un registro de 256 bits puede procesar hasta 8 float en paralelo. Por lo tanto, el valor observado de 8 es el valor esperado y está en línea con las capacidades de la extensión AVX2 
   utilizada.

  *Analísis de ganancia
    Versión Original
     Tiempo total de CPU: 10.47 segundos
     Instrucciones de vectorización: SSE2 (no hay vectorización efectiva en el código)
     Rendimiento en GFLOPS: 1.91 GFLOPS
    Versión Vectorizada (Optimizada)
     Tiempo total de CPU: 0.789 segundos
     Instrucciones de vectorización: AVX2 (utiliza instrucciones vectoriales)
     Rendimiento en GFLOPS: 250 GFLOPS
   *Ganancia de Rendimiento
      Reducción de tiempo: De 10.47 segundos a 0.789 segundos, lo que implica una disminución del tiempo en un 93%.
      Incremento en GFLOPS: De 1.91 a 250, un aumento significativo que confirma el uso eficiente de las instrucciones AVX2.

    La ganancia obtenida es notablemente alta, y esto se alinea con lo esperado al aprovechar al máximo las instrucciones AVX2 en la vectorización del programa. Intel Advisor confirma que el 
    cambio en el conjunto de instrucciones de SSE2 a AVX2, que permite un mayor número de operaciones simultáneas, es el principal factor de mejora en el rendimiento.
    Este incremento en rendimiento es el resultado esperado, ya que la vectorización ha permitido aprovechar al máximo las capacidades de la arquitectura SIMD disponible.







  
    
  
-----

# Task 3: Vectorization

## Questions

* Before starting the vectorization process, it is crucial to understand the specifics of your machine. What are the SIMD multimedia extensions available on your architecture?
* Review the analysis you've conducted on the complexmul.cpp program. Intel Advisor should have identified an underutilization of instructions, directly related to vectorization, as it indicates that you have available SIMD extensions that are not being leveraged. To vectorize the algorithm, Intel Advisor itself provides guidance on how to proceed. What steps have you taken to vectorize the loop? Keep in mind that you should pursue maximum vectorization that your architecture permits.

* After vectorizing the program, conduct an analysis and save it under the name "task3":
   * What is the value indicated in the 'Vector Length' field? Considering the extensions you're utilizing and the program's use of 32-bit floats, is this the expected value? Justify the anticipated value, whether the actual value aligns with your expectations or not.
   * What was the extent of the improvement? Discuss whether this is the outcome you predicted; if not, explain what you believe might be the reason (Hint: Intel Advisor can offer insights into what the issue might be).
