#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAXCHAR 99

//Definir structs de datos para los pacientes
typedef struct{
  char nombre[MAXCHAR];
  int edad;
  char sintoma[MAXCHAR];
  time_t horaRegistro;
  char prioridad[50];
} tipoPaciente;

//Crear las listas por prioridad globales
List *listaPrioridadAlta;
List *listaPrioridadMedia;
List *listaPrioridadBaja;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

//Funcion comparacion para las horas de registros entre pacientes
int compararPorHoraRegistro(void *a, void *b) {
    tipoPaciente *pacienteA = (tipoPaciente *)a;
    tipoPaciente *pacienteB = (tipoPaciente *)b;

    // Ordenar en orden ascendente por hora de registro
    if (pacienteA->horaRegistro < pacienteB->horaRegistro) return -1;
    if (pacienteA->horaRegistro > pacienteB->horaRegistro) return 1;
    return 0;
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

//Funcion auxiliar para verificar si una cadena es numerica o no.
int esNumero(const char *cadena) {
    while (*cadena) {
        if (!isdigit(*cadena)) {
            return 0;
        }
        cadena++;
    }
    return 1;
}

//Funcion para registrar pacientes
void registrar_paciente(List *pacientes) {
  printf("========================================\n");
  printf("Registrar nuevo paciente\n");
  printf("========================================\n");
  
  // Aquí implementarías la lógica para registrar un nuevo paciente
  tipoPaciente *regPaciente = malloc(sizeof(tipoPaciente));
  if (regPaciente == NULL){
    printf("Error al asignar memoria para el nuevo paciente");
    return;
  }

  //Asignacioon nombre ak paciente
  printf("Ingrese el nombre del paciente: ");
  scanf(" %[^\n]", &regPaciente->nombre);

  //Verificacion de edad valida
  char edadAuxSTR[100];
  int edadAuxINT = -1;
  do {
    printf("Ingrese la edad del paciente: ");
    scanf(" %s[^\n]", edadAuxSTR);
    
    if (!esNumero(edadAuxSTR)){
      printf("La edad ingresada no es valida, intente nuevamente... \n");
      continue; //Si la edad ingresada no es valida se reintenta
    }
    edadAuxINT = atoi(edadAuxSTR);
  }
  while(!(edadAuxINT >= 0));
  regPaciente->edad = edadAuxINT; // Aignacion edad del paciente
  
  
  printf("Ingrese el sintoma del paciente: ");
  scanf(" %[^\n]", &regPaciente->sintoma);

  //Verificacion de hora de ingreso valida
  int hora;
  int minuto;
  do {
    printf("Ingrese la tiempo de registro del paciente (formato 24:59)... \n");
    printf("Ingrese una hora válida (desde 00 hasta 23): ");
    scanf(" %d", &hora);
    printf("Ingrese minutos válidos (desde 00 hasta 59): ");
    scanf(" %d", &minuto);
    if ((hora < 0) || (hora > 23) || (minuto < 0) || (minuto > 59)) {
        printf("La hora o los minutos ingresados no son válidos, intente nuevamente... \n");
        continue;
    } 
    break;
  } while(1);
  // Asignacion hora de registro del paciente
  regPaciente->horaRegistro = time(NULL);
  struct tm date = *localtime(&regPaciente->horaRegistro);
  date.tm_hour = hora;
  date.tm_min = minuto;
  regPaciente->horaRegistro = mktime(&date);

  //Asignacion default de prioridad
  strcpy(regPaciente->prioridad, "Baja");
  list_sortedInsert(listaPrioridadBaja, regPaciente, compararPorHoraRegistro);
  list_sortedInsert(pacientes, regPaciente, compararPorHoraRegistro);
  printf("========================================\n");
}

//Funcion para modificar la prioridad de un paciente
void asignarPrioridad(List *pacientes) {
  char nombrePaciente[MAXCHAR];
  char prioridadPaciente[50];

  printf("Asignar prioridad a paciente\n");
  printf("Ingrese el nombre del paciente: ");
  scanf(" %[^\n]", nombrePaciente);
  printf("Ingrese la prioridad del paciente (Alta/Media/Baja): ");
  scanf(" %s", prioridadPaciente);

  tipoPaciente *pacienteAux = list_first(pacientes);

  while (pacienteAux != NULL){

    //Busco por nombre
    if (strcasecmp (pacienteAux->nombre, nombrePaciente) == 0){

      //Validar prioridad ingresada
      if (strcasecmp(prioridadPaciente, "alta") != 0 &&
          strcasecmp(prioridadPaciente, "media") != 0 &&
          strcasecmp(prioridadPaciente, "baja") != 0) {
        printf("La prioridad ingresada no es válida\n");
        return;
      }

      //Validar prioridad ingresada
      if (strcasecmp(prioridadPaciente, pacienteAux->prioridad) == 0){
        printf("El paciente ya pertenece a esta prioridad\n");
        return;
      }

      
      //Si la nueva prioridad es alta
      if (strcasecmp(prioridadPaciente, "alta") == 0){
        
        //Eliminar de la lista de prioridad anterior del paciente
        if (strcasecmp(pacienteAux->prioridad, "media") == 0){
          list_popCurrent(listaPrioridadMedia);

        } else if (strcasecmp(pacienteAux->prioridad, "baja") == 0){
          list_popCurrent(listaPrioridadBaja);
        }
        //Asignar nueva prioridad
        strcpy(pacienteAux->prioridad, "Alta");
        list_sortedInsert(listaPrioridadAlta, pacienteAux, compararPorHoraRegistro);

        
        
        printf("Prioridad modificada a Alta\n");
      }
        
      //Si la nueva prioridad es media
      else if (strcasecmp(prioridadPaciente, "media") == 0){

        //Eliminar de la lista de prioridad anterior del paciente
        if (strcasecmp(pacienteAux->prioridad, "alta") == 0){
          list_popCurrent(listaPrioridadAlta);

        } else if (strcasecmp(pacienteAux->prioridad, "baja") == 0){
          list_popCurrent(listaPrioridadBaja);
        }
        
        //Asignar nueva prioridad
        strcpy(pacienteAux->prioridad, "Media");
        list_sortedInsert(listaPrioridadMedia, pacienteAux, compararPorHoraRegistro);
        
        
        
        printf("Prioridad modificada a Media\n");
      }
        
      //Si la nueva prioridad es baja
      else if (strcasecmp(prioridadPaciente, "baja") == 0){

        //Eliminar de la lista de prioridad anterior del paciente
        if (strcasecmp(pacienteAux->prioridad, "alta") == 0){
          list_popCurrent(listaPrioridadAlta);

        } else if (strcasecmp(pacienteAux->prioridad, "media") == 0){
          list_popCurrent(listaPrioridadMedia);
        }

        //Asignar nueva prioridad
        strcpy(pacienteAux->prioridad, "Baja");
        list_sortedInsert(listaPrioridadBaja, pacienteAux, compararPorHoraRegistro);
        
        
        printf("Prioridad modificada a Baja\n");
      }

      //Si la prioridad no es ninguna de las anteriores
      else{
        printf("La prioridad ingresada no es válida\n");
        printf("========================================\n");
      }

        return; //Termino la funcion cuando modifico la prioridad
      }
    
    pacienteAux = list_next(pacientes); //Paso al sig. paciente hasta dar con el que busco
  }
  printf("========================================\n");
  printf("No ha encontrado el paciente ingresado\n");
  printf("========================================\n");
}

//Funcion para mostrar a todos los pacientes
void mostrar_lista_pacientes(List *pacientes) {
  printf("========================================\n");
  printf("Pacientes en espera: \n");
  printf("========================================\n");

  // Verificar si todas las listas están vacías
  if (list_first(listaPrioridadAlta) == NULL &&
      list_first(listaPrioridadMedia) == NULL &&
      list_first(listaPrioridadBaja) == NULL) {
    printf("No hay pacientes en la lista de espera.\n");
    printf("========================================\n");
  }
  
  tipoPaciente *pacienteAux = NULL;
  
  // Mostrar pacientes de prioridad ALta
  pacienteAux = list_first(listaPrioridadAlta);
  while (pacienteAux != NULL) {
    printf("========================================\n");
    printf("Nombre: %s\n", pacienteAux->nombre);
    printf("Edad: %d\n", pacienteAux->edad);
    printf("Síntoma: %s\n", pacienteAux->sintoma);
    printf("Prioridad: %s\n", pacienteAux->prioridad);
    printf("Hora de registro: %s", asctime(localtime(&pacienteAux->horaRegistro)));
    printf("========================================\n");

    pacienteAux = list_next(listaPrioridadAlta);
  }

  // Mostrar pacientes de prioridad Mdia
  pacienteAux = list_first(listaPrioridadMedia);
  while (pacienteAux != NULL) {
    printf("========================================\n");
    printf("Nombre: %s\n", pacienteAux->nombre);
    printf("Edad: %d\n", pacienteAux->edad);
    printf("Síntoma: %s\n", pacienteAux->sintoma);
    printf("Prioridad: %s\n", pacienteAux->prioridad);
    printf("Hora de registro: %s", asctime(localtime(&pacienteAux->horaRegistro)));
    printf("========================================\n");

    pacienteAux = list_next(listaPrioridadMedia);
  }

  // Mostrar pacientes de prioridad Baja
  pacienteAux = list_first(listaPrioridadBaja);
  while (pacienteAux != NULL) {
    printf("========================================\n");
    printf("Nombre: %s\n", pacienteAux->nombre);
    printf("Edad: %d\n", pacienteAux->edad);
    printf("Síntoma: %s\n", pacienteAux->sintoma);
    printf("Prioridad: %s\n", pacienteAux->prioridad);
    printf("Hora de registro: %s", asctime(localtime(&pacienteAux->horaRegistro)));
    printf("========================================\n");

    pacienteAux = list_next(listaPrioridadBaja);
  }
  free(pacienteAux);
}

//Funcion para atender al paciente siguiente segun prioridad y hora de llegada
void atender_siguiente_paciente(){
  printf("========================================\n");
  printf("Atendiendo al siguiente paciente\n");
  printf("========================================\n");
  tipoPaciente *pacienteAtendido = NULL;

  //Revisar si hay pacientes en la lista de prioridad alta
  if (list_first(listaPrioridadAlta) != NULL) {
    printf("El paciente siguiente será de prioridad alta\n");
    pacienteAtendido = list_popBack(listaPrioridadAlta);
  }
  //Revisar si hay pacientes en la lista de prioridad media
  else if (list_first(listaPrioridadMedia) != NULL) {
    printf("El paciente siguiente será de prioridad media\n");
    pacienteAtendido = list_popBack(listaPrioridadMedia);
  }
  //Revisar si hay pacientes en la lista de prioridad baja
  else if (list_first(listaPrioridadBaja) != NULL) {
    printf("-El paciente siguiente será de prioridad baja-\n");
    pacienteAtendido = list_popBack(listaPrioridadBaja);
  }

  // Si existe un paciente atendido, se muestra su informacion
  if (pacienteAtendido != NULL) {
    printf("========================================\n");
    printf("===El ultimo paciente atendido fue===\n");
    printf("Nombre: %s\n", pacienteAtendido->nombre);
    printf("Edad: %d\n", pacienteAtendido->edad);
    printf("Síntoma: %s\n", pacienteAtendido->sintoma);
    printf("Prioridad: %s\n", pacienteAtendido->prioridad);
    printf("Hora de registro: %s", asctime(localtime(&pacienteAtendido->horaRegistro)));
    printf("========================================\n");

    free(pacienteAtendido);
  } else {
    printf("No hay pacientes en espera\n");
    printf("========================================\n");
  }
}

//Funcion para mostrar los pacientes por prioridad
void mostrar_pacientes_prioridad() {
  printf("Pacientes por prioridad:\n");
  char prioridadPaciente[50];
  List *listaPrioridad = NULL; //lista auxiliar referencial la lista de prioridad a utilizar
  
  printf("Ingrese el nivel de prioridad a mostrar (Alta/Media/Baja): ");
  scanf("%s", prioridadPaciente);

  //Validar prioridad ingresada
  if (strcasecmp(prioridadPaciente, "alta") != 0 &&
      strcasecmp(prioridadPaciente, "media") != 0 &&
      strcasecmp(prioridadPaciente, "baja") != 0) {
    printf("La prioridad ingresada no es válida\n");
    return;
  }

  //Setear la lista de priordad que vamos a utilizar
  if (strcasecmp(prioridadPaciente, "Alta") == 0){
    listaPrioridad = listaPrioridadAlta;
  } else if (strcasecmp(prioridadPaciente, "Media") == 0){
    listaPrioridad = listaPrioridadMedia;
  } else {
    listaPrioridad = listaPrioridadBaja;
  }
    
  tipoPaciente *pacienteAux = list_first(listaPrioridad);
  if (pacienteAux == NULL){
    printf("No hay pacientes en la lista de espera ingresada.\n");
    return;
  }
  
  printf("Pacientes con prioridad %s:\n", prioridadPaciente);
  while (pacienteAux != NULL){
    
    // Mostrar info del paciente del nivel de prioridad ingresado
    printf("========================================\n");
    printf("Nombre: %s\n", pacienteAux->nombre);
    printf("Edad: %d\n", pacienteAux->edad);
    printf("Síntoma: %s\n", pacienteAux->sintoma);
    printf("Hora de registro: %s", asctime(localtime(&pacienteAux->horaRegistro)));
    printf("========================================\n");

    pacienteAux = list_next(listaPrioridad);
  }
}

//FUncion principal
int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes
  
  listaPrioridadAlta = list_create();
  listaPrioridadMedia = list_create();
  listaPrioridadBaja = list_create();
  
  do {
    mostrarMenuPrincipal();
    printf("========================================\n");
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior
    printf("\n========================================\n");
    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      // Lógica para asignar prioridad
      asignarPrioridad(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      atender_siguiente_paciente(pacientes);
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
      mostrar_pacientes_prioridad();
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}
