#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int compartida = 0; // Variable global compartida entre los threads

// Función que ejecuta los THREADS de tipo 1
void *functionTipo1(void *i)
{
    printf("Thread1 instancia %d \n", *(int *)i); // Muestra el número de instancia del thread
    usleep(rand() / RAND_MAX); // Suspende el thread por un tiempo aleatorio entre 0 y 1 segundo
    compartida++; // Incrementa la variable global compartida
}

// Función que ejecuta los THREADS de tipo 2
void *functionTipo2(void *i)
{
    printf("Thread2 instancia %d \n", *(int *)i); // Muestra el número de instancia del thread
    usleep(rand() / RAND_MAX); // Suspende el thread por un tiempo aleatorio entre 0 y 1 segundo
    printf("El valor de la variable compartida es: %d \n", compartida); // Muestra el valor actual de la variable compartida
}

int main(int argc, char *argv[])
{
    // Verifica que se hayan pasado los argumentos N y M
    if (argc != 3) {
        printf("Uso: %s <N> <M>\n", argv[0]);
        return -1;
    }

    int N = atoi(argv[1]); // Número de threads tipo 1
    int M = atoi(argv[2]); // Número de threads tipo 2

    pthread_t idHiloTipo1[N], idHiloTipo2[M]; // Identificadores para los threads

    // Crear N threads de tipo 1
    for (int i = 0; i < N; i++)
    {
        int *variable = malloc(sizeof(int)); // Asigna memoria para el índice del thread
        *variable = i; // Almacena el número de instancia del thread
        pthread_create(&idHiloTipo1[i], NULL, functionTipo1, (void *)variable); // Crea el thread de tipo 1
    }

    // Crear M threads de tipo 2
    for (int i = 0; i < M; i++)
    {
        int *variable = malloc(sizeof(int)); // Asigna memoria para el índice del thread
        *variable = i; // Almacena el número de instancia del thread
        pthread_create(&idHiloTipo2[i], NULL, functionTipo2, (void *)variable); // Crea el thread de tipo 2
    }

    // Espera a que terminen todos los threads de tipo 1
    for (int i = 0; i < N; i++)
    {
        pthread_join(idHiloTipo1[i], NULL); // Espera la finalización del thread tipo 1
    }

    // Espera a que terminen todos los threads de tipo 2
    for (int i = 0; i < M; i++)
    {
        pthread_join(idHiloTipo2[i], NULL); // Espera la finalización del thread tipo 2
    }

    printf("Fin del programa\n"); 
    return 0;
}
