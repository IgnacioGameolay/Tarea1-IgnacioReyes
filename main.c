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

void registrar_paciente(List *pacientes) {
  printf("Registrar nuevo paciente\n");
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
  //getchar();
  
  //printf("Ingrese la hora de registro: ");
  //scanf("%s", &regPaciente->horaRegistro);
  
  //Asignamos la hora automaticamente segun la zona horaria del equipo que 
  //ejecute el programa
  regPaciente->horaRegistro = time(NULL);
  struct tm date = *localtime(&regPaciente->horaRegistro);
  printf("La hora de registro es: %02d:%02d\n", date.tm_hour,
    date.tm_min);
  
  //Asignacion default de prioridad
  strcpy(regPaciente->prioridad, "Baja");

  list_pushBack(pacientes, regPaciente);
}

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
    
    if (strcasecmp (pacienteAux->nombre, nombrePaciente) == 0){
      for (int i = 0; prioridadPaciente[i]; i++){
        prioridadPaciente[i] = tolower(prioridadPaciente[i]);
      }
      
      if (strcasecmp(prioridadPaciente, "alta") == 0){
        strcpy(pacienteAux->prioridad, "Alta");
        list_popCurrent(pacientes);
        list_pushBack(pacientes, pacienteAux);

      }
      else if (strcasecmp(prioridadPaciente, "baja") == 0){
        strcpy(pacienteAux->prioridad, "Baja");
        list_popCurrent(pacientes);
        list_pushFront(pacientes, pacienteAux);

      }
      else if (strcasecmp(prioridadPaciente, "media") == 0){

          strcpy(pacienteAux->prioridad, "Media");
        }
        else{
          printf("La prioridad ingresada no es válida\n");
        }

        return;
      }
    pacienteAux = list_next(pacientes);
  }
}

void mostrar_lista_pacientes(List *pacientes) {
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
  tipoPaciente *pacienteAux = list_first(pacientes);

  if (pacienteAux == NULL){
    printf("No hay pacientes en la lista de espera.\n");
    return;

  }
  
  while (pacienteAux != NULL) {
      printf("- Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %s\n",
      pacienteAux->nombre, pacienteAux->edad, 
      pacienteAux->sintoma, pacienteAux->prioridad);
    
      pacienteAux = list_next(pacientes);
  }
}
atender_siguiente_paciente(List *pacientes){
  printf("Atender al siguiente paciente\n");
  if(list_first(pacientes) == NULL){
    printf("No hay pacientes en la lista de espera");
    return;
  }

  tipoPaciente *pacienteAtendido = list_popFront(list_first(pacientes));
  
  printf("Atendiendo al siguiente paciente:\n");
  printf("- Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %s\n",
         pacienteAtendido->nombre, pacienteAtendido->edad,
         pacienteAtendido->sintoma, pacienteAtendido->prioridad);

  free(pacienteAtendido);
}

void mostrar_pacientes_prioridad(List *pacientes) {
  printf("Pacientes por prioridad:\n");
  
  tipoPaciente *pacienteAux = list_first(pacientes);
  if (pacienteAux == NULL){
    printf("No hay pacientes en la lista de espera.\n");
    return;

  }
  
  printf("Prioridad Alta:\n");
  while (pacienteAux != NULL && strcasecmp(pacienteAux->prioridad, "alta") == 0) {
    printf("- Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %s\n",
           pacienteAux->nombre, pacienteAux->edad,
           pacienteAux->sintoma, pacienteAux->prioridad);
    pacienteAux = list_next(pacientes);
  }

  printf("Prioridad Media:\n");
  while (pacienteAux != NULL && strcasecmp(pacienteAux->prioridad, "media") == 0) {
    printf("- Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %s\n",
           pacienteAux->nombre, pacienteAux->edad,
           pacienteAux->sintoma, pacienteAux->prioridad);
    pacienteAux = list_next(pacientes);
  }

  printf("Prioridad Baja:\n");
  while (pacienteAux != NULL && strcasecmp(pacienteAux->prioridad, "baja") == 0) {
    printf("- Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %s\n",
           pacienteAux->nombre, pacienteAux->edad,
           pacienteAux->sintoma, pacienteAux->prioridad);
    pacienteAux = list_next(pacientes);
  }
}

int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes
  
  listaPrioridadAlta = list_create();
  listaPrioridadMedia = list_create();
  listaPrioridadBaja = list_create();
  
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

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
      mostrar_pacientes_prioridad(pacientes);
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
