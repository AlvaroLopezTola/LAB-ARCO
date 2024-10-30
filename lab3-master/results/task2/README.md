# Tarea 2: Roofline
## Preguntas
1. Genera un roofline y analiza la información representada. Copia una captura del roofline en la respuesta
para apoyar tu análisis. Finalmente genera un snapshot con el nombre "task2" y añádelo a esta misma carpeta.
2. ¿Por qué está limitado el algoritmo? ¿Qué técnicas podríamos aplicar para mejorar el rendimiento?

## Respuestas
* Ordenador Intel-Edu
Antes de analizar la información del Roofline, queremos dejar claro de que se trata este modelo Roofline, el cual es capaz de determinar cuales son los potenciales cuellos de botella de nuestra aplicación o programa de manera gráfica.
Podríamos decir que se centra en dos partes o limites:
El primero es el rendimiento pico de nuestro computador, el cual podremos calcular como:

      PEAK FLOP = nº sockets * Core Frequency * nº cores * nº single precision element in SIMD register * (operation FMA)

  El otro limite viene determinado por el acceso a memoria, cual es el ancho de banda que tenemos.
  También puede calcularse teóricamente como:

      PEAK BW = nº sockets * Memory Frequency * Byte per channel * nº of mem channels

  Dicho esto, con nuestra herramienta advisor determinaremos los limites de nuestra aplicación o programa, y si vienen determinados por computo o memoria, 'Compute Bound' y 'Memory Bound'

  ![image](https://blog.kakaocdn.net/dn/p5j9v/btrJvSjDUQr/a2LSRTP3sKrFTK2iynAAJ0/img.png)
  
  Este modelo Roofline se centra también en el ancho de banda en memoria principal y en cachés de primer, segundo y tercer nivel, (parte izquierda de nuestro Roofline), y también vemos los limites asociados al pico por un procesador escalar (   (Scalar Add Peak), cuando le introducimos vectorización (Vector add peak) y también si hacemos uso de la función FMA o multiplicación y suma fusionada.

  A continuación mostramos una captura del roofline generado en nuestra aplicación:
  ![image](https://github.com/user-attachments/assets/8c150000-c1c4-47eb-bd44-66f9797ccd6f)
  Analizando el gráfico vemos que el rendimiento de nuestro programa es bajo, por debajo de la linea de caché nivel 3, esto nos sugiere que el rendimiento podría estár limitado por el acceso a memoria,
  ya que nuestro programa se encuentra en la zona 'Bound by memory and compute'.
  Efectivamente podemos ver como la mayor parte del tiempo la invertimos en accesos a memoria, con un 66%, frente a un 37% de computo.
  Para mejorar el rendimiento relacionado con la memoria podemos mejorar la eficiencia del almacenamiento en caché, mejorando el bucle escalar por medio de técnicas como la vectorización. 

----

# Task2: Roofline
1. Generate a roofline and analyze the information depicted. Copy a screenshot of the roofline in your response to support your analysis. Finally, create a snapshot with the name "task2" and add it to this same folder.
2. Why is the algorithm limited? What techniques could we apply to improve performance?
