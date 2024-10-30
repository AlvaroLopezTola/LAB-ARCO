# Tarea 1: Intel Advisor

## Preguntas
* En la vista de "Survey & Roofline" se hace referencia a Total time y self-time. ¿Qué diferencia hay entre ambas?
* Realiza un análisis de tipo Survey, accede a  la pestaña "Survey & Roofline" y haz una captura de la información (se usará
más tarde).
* Pulsa sobre roofline (dentro de Survey & Roofline) y comprueba que no aparece ningún gráfico. ¿A qué se debe?
* Haz un análisis de trip-counts y flop. ¿Qué información nueva aparece en la vista de survey? Haz una captura y comenta
los datos nuevos más relevantes.

## Respuestas
* 'Self time' hace referencia al tiempo que ejecuta activamente una función o bucle, sin incluir el tiempo de las funciones invocadas en el bucle o función.
Sin embargo 'Time total' es el tiempo que ejecuta activamente una función o bucle incluyendo el tiempo de las funciones invocadas.
* Puede ser por varias razones que no se nos muestre el gráfico, como por ejemplo; Datos perdidos o incompletos que se requieren para construir el gráfico,
una configuración incorrecta de nuestra herramienta Intel Advisor, problemas con el entorno de ejecución y los permisos.
* Tras hacer el nuevo ánalisis, hemos detectado nueva información en la vista survey, como son: la información relacionada con los 'Trip Counts', media, máximos, mínimos,
duración de la iteración; información del gráfico 'Roofline', nos dice que este bucle está principalmente vinculado a la memoria, el rendimiento de los bucles está limitado por el ancho de banda de la caché compartida y la DRAM.
Una recomendación que nos da Roofline es que ejecutemos para todos los niveles de memoria; y por último 'Tiempo de CPU Total', por iteración y por instancia. 

-----------------

# Task 1: Intel Advisor

## Questions
* Within the "Survey & Roofline" view, references are made to both Total time and Self-time. What is the difference between these two terms?
* Conduct a Survey analysis, navigate to the "Survey & Roofline" tab, and capture the information displayed (this will be used later).
* Click on the roofline within the "Survey & Roofline" and observe that no chart appears. What could be the reason for this absence?
* Perform an analysis focusing on trip-counts and FLOP (Floating Point Operations). What new information is presented in the survey view? Capture this information and discuss the most pertinent new data.
