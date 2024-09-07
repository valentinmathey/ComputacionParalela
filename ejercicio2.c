#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>

// Función para los procesos de Tipo 1
void functionTipo1(int i, int *compartida)
{
    printf("Proceso Tipo 1 instancia %d\n", i);

    // Suspender el proceso por un tiempo aleatorio entre 0 y 1 segundo
    usleep(rand() % 1000000);

    // Incrementar la variable global compartida
    (*compartida)++;
}

// Función para los procesos de Tipo 2
void functionTipo2(int i, int *compartida)
{
    printf("Proceso Tipo 2 instancia %d\n", i);

    // Suspender el proceso por un tiempo aleatorio entre 0 y 1 segundo
    usleep(rand() % 1000000);

    // Leer y mostrar el valor de la variable compartida
    printf("El valor de la variable compartida es: %d\n", *compartida);
}

int main(int argc, char *argv[])
{
    // Validar la cantidad de argumentos
    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <N> <M>\n", argv[0]);
        return 1;
    }

    // Inicializar la semilla para los números aleatorios
    srand(time(NULL));

    // Convertir los argumentos de la línea de comandos a enteros
    int N = atoi(argv[1]); // Número de procesos tipo 1
    int M = atoi(argv[2]); // Número de procesos tipo 2

    // Crear un segmento de memoria compartida para la variable "compartida"
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("Error al crear la memoria compartida");
        exit(1);
    }

    // Adjuntar la memoria compartida al proceso
    int *compartida = (int *)shmat(shmid, NULL, 0);
    if (compartida == (int *)-1)
    {
        perror("Error al adjuntar la memoria compartida");
        exit(1);
    }

    // Inicializar la variable compartida en 0
    *compartida = 0;

    // Arreglos para almacenar los PID de los procesos
    pid_t pidsTipo1[N], pidsTipo2[M];

    // Crear N procesos de tipo 1
    for (int i = 0; i < N; i++)
    {
        pid_t pid = fork(); // Crear un proceso hijo
        if (pid == 0)       // Código del proceso hijo
        {
            functionTipo1(i, compartida);
            exit(0); // Terminar el proceso hijo
        }
        else if (pid > 0) // Código del proceso padre
        {
            pidsTipo1[i] = pid; // Almacenar el PID del proceso hijo
        }
        else // Error al crear el proceso
        {
            perror("Error al crear el proceso tipo 1");
            exit(1);
        }
    }

    // Crear M procesos de tipo 2
    for (int i = 0; i < M; i++)
    {
        pid_t pid = fork(); // Crear un proceso hijo
        if (pid == 0)       // Código del proceso hijo
        {
            functionTipo2(i, compartida);
            exit(0); // Terminar el proceso hijo
        }
        else if (pid > 0) // Código del proceso padre
        {
            pidsTipo2[i] = pid; // Almacenar el PID del proceso hijo
        }
        else // Error al crear el proceso
        {
            perror("Error al crear el proceso tipo 2");
            exit(1);
        }
    }

    // Esperar a que todos los procesos tipo 1 terminen
    int status;
    for (int i = 0; i < N; i++)
    {
        waitpid(pidsTipo1[i], &status, 0);
    }

    // Esperar a que todos los procesos tipo 2 terminen
    for (int i = 0; i < M; i++)
    {
        waitpid(pidsTipo2[i], &status, 0);
    }

    // Detachar la memoria compartida
    if (shmdt(compartida) == -1)
    {
        perror("Error al detachar la memoria compartida");
        exit(1);
    }

    // Eliminar la memoria compartida
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("Error al eliminar la memoria compartida");
        exit(1);
    }

    printf("Fin del programa\n");

    return 0;
}
