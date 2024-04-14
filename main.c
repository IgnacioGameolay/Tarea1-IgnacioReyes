#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char horaRegistro[50];
  char nombre[50];
  int edad;
  char sintoma[50];
  char prioridad[50];
} tipoPaciente;

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
  scanf("%s", &regPaciente->sintoma);
  printf("Ingrese la hora de registro: ");
  scanf("%s", &regPaciente->horaRegistro);
  //Asignacion default de prioridad
  strcpy(regPaciente->prioridad, "Baja");

  list_pushBack(pacientes, regPaciente);
}

void asignarPrioridad(List *pacientes) {
  char nombrePaciente[50];
  char prioridadPaciente[50];
  
  printf("Asignar prioridad a paciente\n");
  printf("Ingrese el nombre del paciente: ");
  scanf("%s", nombrePaciente);
  printf("Ingrese la prioridad del paciente (Alta/Media/Baja): ");
  scanf("%s", prioridadPaciente);
  
  tipoPaciente *pacienteAux = list_first(pacientes);
  
  while (pacienteAux != NULL){
    
    if (strcasecmp (pacienteAux->nombre, nombrePaciente) == 0){
      //
      
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

int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

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
