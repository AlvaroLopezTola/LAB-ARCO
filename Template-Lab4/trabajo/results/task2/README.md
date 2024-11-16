# Tarea 2: Anotación y análisis de tipo threading

Antes de realizar una modificación en un programa, con la complejidad que ello conlleva, resulta muy interesante poder realizar un análisis o profiling para ver los posibles puntos de mejora.
Estos análisis pueden variar en complejidad y en función de la cantidad de datos que se de a la herramienta la predicción de mejora será más o menos precisa.

Intel advisor posee la vista threading para este cometido. Una vez seleccionada esta vista aparecerá un nuevo análisis llamado "Suitability". Mediante este análisis podrás ver el rendimiento esperado en caso de paralelizar determinadas regiones de código.

Para que la herramienta pueda realizar este análisis requiere ayuda por parte del programador/a.
El programador deberá instrumentalizar el código mediante las herramientas que el programa de análisis provea. En el caso de intel advisor a este proceso se le llama "anotación de código".

Revisa el código y responde a las siguientes preguntas:

* ¿Qué bucles se han anotado?
* ¿Qué estructura sigue una anotación? ¿En qué partes se descomponen?
* Las anotaciones son como un pseudocódigo de cómo paralelizaríamos con OpenMP. ¿A qué equivale en OpenMP cada una de las partes de la anotación?

Una vez ejecutado el análisis de tipo "Suitability" accede a la pestaña Suitability Report y contesta a las siguientes preguntas:

* ¿Qué significan cada una de las columnas de la tabla superior?
* ¿Qué diferencia existe entre Impact to Program Gain y "Site Gain"?
* ¿Qué bucles paralelizarías? ¿Con qué bucle obtendrías un mayor rendimiento?
* ¿Cómo afecta la duración y número de iteraciones al rendimiento esperado? Utiliza capturas de pantalla para apoyar el análisis
* ¿A qué corresponde el número de iteraciones en cada "site" en el código? ¿Qué explicación tienen dentro del algoritmo?


# Respuestas

Antes de pasar a analizar los resultados de Intel Advisor es necesario instumentalizar el código para que la herramienta sea capaz de entender que partes queremos paralelizar, mejorar.
* Hemos anotado los bucles del anterior ejercicio porque eran los que más tiempo consumían, estos se encuentran anotados mediante comentarios y directivas de Intel Advisor: subtractingInformation, projectingImg, brightnessAD.
* La estructura de una anotación generalmente sigue un formato basado en identificación de bucles, que podrían ser paralelizados, aparte de proporcionar información de como podrían ejecutarse en paralelo y mas recomendaciones.
Se descomponen en 4 partes:
  - Directiva de paralelización: esto es una sugerencia o instrucción prara indicar que bucle o sección de código es candidato para la paralelización.
  - Dependencias de datos: en algunos casos se especifican dependencias entre iteraciones del bucle que podrían limitar la paralelización.
  - Tamaño del dominio: en ocasiones el programador proporciona detalles sobre el tamaño de los datos, como por ejemplo los vectores o matrices.
  - Sugerencias de paralelización: el programador debe indicar que tipo de paralelización cree que es más adecuada utilizar.

Como ya sabemos, en términos de OpenMP:
#pragma omp parallel for (para paralelizar bucles)
#pragma omp for (para dividir el trabajo entre hilos)
#pragma omp critical (para secciones críticas)
#pragma omp reduction (para reducir variables compartidas entre hilos)

* Podemos observar las columnas, e identificar que dato nos proporciona cada una de ellas:
  - Loop: identificador del bucle
  - Total Serial Time: tiempo en ejecutar una región del código sin paralelización
  - Site Gain: es la ganancia estimada al paralelizar la región del código en función del ánalisis. Es decir, cuánto mejoraría esta parte con paralelización
  - Impact to Program Gain: es la ganancia de rendimiento estimada para el programa completo si la paralelización se implementara
* Podemos observar la diferencia de ambas en las anteriores descripciones, 'Site Gain' es para una región del código mientras que 'Impact to Program Gain' es para el código completo.

---

# Task 2: Annotation and threading analysis

**In this exercise, the -xCORE-AVX2 optimization should NOT be used as all SIMD vectorization will be explicitly indicated through pragmas**

Before making a modification to a program, with the complexity that entails, it is advisable to perform an analysis or profiling to see the possible points of improvement of the program.
These analyses can vary in complexity and, depending on the amount of data given to the tool, the quality of the prediction will be higher or lower.

Intel Advisor has the threading view for this purpose. Once this view is selected, a new analysis called "Suitability" will appear. Through this analysis, you can see the expected performance if certain regions of code are parallelized.

For the tool to perform this analysis, it requires help from the programmer.
The programmer must instrument the code using the tools provided by the analysis program. In the case of Intel Advisor, this process is called "code annotation."

Review the code and answer the following questions:

* Which loops have been annotated?
* What structure does an annotation follow? Into what parts is it decomposed?
* Annotations are like pseudocode of how we would parallelize with OpenMP. What does each part of the annotation correspond to in OpenMP?

Once the "Suitability" analysis is executed, go to the Suitability Report tab and answer the following questions:

* What do each of the columns in the top table mean?
* What is the difference between Impact to Program Gain and "Site Gain"?
* Which loops would you parallelize? With which loop would you achieve the highest performance?
* How do duration and number of iterations affect the expected performance? Use screenshots to support the analysis.
* What does the number of iterations in each "site" correspond to in the code? What is its function within the algorithm?
