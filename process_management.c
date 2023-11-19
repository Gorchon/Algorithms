#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un proceso
typedef struct {
    int pid;  // ID del proceso
    int burst_time;  // Tiempo de ráfaga del proceso
} Process;

// Estructura para representar el bloque de control de procesos (PCB)
typedef struct {
    Process *process;  // Puntero al proceso asociado
    int remaining_time;  // Tiempo restante para la ejecución del proceso
} PCB;

// Función para inicializar un proceso
Process *createProcess(int pid, int burst_time) {
    Process *process = (Process *)malloc(sizeof(Process));
    process->pid = pid;
    process->burst_time = burst_time;
    return process;
}

// Función para inicializar un PCB
PCB *createPCB(Process *process) {
    PCB *pcb = (PCB *)malloc(sizeof(PCB));
    pcb->process = process;
    pcb->remaining_time = process->burst_time;
    return pcb;
}

// Función principal que simula la ejecución de procesos con un scheduler muy básico
void simulateExecution(Process *processes[], int num_processes) {
    // Crear PCBs para cada proceso
    PCB *pcbs[num_processes];
    for (int i = 0; i < num_processes; i++) {
        pcbs[i] = createPCB(processes[i]);
    }

    // Simulación del scheduler (Round Robin en este caso)
    int time_quantum = 2;  // Tiempo cuántico para Round Robin
    int total_remaining_time = 0;

    // Calcular el tiempo total restante para la ejecución de todos los procesos
    for (int i = 0; i < num_processes; i++) {
        total_remaining_time += processes[i]->burst_time;
    }

    // Simulación de la ejecución
    while (total_remaining_time > 0) {
        for (int i = 0; i < num_processes; i++) {
            if (pcbs[i]->remaining_time > 0) {
                printf("Ejecutando proceso %d\n", pcbs[i]->process->pid);
                
                // Reducir el tiempo restante al mínimo entre el tiempo cuántico y el tiempo restante
                int tiempo_ejecucion = (pcbs[i]->remaining_time < time_quantum) ? pcbs[i]->remaining_time : time_quantum;

                pcbs[i]->remaining_time -= tiempo_ejecucion;
                total_remaining_time -= tiempo_ejecucion;
                
                if (pcbs[i]->remaining_time <= 0) {
                    printf("Proceso %d completado\n", pcbs[i]->process->pid);
                }
            }
        }
    }
}

int main() {
    // Crear algunos procesos para la simulación
    int num_processes = 3;
    Process *process1 = createProcess(1, 5);
    Process *process2 = createProcess(2, 3);
    Process *process3 = createProcess(3, 7);

    Process *processes[] = {process1, process2, process3};

    // Simular la ejecución de los procesos
    simulateExecution(processes, num_processes);

    // Liberar memoria
    for (int i = 0; i < num_processes; i++) {
        free(processes[i]);
    }

    return 0;
}
