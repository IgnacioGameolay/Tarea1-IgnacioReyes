#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>

typdef struct{
  char horaRegistro;
  char nombre;
  int edad;
  char sintoma;
  char prioridad;
} tipoPaciente

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
  tipoPaciente *regPaciente;
  printf("Ingrese el nombre del paciente: ");
  scanf("%s", &regPaciente->nombre);
  printf("Ingrese la edad del paciente: ");
  scanf("%d", &regPaciente->edad);
  printf("Ingrese el sintoma del paciente: ");
  scanf("%s", &regPaciente->sintoma);
  printf("Ingrese la hora de registro: ");
  scanf("%s", &regPaciente->horaRegistro);
  //Asignacion default de prioridad
  regPaciente->prioridad = 'Baja';

  list_pusBack(pacientes, regPaciente);
}

void asignarPrioridad(List *pacientes) {
  char nombrePaciente[50];
  char proridadPaciente[50];
  printf("Asignar prioridad a paciente\n");
  scanf("%s", &nombrePaciente);
  scanf("%s", &proridadPaciente);
  
  tipoPaciente *pacienteAux = list_first(pacientes);
  
  while (pacienteAux->nombre !=nombre || pacienteAux != NULL){
    
    if (pacienteAux->nombre == nombrePaciente){
      pacienteAux->prioridad = proridadPaciente;
      
      if (pacienteAux->prioridad == 'Alta'){
        list_popCurrent(pacientes);
        list_pushBack(pacientes, pacienteAux);
      }
      else if (pacienteAux->prioridad == 'Baja'){
        list_popCurrent(pacientes);
        list_pushFront(pacientes, pacienteAux);
      }
      else{
        return;
      }
      
    }
    pacienteAux = list_next(pacientes);
  }

  printf("El paciente no existe en el registro!");
}

void mostrar_lista_pacientes(List *pacientes) {
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera: \n");
  // Aquí implementarías la lógica para recorrer y mostrar los pacientes
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
