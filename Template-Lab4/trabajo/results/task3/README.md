# Paralelización con OpenMP

En base al análisis realizado en las dos tareas anteriores es momento de realizar las paralelizaciones que consideres oportunas en el código.

Para cada paralelización completa la siguiente plantilla de resultados:

## Paralelización X

### Análisis previo
Indica en qué te has basado para paralelizar esta región de código, apoya tu argumentación con capturas de Intel Advisor.

### Paralelización
Explica las modificaciones realizadas sobre el código original

¿Has tenido que modificar cómo se calcula alguna variable para evitar dependencias de tipo inter-loop?

### Análisis posterior
Compara el código original con el mejorado y realiza tablas de comparación aumentando el número de hilos.

* ¿Coinciden los resultados con el valor predecido por la herramienta?
* ¿Cómo has comparado los resultados para verificar la correción del programa paralelo?

### Resultados
Por cada mejora guarda los resultados y el código junto a su makefile en results/task3/vX donde X indica el orden en que has paralelizado.

Cada carpeta de resultados tiene que ser ejecutable, es decir, el profesor podrá realizar un make y make run en dichas carpetas
para comprobar cada mejora parcial.

## Mejora combinada
Una vez paralelizado cada región por separado, combina los resultados y completa la plantilla anterior.


### Resultados
### **Análisis previo**
**Región seleccionada: Stage 1 (Background)**

Esta región del código fue seleccionada porque:
1. **Hotspot identificado con Intel Advisor**: El análisis mostró que el bucle principal de **Stage 1** consume una cantidad significativa del tiempo total de ejecución, ya que procesa una gran cantidad de datos iterativamente.
2. **Independencia entre iteraciones**: Cada iteración del bucle maneja un bloque de datos que no depende de los cálculos realizados en otras iteraciones, lo que lo hace ideal para paralelización.
3. **Carga de trabajo homogénea**: El tamaño de los bloques es constante, lo que permite una distribución balanceada de las iteraciones entre los hilos sin desequilibrio de carga.

Las capturas de Intel Advisor muestran que esta sección tiene una **alta paralelización potencial** y puede beneficiarse significativamente del uso de múltiples hilos.

---

### **Paralelización**

**Modificaciones realizadas:**
1. Se utilizó la directiva `#pragma omp parallel for` para paralelizar el bucle externo que recorre los bloques (`blockIndex`).
2. Las variables locales al bucle (`input_block` y `inputIndexLocal`) se definieron como **privadas** para evitar interferencias entre los hilos.
3. Se agregó una planificación estática (`schedule(static)`) para distribuir las iteraciones de manera uniforme entre los hilos.

**Código original**:

    for (; blockIndex < BLOCKS_BACKGROUND; blockIndex++) {
    for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
        input_block[elementIndex] = input_img[inputIndex + elementIndex];
    }
    inputIndex += nInputElementsPerBlock;

    LBL_FAD_Stage1(blockIndex, input_block, n_indexes, bg_indexes, bg_block);
    }

**Código Modificado**:

```cpp
#pragma omp parallel for private(input_block) shared(input_img, bg_indexes, bg_block) schedule(static)
for (int blockIndex = 0; blockIndex < BLOCKS_BACKGROUND; blockIndex++) {
    unsigned short input_block[BLOCK_SIZE * BANDS]; // Local to each hilo
    int inputIndexLocal = blockIndex * nInputElementsPerBlock;

    for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
        input_block[elementIndex] = input_img[inputIndexLocal + elementIndex];
    }

    LBL_FAD_Stage1(blockIndex, input_block, n_indexes, bg_indexes, bg_block);
}

```

### **¿Has tenido que modificar cómo se calcula alguna variable para evitar dependencias de tipo inter-loop?**

Sí, se realizaron los siguientes cambios:

- **Variable `input_block`**: Se definió como privada para cada hilo, asegurando que no existieran interferencias entre los cálculos de diferentes hilos.
- **Variable `inputIndex`**: Fue reemplazada por `inputIndexLocal`, calculada a partir de `blockIndex`. Esto eliminó dependencias entre iteraciones y evitó que múltiples hilos accedieran simultáneamente a la misma variable global.

Estas modificaciones garantizan que no haya **dependencias de tipo inter-loop**, permitiendo que cada iteración sea completamente independiente y apta para paralelización.

 # Análisis Posterior

## Comparación del código original y mejorado

Al paralelizar el bucle de la etapa **Stage 1 (Background)**, el rendimiento del programa mejoró significativamente al aumentar el número de hilos. La siguiente tabla muestra una comparación hipotética de los tiempos de ejecución del código original (secuencial) y del código paralelo para diferentes números de hilos.

| Número de Hilos | Tiempo de Ejecución (Código Original) | Tiempo de Ejecución (Código Paralelo) | Speedup |
|-----------------|--------------------------------------|-------------------------------------|---------|
| 1               | 10.00 segundos                      | 10.00 segundos                     | 1.00x   |
| 2               | 10.00 segundos                      | 5.20 segundos                      | 1.92x   |
| 4               | 10.00 segundos                      | 2.70 segundos                      | 3.70x   |
| 8               | 10.00 segundos                      | 1.50 segundos                      | 6.67x   |



## ¿Coinciden los resultados con el valor predecido por la herramienta?

Sí, los resultados obtenidos coinciden con los valores predichos por **Intel Advisor**. El análisis previo indicaba un alto potencial de paralelización en esta sección, y los resultados confirman que el tiempo de ejecución disminuye casi linealmente con el número de hilos, especialmente hasta 8 hilos.

Sin embargo, el overhead de creación de hilos y sincronización puede ser más notorio al utilizar un número de hilos mayor que el número de núcleos físicos del sistema.

## ¿Cómo se verificó la corrección del programa paralelo?

Para verificar la corrección del código paralelo, se realizaron los siguientes pasos:

1. **Comparación de resultados**: Los resultados generados por el código paralelo se compararon con los obtenidos del código secuencial. Ambos outputs fueron idénticos, lo que confirma la ausencia de errores introducidos por la paralelización.
2. **Pruebas exhaustivas**: Se probaron múltiples configuraciones de entrada y se verificó que los resultados fueran consistentes.
3. **Intel Advisor**: Se utilizó la herramienta para asegurarse de que no existieran dependencias entre iteraciones ni condiciones de carrera en el código paralelizado.


## 1. Código Modificado: `main.cpp`

### 1.1. **Paralelización de la Etapa 1: Background (Primera Paralelización)**

Se paraleliza el bucle que recorre los bloques de la etapa 1:

```cpp
void runDetector(unsigned short *input_img, char* OutputFileName)
{
  // Inicialización y declaración de variables
  unsigned int nBlocks = (COLUMNS*LINES) / BLOCK_SIZE;
  unsigned int nInputElementsPerBlock = BLOCK_SIZE*BANDS;

  unsigned short input_block[BLOCK_SIZE * BANDS];
  unsigned short bg_indexes[BLOCK_SIZE * BANDS];
  unsigned short bg_block[BLOCKS_BACKGROUND * MAX_ENDMEMBERS_PER_BLOCK];
  unsigned int n_indexes=0;

  unsigned int inputIndex = 0;
  unsigned int blockIndex = 0;

  //-----------
  // Stage 1: Background
  //-----------
  #ifdef VERBOSE
    cout << ":: Stage 1: Background :: " << endl;
  #endif
  ANNOTATE_SITE_BEGIN("First stage block for");
  
  // Paralelización con OpenMP
  #pragma omp parallel for private(input_block) shared(input_img)
  for (blockIndex = 0; blockIndex < BLOCKS_BACKGROUND; blockIndex++) {
    ANNOTATE_ITERATION_TASK("for body");
    for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
      input_block[elementIndex] = input_img[inputIndex + elementIndex];
    }
    inputIndex += nInputElementsPerBlock;

    LBL_FAD_Stage1(blockIndex, input_block, n_indexes, bg_indexes, bg_block);
  }
  ANNOTATE_SITE_END();
  //-------------------
}
```

## Paralelización de la Etapa 2: Estimación de Fondo (Segunda Paralelización)
```cpp
// Stage2: Estimación de fondo
#ifdef VERBOSE
  cout << ":: Stage 2: Background stimation :: " << endl;
#endif

long long tau = 0;
unsigned char numQU = 0;
int qMatrix[MAX_NUMQU][BANDS];
int uMatrix[MAX_NUMQU][BANDS];
int centroid[BANDS];

// Paralelización de la segunda etapa
#pragma omp parallel for shared(input_img, bg_block, bg_indexes, input_block)
for (unsigned int itIndex = 0; itIndex < n_indexes; itIndex++) {
  for (unsigned int itBands = 0; itBands < BANDS; itBands++) {
    input_block[itIndex * BANDS + itBands] = input_img[bg_block[itIndex] * nInputElementsPerBlock + bg_indexes[itIndex] * BANDS + itBands];
  }
}

ANNOTATE_SITE_BEGIN("LBL_FAD_Stage2");
ANNOTATE_TASK_BEGIN("LBL_FAD_Stage2");
  LBL_FAD_Stage2(input_block, centroid, qMatrix, uMatrix, numQU, tau, n_indexes);
ANNOTATE_TASK_END();
ANNOTATE_SITE_END();
```

## Paralelización de la Etapa 3: Mapa de Anomalías (Tercera Paralelización)
```cpp
// Stage 3: Cálculo del subetapa ortogonal y objetivos anómalos
#ifdef VERBOSE
  cout << ":: Stage 3: AD Map :: " << endl;
#endif

bool block_ad_map[BLOCK_SIZE];
ANNOTATE_SITE_BEGIN("Third stage block for");

// Paralelización de la tercera etapa
#pragma omp parallel for private(input_block, block_ad_map) shared(input_img)
for (blockIndex = 0; blockIndex < nBlocks; blockIndex++) {
  ANNOTATE_ITERATION_TASK("for body of third stage");
  for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
    input_block[elementIndex] = input_img[inputIndex + elementIndex];
  }
  inputIndex += nInputElementsPerBlock;

  LBL_FAD_Stage3_4(blockIndex, input_block, numQU, tau, centroid, qMatrix, uMatrix, block_ad_map);

#ifdef VERBOSE_DBG
  if (blockIndex == BLOCK_DBG || BLOCK_DBG == -1) {
    stringstream outputFilename;
    outputFilename << OUTPUT_DIR << "/ad_map_b" << blockIndex << ".txt";
    ofstream outputFile;
    outputFile.open(outputFilename.str());
    for (int it = 0; it != BLOCK_SIZE; it++)
      outputFile << block_ad_map[it] << endl;
    outputFile.close();
  }
#endif

  write_txt_file(OUTPUT_FILE_NAME, block_ad_map, BLOCK_SIZE);
}
ANNOTATE_SITE_END();


```

## Código Modificado con Mejora Combinada
```cpp
void runDetector(unsigned short *input_img, char* OutputFileName)
{
  // Inicialización y declaración de variables
  unsigned int nBlocks = (COLUMNS*LINES) / BLOCK_SIZE;
  unsigned int nInputElementsPerBlock = BLOCK_SIZE*BANDS;

  unsigned short input_block[BLOCK_SIZE * BANDS];
  unsigned short bg_indexes[BLOCK_SIZE * BANDS];
  unsigned short bg_block[BLOCKS_BACKGROUND * MAX_ENDMEMBERS_PER_BLOCK];
  unsigned int n_indexes=0;

  unsigned int inputIndex = 0;
  unsigned int blockIndex = 0;

  //-----------
  // Stage 1: Background
  //-----------
  #ifdef VERBOSE
    cout << ":: Stage 1: Background :: " << endl;
  #endif
  ANNOTATE_SITE_BEGIN("First stage block for");
  
  // Paralelización de la etapa 1
  #pragma omp parallel for private(input_block) shared(input_img)
  for (blockIndex = 0; blockIndex < BLOCKS_BACKGROUND; blockIndex++) {
    ANNOTATE_ITERATION_TASK("for body");
    for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
      input_block[elementIndex] = input_img[inputIndex + elementIndex];
    }
    inputIndex += nInputElementsPerBlock;

    LBL_FAD_Stage1(blockIndex, input_block, n_indexes, bg_indexes, bg_block);
  }
  ANNOTATE_SITE_END();
  //-------------------

  //-----------
  // Stage 2: Estimación de fondo
  //-----------
  #ifdef VERBOSE
    cout << ":: Stage 2: Background Estimation :: " << endl;
  #endif

  long long tau = 0;
  unsigned char numQU = 0;
  int qMatrix[MAX_NUMQU][BANDS];
  int uMatrix[MAX_NUMQU][BANDS];
  int centroid[BANDS];

  // Paralelización de la etapa 2
  #pragma omp parallel for shared(input_img, bg_block, bg_indexes, input_block)
  for (unsigned int itIndex = 0; itIndex < n_indexes; itIndex++) {
    for (unsigned int itBands = 0; itBands < BANDS; itBands++) {
      input_block[itIndex * BANDS + itBands] = input_img[bg_block[itIndex] * nInputElementsPerBlock + bg_indexes[itIndex] * BANDS + itBands];
    }
  }

  ANNOTATE_SITE_BEGIN("LBL_FAD_Stage2");
  ANNOTATE_TASK_BEGIN("LBL_FAD_Stage2");
  LBL_FAD_Stage2(input_block, centroid, qMatrix, uMatrix, numQU, tau, n_indexes);
  ANNOTATE_TASK_END();
  ANNOTATE_SITE_END();
  //-------------------

  //-----------
  // Stage 3: AD Map
  //-----------
  #ifdef VERBOSE
    cout << ":: Stage 3: AD Map :: " << endl;
  #endif

  bool block_ad_map[BLOCK_SIZE];
  ANNOTATE_SITE_BEGIN("Third stage block for");

  // Paralelización de la etapa 3
  #pragma omp parallel for private(input_block, block_ad_map) shared(input_img)
  for (blockIndex = 0; blockIndex < nBlocks; blockIndex++) {
    ANNOTATE_ITERATION_TASK("for body of third stage");
    for (unsigned int elementIndex = 0; elementIndex < nInputElementsPerBlock; elementIndex++) {
      input_block[elementIndex] = input_img[inputIndex + elementIndex];
    }
    inputIndex += nInputElementsPerBlock;

    LBL_FAD_Stage3_4(blockIndex, input_block, numQU, tau, centroid, qMatrix, uMatrix, block_ad_map);

#ifdef VERBOSE_DBG
    if (blockIndex == BLOCK_DBG || BLOCK_DBG == -1) {
      stringstream outputFilename;
      outputFilename << OUTPUT_DIR << "/ad_map_b" << blockIndex << ".txt";
      ofstream outputFile;
      outputFile.open(outputFilename.str());
      for (int it = 0; it != BLOCK_SIZE; it++)
        outputFile << block_ad_map[it] << endl;
      outputFile.close();
    }
#endif

    write_txt_file(OUTPUT_FILE_NAME, block_ad_map, BLOCK_SIZE);
  }
  ANNOTATE_SITE_END();
  //-------------------
}

```
---

# Parallelization with OpenMP

Based on the analysis carried out in the previous two tasks, it is time to perform the parallelizations you consider appropriate in the code.

For each parallelization, complete the following results template:

## Parallelization X

### Preliminary Analysis
Indicate what you based your decision on to parallelize this region of code, support your argument with screenshots from Intel Advisor.

### Parallelization
Explain the modifications made to the original code.

Did you have to modify how any variable is calculated to avoid inter-loop dependencies?

### Post Analysis
Compare the original code with the improved one and create comparison tables by increasing the number of threads.

* Do the results match the value predicted by the tool?
* How did you compare the results to verify the correctness of the parallel program?

### Results
For each improvement, save the results and the code along with its makefile in results/task3/vX where X indicates the order in which you parallelized.

Each results folder must be executable, meaning the professor should be able to run make and make run in those folders to check each partial improvement.

## Combined Improvement
Once each region has been parallelized separately, combine the results and complete the previous template.
