#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXCHAR 99

//Definir structs de datos para los pacientes
typedef struct{
  char nombre[MAXCHAR];
  int edad;
  char sintoma[MAXCHAR];
  //char horaRegistro[50];
  time_t horaRegistro;
  char prioridad[50];
} tipoPaciente;

//Crear las listas por prioridad
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

  printf("Ingrese el nombre del paciente: ");
  scanf("%s", &regPaciente->nombre);

  printf("Ingrese la edad del paciente: ");
  scanf("%d", &regPaciente->edad);

  printf("Ingrese el sintoma del paciente: ");
  scanf("%s[\n]", &regPaciente->sintoma);

  //Asignamos la hora automaticamente segun la zona horaria del equipo que 
  //ejecute el programa
  
  regPaciente->horaRegistro = time(NULL);
  struct tm date = *localtime(&regPaciente->horaRegistro);
  printf("La hora de registro es: %02d:%02d\n", date.tm_hour,
    date.tm_min);
  
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
  scanf("%s", nombrePaciente);
  printf("Ingrese la prioridad del paciente (Alta/Media/Baja): ");
  scanf("%s", prioridadPaciente);

  tipoPaciente *pacienteAux = list_first(pacientes);

  while (pacienteAux != NULL){

    //Busco por nombre
    if (strcasecmp (pacienteAux->nombre, nombrePaciente) == 0){

      //Si la prioridad es alta
      if (strcasecmp(prioridadPaciente, "alta") == 0){
        strcpy(pacienteAux->prioridad, "Alta");
        list_sortedInsert(listaPrioridadAlta, pacienteAux, compararPorHoraRegistro);
        printf("Prioridad modificada a Alta\n");
      }
        
      //Si la prioridad es baja
      else if (strcasecmp(prioridadPaciente, "baja") == 0){
        list_sortedInsert(listaPrioridadBaja, pacienteAux, compararPorHoraRegistro);
        printf("Prioridad modificada a Baja\n");
      }
        
      //Si la prioridad es media
      else if (strcasecmp(prioridadPaciente, "media") == 0){
          strcpy(pacienteAux->prioridad, "Media");
          list_sortedInsert(listaPrioridadMedia, pacienteAux, compararPorHoraRegistro);
          printf("Prioridad modificada a Media\n");
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
    pacienteAtendido = list_popFront(listaPrioridadAlta);
  }
  //Revisar si hay pacientes en la lista de prioridad media
  else if (list_first(listaPrioridadMedia) != NULL) {
    printf("El paciente siguiente será de prioridad media\n");
    pacienteAtendido = list_popFront(listaPrioridadMedia);
  }
  //Revisar si hay pacientes en la lista de prioridad baja
  else if (list_first(listaPrioridadBaja) != NULL) {
    printf("-El paciente siguiente será de prioridad baja-\n");
    pacienteAtendido = list_popFront(listaPrioridadBaja);
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
  List *listaPrioridad = NULL;
  
  printf("Ingrese el nivel de prioridad a mostrar (Alta/Media/Baja): ");
  scanf("%s", prioridadPaciente);

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
      printf("Nombre: %s\n", pacienteAux->nombre);
      printf("Edad: %d\n", pacienteAux->edad);
      printf("Síntoma: %s\n", pacienteAux->sintoma);
      printf("Hora de registro: %s", asctime(localtime(&pacienteAux->horaRegistro)));
      printf("\n");

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
    printf("========================================\n");
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
