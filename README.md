# Minishell - 42 School Project

**Minishell** es un proyecto de la escuela 42 que consiste en desarrollar un intérprete de comandos simple, similar a `bash` o `zsh`. Este proyecto tiene como objetivo profundizar en el entendimiento de los procesos, la gestión de memoria, la manipulación de archivos y la implementación de un intérprete de comandos básico.

## Características Principales

- **Interpretación de comandos**: Soporta comandos básicos como `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`, etc.
- **Redirecciones y pipes**: Implementa redirecciones (`>`, `<`, `>>`) y pipes (`|`) para la comunicación entre procesos.
- **Manejo de señales**: Gestiona señales como `Ctrl-C` (SIGINT) y `Ctrl-\` (SIGQUIT) de manera similar a los shells modernos.
- **Variables de entorno**: Soporta la expansión de variables de entorno y la gestión de las mismas.
- **Prompt interactivo**: Muestra un prompt interactivo que permite al usuario introducir comandos.

## Tecnologías Utilizadas

- **Lenguaje**: C
- **Funciones de sistema**: `fork()`, `execve()`, `pipe()`, `dup2()`, `waitpid()`, etc.
- **Gestión de memoria**: Uso de `malloc()`, `free()`, y manejo de fugas de memoria con herramientas como `valgrind`.
- **Señales**: Uso de `signal()` o `sigaction()` para manejar señales.

## Aprendizaje y Desafíos

- **Procesos y ejecución**: Aprendizaje profundo sobre la creación y manejo de procesos en Unix.
- **Redirecciones y pipes**: Implementación de mecanismos para redirigir la entrada/salida y conectar comandos mediante pipes.
- **Manejo de errores**: Gestión robusta de errores y manejo de casos extremos.
- **Optimización**: Mejora del rendimiento y eficiencia del shell.

## Instalación y Uso

1. Clona el repositorio:
   ```bash
   git clone https://github.com/hinve/minishell.git
   ```
2. Compila el proyecto:
   ```bash
   make
   ```
3. Ejecuta el proyecto:
   ```bash
   ./minishell
   ```
