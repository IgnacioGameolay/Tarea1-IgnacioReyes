# Sistema de Gestión Hospitalaria

## Descripción del programa

Este programa cumple la funcionalidad de ser un Sistema de Gestión Hospitalaria, permitiendo así a los usuarios registrar pacientes, asignarles prioridades, ver la lista de espera, atender a los pacientes en función de su prioridad y mostrar pacientes de una determinada prioridad deseada. Está enfocado para facilitar la organización y atención de los pacientes en un entorno hospitalario, además de ser intuitivo y fácil de utilizar.

## Cómo compilar y ejecutar

Como uno de los objetivos del programa es ser fácil de utilizar y ser sumamente accesible, es recomendable utilizar webs como `Repl.it` para probar y ejecutar el sistema rápidamente. 
Para ello seguir los siguientes pasos:

1. Visitar [Repl.it](https://repl.it/).
2. Crear una nueva cuenta o iniciar sesión si ya tienes una.
3. Estando en el `dashboard`, seleccionar la opción "`New Repl`" y eligir "`Import from GitHub`".
4. Clonar el repositorio de GitHub: `https://github.com/IgnacioGameolay/Tarea1-IgnacioReyes.git`
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará el entorno de ejecución automáticamente.
6. Finalmente, presionar el botón "Run" para compilar y ejecutar la aplicación de manera automática. O bien, compilar el código manualmente utilizando: `gcc tdas/*.c main.c -Wno-unused-result -o main` , y posteriormente ejecutar con: `./main`



## Funcionalidades

### Funcionando correctamente:

- Registrar/Ingresar pacientes con sus datos personales y una prioridad por defecto.
- Asignar o modificar la prioridad de un paciente dando su nombre.
- Ver la lista de espera de pacientes de todas las prioridades, ordenada por prioridad y hora de registro.
- Atender al paciente siguiente e imprimiendo los datos del paciente anteriormente atendido, respetando el orden de prioridad para escoger el siguiente.
- Ver la lista de espera de pacientes de una prioridad en específico, ordenada hora de ingreso.
- Salir del sistema de gestión hospitalaria.

### Problemas conocidos:

- Al ingresar síntomas o nombres demasiado largos **podrían** llegar a haber problemas por posible falta de espacio en esos campos, pero esto serían muy raros casos, sin embargo existe esa posibilidad.
- Al ingresar una edad se podría ingresar una edad válida pero difícil de manejar/interpretar, es decir, en el caso de que sea un infante con menos de 1 año de nacido, en el sistema su edad se registraría como "0", siendo válida pero poco exacta.

### A mejorar:

- Permitir la edición de los datos de los pacientes en cualquier momento.
- Desarrollar e implementar una interfaz que facilite al usuario trabajar con el sistema más cómodamente que por consola.

## Ejemplo de uso
A continuación veremos un ejemplo de cómo utilizar el sistema para un paciente que acaba de llegar al hospital.
Por ello, al iniciar el sistema de gestión hospitalaria tendremos el siguiente menú con el cual interactuar:

``` 
========================================
     Sistema de Gestión Hospitalaria
========================================
1) Registrar paciente
2) Asignar prioridad a paciente
3) Mostrar lista de espera
4) Atender al siguiente paciente
5) Mostrar pacientes por prioridad
6) Salir
```
En este menú, podremos seleccionar una de las 6 opciones cuando se nos solicite `Ingrese su opción: `.

Los nombres de las opciones son bastante descriptivas (hacen lo que mencionan), pero de igual manera a continuación se mostrarán los pasos a seguir en el caso de la ruta de tratamiento completo de un paciente, desde que llega al hospital hasta que es atendido.


**Paso 1: Ingresar al nuevo paciente al sistema**

Empezamos por registrar al paciente que acaba de llegar al sistema, para ello seleccionamos la opción (1).
Luego de seleccionar la opción 1, tendremos que ingresar los datos del paciente: nombre, edad, síntoma. Y además, habrá que ingresar de manera separada la hora y minutos en la que se registró el paciente (en formato 23:59). A continuación un ejemplo:

```
========================================
Ingrese su opción: 1
========================================
========================================
Registrar nuevo paciente
========================================
Ingrese el nombre del paciente: Naotus Ironwill
Ingrese la edad del paciente: 19
Ingrese el síntoma del paciente: Tos seca y dolor de garganta
Ingrese la tiempo de registro del paciente (formato 24:59)... 
Ingrese una hora válida (desde 00 hasta 23): 14
Ingrese minutos válidos (desde 00 hasta 59): 23
========================================
```

El paciente ingresará al sistema con una prioridad inicial "Baja" que podrá ser modificada posteriormente de ser requerido por la opinión médica, y además se guarda la hora actual del registro. Como dato a destacar, el sistema detectará automáticamente la fecha y los segundos en los que se ingresó al usuario, esto para complementar las horas y minutos registradas.

**Paso 2: Asignar Prioridad a Paciente**

Una vez el paciente esté ingresado en el sistema (en caso de no encontrar al paciente el sistema dará el aviso correspondiente), y haya sido evaluado médicamente, de ser requerido se podría necesitar modificar su prioridad, para lo cual tendremos 3 opciones entre las cuales elegir como podemos ver a continuación:

```
========================================
Ingrese su opción: 2
========================================
========================================
Asignar prioridad a paciente
========================================
Ingrese el nombre del paciente: Naotus Ironwill
Ingrese la prioridad del paciente (Alta/Media/Baja): Media
========================================
Prioridad modificada a Media
========================================
```

Por lo visto en el ejemplo, el sistema actualizará la prioridad de Naotus Ironwill a "Media", ya que su caso requiere atención moderada, mas no inmediata.

**Paso 3: Mostrar lista de Espera**

El usuario también tiene la opción de revisar la lista de espera para ver todos los pacientes, con sus prioridades y datos personales, se mostrarán en orden de prioridad y hora de registro. 
En el caso de no haber pacientes el sistema el sistema dará el aviso correspondiente.

```
========================================
Ingrese su opción: 3
========================================
========================================
Pacientes en espera: 
========================================
========================================
Nombre: Naotus Ironwill
Edad: 19
Síntoma: Tos seca y dolor de garganta
Prioridad: Media
Hora de registro: Sat Apr 20 14:23:51 2024
======================================== 
```

Como se puede apreciar, en la lista se muestran los datos del paciente Naotus Ironwill, indicando que será el siguiente paciente a ser atendido, lo que nos lleva a la siguiente funcionalidad del programa. 

**Paso 4: Atender al siguiente paciente**

Al seleccionar esta opción se procederá a atender a Naotus Ironwill, y se mostrará además la prioridad del próximo paciente a ser atendido, seguido de la información del paciente Naotus Ironwill.

```
========================================
Ingrese su opción: 4
========================================
========================================
Atendiendo al siguiente paciente
========================================
El paciente siguiente será de prioridad media
========================================
===El ultimo paciente atendido fue===
Nombre: Naotus Ironwill
Edad: 19
Síntoma: Tos seca y dolor de garganta
Prioridad: Media
Hora de registro: Sat Apr 20 14:23:51 2024
========================================
```

Una vez el sistema muestre los datos del ultimo paciente atendido, en este caso Naotus Ironwill, se procederá a eliminarlo de la lista de espera y así, del sistema (pues ya ha sido atendido).

**Paso 5: Mostrar pacientes por prioridad**

Esta opción permite al usuario ver la lista de pacientes que tienen una prioridad específica. El usuario puede elegir entre las prioridades Alta, Media o Baja y el sistema mostrará todos los pacientes pertenecientes a esa prioridad y ordenados por hora de registro. A continuación, podemos ver uun ejemplo:


```
========================================
Ingrese su opción: 5

========================================
Pacientes por prioridad:
Ingrese el nivel de prioridad a mostrar (Alta/Media/Baja): baja
Pacientes con prioridad Baja:
========================================
Nombre: Patrick Holmes
Edad: 21
Síntoma: Cansancio general leve
Hora de registro: Sat Apr 20 14:35:00 2024
========================================
```


***Cualquier consulta o duda que pueda surgir, contactarse al siguiente mail: 
ireyestoledo8@gmail.com***
-
