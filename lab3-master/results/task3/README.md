# Tarea 3: Vectorización

## Preguntas
* Antes de comenzar la vectorización es importante conocer cuáles son las características de tu máquina ¿Cuáles son las extensiones multimedia SIMD con las que cuenta tu arquitectura?

* Observa el análisis que has realizado al programa complexmul.cpp. El propio Intel Advisor debe haber detectado que hay una infrautilización de instrucciones, esto está directamente relacionado con la vectorización, ya que lo que pretende reflejar es que tienes disponibles las extensiones SIMD y no las estás utilizando. Para vectorizar el algoritmo, el propio programa Intel Advisor te aconseja como hacerlo ¿Qué has hecho para vectorizar el bucle? Ten en cuenta que debes vectorizar lo máximo que te permita tu arquitectura.

* Una vez vectorizado el programa realiza un análisis y guárdalo con el nombre task3:
    * ¿Cual es el valor del campo Vector Length? ¿Es este el valor esperado teniendo en cuenta las extensiones que estás utilizando y que el programa utiliza floats de 32 bits? Tanto si la respuesta es afirmativa como negativa justifica cual es el valor que esperabas.
    * ¿Cuál ha sido la ganancia? Explica si es el resultado esperado, si no lo es, explica cuál crees que es la razón (Pista: Intel Advisor puede darte indicios de cuál es el problema).

-----

# Task 3: Vectorization

## Questions

* Before starting the vectorization process, it is crucial to understand the specifics of your machine. What are the SIMD multimedia extensions available on your architecture?
* Review the analysis you've conducted on the complexmul.cpp program. Intel Advisor should have identified an underutilization of instructions, directly related to vectorization, as it indicates that you have available SIMD extensions that are not being leveraged. To vectorize the algorithm, Intel Advisor itself provides guidance on how to proceed. What steps have you taken to vectorize the loop? Keep in mind that you should pursue maximum vectorization that your architecture permits.

* After vectorizing the program, conduct an analysis and save it under the name "task3":
   * What is the value indicated in the 'Vector Length' field? Considering the extensions you're utilizing and the program's use of 32-bit floats, is this the expected value? Justify the anticipated value, whether the actual value aligns with your expectations or not.
   * What was the extent of the improvement? Discuss whether this is the outcome you predicted; if not, explain what you believe might be the reason (Hint: Intel Advisor can offer insights into what the issue might be).
