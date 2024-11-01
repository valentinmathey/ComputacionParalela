# 🚀 Computación Paralela en C

¡Bienvenido a este emocionante repositorio de computación paralela implementado en C! Aquí exploraremos el fascinante mundo de la programación concurrente utilizando threads y procesos.

## 📚 Contenido

Este repositorio contiene dos ejercicios principales que demuestran diferentes aspectos de la computación paralela:

### 🧵 Ejercicio Nº1 - Threads

Este programa crea N threads de tipo 1 y M threads de tipo 2, donde N y M son argumentos proporcionados al ejecutar el programa.

#### Funcionalidad:
- 🔵 **Thread tipo 1**: 
  -  Muestra el mensaje "Thread1 instancia x" (x es el número del thread).
  -  Se suspende por un tiempo aleatorio entre 0 y 1 segundo usando `usleep()`.
  -  Incrementa una variable global compartida.

- 🟢 **Thread tipo 2**: 
  -  Muestra el mensaje "Thread2 instancia y" (y es el número del thread).
  -  Se suspende por un tiempo aleatorio entre 0 y 1 segundo.
  -  Lee y muestra el valor de la variable global compartida.

#### 🔍 Detalles técnicos:
- Utiliza `pthread_create()` para crear los threads.
- Implementa `pthread_join()` para esperar la finalización de los threads.
- Usa `malloc()` para asignar memoria dinámica para los índices de los threads.

### 🖥️ Ejercicio Nº2 - Procesos

Este ejercicio es similar al primero, pero utiliza procesos en lugar de threads, demostrando las diferencias clave en la programación paralela.

#### Características:
-  Crea N procesos de tipo 1 y M procesos de tipo 2 usando `fork()`.
-  Implementa memoria compartida entre procesos con `shmget()`, `shmat()`, y `shmdt()`.
-  Utiliza `usleep()` para pausas aleatorias en los procesos.

#### 🔍 Detalles técnicos:
- Emplea `waitpid()` para esperar la finalización de los procesos hijos.
- Gestiona la memoria compartida con las funciones de System V IPC.
- Implementa manejo de errores para la creación de procesos y gestión de memoria compartida.

## 🛠️ Compilación y Ejecución

Para compilar y ejecutar los programas, sigue estas instrucciones:

```bash
# Compilar Ejercicio 1
gcc -o ejercicio1 ejercicio1.c -lpthread

# Ejecutar Ejercicio 1
./ejercicio1 N M

# Compilar Ejercicio 2
gcc -o ejercicio2 ejercicio2.c

# Ejecutar Ejercicio 2
./ejercicio2 N M
```

Reemplaza N y M con los números deseados de threads/procesos de tipo 1 y 2 respectivamente.

## 🧠 Análisis Comparativo

El uso de threads vs procesos revela diferencias importantes:

1.  **Espacio de Memoria**: 
   - Threads: Comparten el mismo espacio de memoria.
   - Procesos: Tienen espacios de memoria separados, requiriendo mecanismos de IPC.

2.  **Rendimiento**:
   - Threads: Generalmente más ligeros y rápidos de crear.
   - Procesos: Mayor overhead en creación y cambio de contexto.

3.  **Aislamiento**:
   - Threads: Menor aislamiento, un fallo puede afectar a otros threads.
   - Procesos: Mayor aislamiento, ofreciendo mejor estabilidad y seguridad.

4.  **Sincronización**:
   - Threads: Sincronización más sencilla con variables compartidas.
   - Procesos: Requiere mecanismos más complejos como semáforos o pipes.

##  Aprendizajes Clave

- Manejo de concurrencia en C.
- Diferencias prácticas entre threads y procesos.
- Uso de memoria compartida y sincronización.
- Gestión de recursos en programación paralela.

# 💻 Tech Stack:
<div align="center">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" height="40" alt="c logo" />
  <img width="12" />
</div>

# 🧑🏻‍💻 Autor:

Valentin Mathey | <a href="https://github.com/valentinmathey">@valentinmathey</a>

[![Discord](https://img.shields.io/badge/Discord-%237289DA.svg?logo=discord&logoColor=white)](https://discord.gg/valentinmathey) [![Facebook](https://img.shields.io/badge/Facebook-%231877F2.svg?logo=Facebook&logoColor=white)](https://facebook.com/ValentinEzequielMathey) [![Instagram](https://img.shields.io/badge/Instagram-%23E4405F.svg?logo=Instagram&logoColor=white)](https://instagram.com/valen.mathey/) [![LinkedIn](https://img.shields.io/badge/LinkedIn-%230077B5.svg?logo=linkedin&logoColor=white)](https://linkedin.com/in/valentin-mathey) [![X](https://img.shields.io/badge/X-%231DA1F2.svg?logo=X&logoColor=white)](https://twitter.com/valen_mathey)
