# Tarea 1
Familiarizarse con el uso de DPC.
En primer lugar copia el código de [src/task1/query.cpp](../../src/task1/query.cpp) en results/task1/src y compilalo con dpcpp.

## ¿Qué salida obtienes?
Para el ordenador de Eduardo obtenemos de resultado al ejecutar query:

    eduardo@eduardo-GF65-Thin-9SEXR:~/Downloads/lab6-main/src/task1$ ./query
    Device: Intel(R) Core(TM) i5-9300H CPU @ 2.40GHz

Para el ordenador de Álvaro obtenemos:

    alvaro@alvaro-ROG-Strix-G513RC-G513RC:~/Practica6/lab6-main/src/task1$ ./query
    Device: AMD Ryzen 7 6800HS with Radeon Graphics  


## ¿Qué tipos de selectores tenemos en DPC? ¿Podemos obtener una GPU? ¿Qué pasa si no existe el dispositivo requerido?
En DPC los selectores de dispositovos que tenemos nos permiten:
Ver cualquier dispositivo disponible: Dejando que el sistema decida.
Solo el dispositivo anfitrión (host): Ejecuta en el CPU principal.
Tipo específico de dispositivo: Por ejemplo, GPU, TPU.
Múltiples tipos de dispositivos: Ejemplo: GPU + FPGA.
Dispositivo específico: Como una GPU Intel o Nvidia

Es probable que alguno de los dispositivos que te permite seleccionar DPC no los tengas disponibles en tu PC. En ese caso habría que recurrir a buscarlos en otros equipos o emplear soluciones de hardware a través de la nube.
Nuestro ordenador al no tener GPU no la lista, nos retorna error 'PI_ERROR_DEVICE_NOT_FOUND'

## Prueba a obtener una GPU, si es posible en tu equipo, modificando el programa query.cpp en gpu_query.cpp
Modificando el programa para que nos liste nuestra GPU, nos retorna que no encuentra el dispositivo. 

## ¿Cómo has obtenido la GPU?


## Modifica el programa para obtener más datos del dispositivo.
**guarda el fichero en results/task1/src/more_query.cpp**

------
# Task 1
Get familiar with Intel DPC compiler.
First copy the code in [src/task1/query.cpp](../../src/task1/query.cpp) to results/task1/src and compile it with dpcpp.

## Which output do you obtain?
**Answer here**

## Which different types of selectors do we have in DPC? Can we obtain a GPU? What happens if the requested device doesn't exist?
**Asnwer here**

It is very likely that some of the devices that can be used with DPC are not available in your PC. In that case, we would look for them in other equipment or use hardware solutions through the cloud.

## Try to obtain a GPU, if it is available in your PC, by the query.cpp program into gpu_query.cpp
**store the resulting file in results/task1/src.**

## How did you obtained the GPU?
**Answer here**

## Modify the program to obtain more data from the device.
**store the resulting file in results/task1/src/more_query.cpp**
