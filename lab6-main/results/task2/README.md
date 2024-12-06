# Tarea 2
El código en [src/task2/buffer.cpp](../../src/task2/buffer.cpp) debería representar el siguiente flujo:
1. Inicializar el buffer A
2. Sumar al valor de cada posición de A el índice de la iteración
3. Inicializar el buffer B Del mismo modo que A
4. Calcular B como resultado del valor de B multiplicado por A

## Comprueba el resultado y muéstralo a continuación
![image](https://github.com/user-attachments/assets/75ab3af9-1f00-48e6-bb70-f9959c8f8b9e)


## ¿Qué abstracción se está usando para los contenedores de datos?

*buffer<int>: Se utiliza como contenedor para los datos que se procesarán en el dispositivo como la GPU o CPU. Los buffers se declaran con un rango (range<1>{num}) que define su tamaño.
* Los buffers gestionan automáticamente la transferencia de datos entre el host (CPU) y el dispositivo (GPU u otros aceleradores). Esto significa que  no necesitamos preocuparnos directamente por mover datos entre la memoria del host y del dispositivo.

* Para trabajar con los datos en los buffers dentro de un kernel, se utilizan accesores. Estos permiten leer, escribir o realizar operaciones en los datos del buffer dentro del contexto del kernel.
## Ejemplos en el código:
* accessor out(A, h, write_only);: Se crea un acceso de escritura a los datos en el buffer A.
* accessor in(A, h, read_only);: Se crea un acceso de solo lectura a los datos en el buffer A.

En resumen, los buffers son la abstracción principal para manejar contenedores de datos en SYCL. Actúan como una capa intermedia que permite abstraer y gestionar 
la memoria entre el host y el dispositivo.

## ¿Cómo se está formando el DAG? ¿implicitamente? ¿explicitamente?
* La formación del DAG en este código es implícita. SYCL utiliza los buffers y accesores para rastrear automáticamente las dependencias entre las tareas, y organiza la ejecución en el dispositivo respetando estas dependencias. Esto simplifica la programación, ya que no necesitamos especificar manualmente las relaciones entre las tareas.
## Enumera todas las dependencias y el tipo de dependencias
## Dependencias y sus tipos:
## 1. Dependencia entre Kernel 1 y Kernel 2
* Buffer involucrado: A
* Acceso en Kernel 1: Escritura (write_only)
* Acceso en Kernel 2: Escritura (write_only)
* Tipo de dependencia: WAW (Write After Write)
Kernel 2 sobrescribe los valores en A después de que Kernel 1 los escribió.
## 2. Dependencia entre Kernel 2 y Tarea 4
* Buffer involucrado: A
* Acceso en Kernel 2: Escritura (write_only)
* Acceso en Tarea 4: Lectura (read_only)
* Tipo de dependencia: RAW (Read After Write)
Tarea 4 necesita leer los valores modificados en A por Kernel 2.
## 3. Dependencia entre Kernel 3 y Tarea 4
* Buffer involucrado: B
* Acceso en Kernel 3: Escritura (write_only)
* Acceso en Tarea 4: Lectura/Escritura (read_write)
* Tipo de dependencia: RAW (Read After Write)
Tarea 4 necesita los valores escritos en B por Kernel 3 antes de modificarlos.
## 4. Dependencia entre Tarea 4 y Host Accessor
* Buffer involucrado: B
* Acceso en Tarea 4: Lectura/Escritura (read_write)
* Acceso en Host Accessor: Lectura (read_only)
* Tipo de dependencia: RAW (Read After Write)
El host necesita leer los valores finales de B que fueron modificados por Tarea 4.

----

# Task 2
Code in [src/task2/buffer.cpp](../../src/task2/buffer.cpp) should represent the following flow:
1. Initialize buffer A
2. Add to each item in A the index of the iteration
3. Initialize buffer B the same way than A
4. Compute B as the result of B multiplied by A

## Check the result and show it below
**Answer here**

## Which abstraction is being used for data containers?
**Answer here**

## How is the DAG being built implicitly or explicitly?
**Answer here**

## Enumerate all dependencies and their types
**Answer here**
