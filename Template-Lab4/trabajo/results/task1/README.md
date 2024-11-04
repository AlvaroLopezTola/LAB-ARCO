# Tarea 1: Análisis de la máquina y rendimiento del código

Esta tarea requiere la compilación y ejecución del código para la detección de anomalías. Para ello dispones de un fichero makefile que automatiza ambos procesos.
Teclea **make** para realizar la compilación, y **make run** para ejecutarlo (todo esto dentro del directorio src).
La ejecución requiere de un fichero de datos de entrada que previamente deberás descargar del siguiente [enlace](https://mega.nz/folder/x4gRhLJJ#GRdxQc1Hnw3Lk_-9JC3Uew). El fichero se debe insertar en src, si quieres usar otro directorio deberás modificar la línea 7 del fichero Configurations.h

**En este ejercicio NO debe utilizarse la optimización -xCORE-AVX2 ya que toda la vectorización SIMD se indicará de manera explícita a través de pragmas**

## Preguntas
* Antes de comenzar a realizar ningún análisis sobre el código es interesante conocer las características de la arquitectura sobre la que estás ejecutando el programa, para ello contesta a las siguientes preguntas:

    * Indica tu modelo de procesador, la arquitectura y de cuantos núcleos e hilos de procesamiento dispones
    * ¿Cuantos hilos pueden ser ejecutados por núcleo?

* Realiza un análisis completo desde la vista de CPU/Roofline. Desde la pestaña de "Survey & Roofline" analiza el resultado Top Down.
    * ¿Qué función de nuestra lógica de negocio consume más tiempo?
    * ¿Qué etapas son las más costosas?
    * ¿Qué operaciones (entendemos operaciones como las funciones definidas en LBL_FAD_Transform_Operations.h/.cpp) son las más complejas y requieren de un mayor tiempo?

Realiza un análisis completo y muestra una captura de pantalla del gráfico roofline.
* ¿Cuáles son los tres bucles más complejos? ¿Por qué están limitados? ¿Cómo los mejorarías?

Finalmente resulta interesante ver el patron de acceso de memoria que se realiza en el código con el objetivo de valorar la vectorización o mejorar los accesos a memoria para hacer un mejor uso de la jerarquía de memoria.

Realiza un análisis de tipo "refinement" añadiendo el paso de Memory Access Patterns y selecciona los dos bucles que más tiempo
consumen realizando cálculos internos.

* Indica que dos bucles son
* ¿Qué tipos de acceso a memoria se está realizando? ¿cuáles existen?

Para cada pregunta analiza y aporta las capturas de pantalla que veas conveniente para apoyar la explicación.

## Respuestas
* Antes de realizar los ánalisis convenientes conoceremos las caracteristicas de la arquitectura del PC de Edu:

        eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/Template-Lab4/trabajo/src$ lscpu       
  
     * El modelo del procesador es un Intel Core i5-9300H @ 2.40GHz, con una arquitectura x86_64, con un total de 8 hilos, 4 núcleos.
     * Teniendo 4 núcleos y 8 hilos, podremos ejecutar 2 hilos por núcleo.

 * Las caracteristicas de la arquitectura del PC de Álvaro son:

      * El modelo del procesador es un AMD Ryzen 7 6800HS @ 4,7GHz, con una arquitectura x86_64 , con 16 hilos en total y 8 nucleos.
      * Teniendo 2 hilos por nucleo para ejecutar.


* Desde la pestaña de Top Down analizamos las funciones que más consumen y son:

   * AD_Stage3_4 con un tiempo de 3,532 segundos.
   * loop in LBL_FAD_Stage3_4 at LBL_FAD_Transform_Operations.cpp:146 con un tiempo de 2,822 segundos.

* La etapa más costosa es la 3

* Y las operaciones más complejas y que requieren mayor tiempo son las de substractinginformation, por los 2 bucles anidados que contiene.
 
   


      
----

# Task 1: Machine Analysis and Code Performance

This task requires the compilation and execution of the code for anomaly detection. For this, you have a makefile that automates both processes.
Type **make** to compile, and **make run** to execute it (all within the src directory).
The execution requires an input data file that you must download from the following [link](https://mega.nz/folder/x4gRhLJJ#GRdxQc1Hnw3Lk_-9JC3Uew). The file should be placed in src, if you want to use another directory you must modify line 7 of the Configurations.h file.

**In this exercise, the -xCORE-AVX2 optimization should NOT be used as all SIMD vectorization will be explicitly indicated through pragmas**

## Questions
* Before starting any analysis on the code, it is interesting to know the characteristics of the architecture on which you are running the program, so answer the following questions:

    * Indicate your processor model, architecture, and how many cores and processing threads you have.
    * How many threads can be executed per core?

* Perform a complete analysis from the CPU/Roofline view. From the "Survey & Roofline" tab, analyze the Top Down result.
    * Which function of our business logic consumes the most time?
    * Which stages are the most costly?
    * Which operations (we understand operations as the functions defined in LBL_FAD_Transform_Operations.h/.cpp) are the most complex and require the most time?

Perform a complete analysis and show a screenshot of the roofline graph.
* What are the three most complex loops? Why are they limited? How would you improve them?

Finally, it is interesting to see the memory access pattern performed in the code to evaluate vectorization or improve memory accesses to make better use of the memory hierarchy.

Perform a "refinement" analysis by adding the Memory Access Patterns step and select the two loops that consume the most time performing internal calculations.

* Indicate which two loops they are.
* What types of memory access are being performed? Which ones exist?

For each question, analyze and provide screenshots that you deem appropriate to support the explanation.
