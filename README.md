# Minishell

## Tan bonito como shell

42 Malaga Project with my colleague [@davigome](https://profile.intra.42.fr/users/davigome)

### Resumen
El proyecto **Minishell** tiene como objetivo crear un shell sencillo desde cero, similar a Bash. A través de este proyecto, aprenderás sobre procesos, manejo de file descriptors y otros conceptos esenciales del sistema operativo.

### Características principales
- **Interfaz interactiva:** Entrada de comandos con historial funcional.
- **Gestión de comandos:** Ejecución de programas basados en PATH o rutas específicas.
- **Redirecciones:** Soporte para `<`, `>`, `<<`, `>>`.
- **Pipes:** Comunicación entre comandos mediante `|`.
- **Variables de entorno:** Expansión de `$` y soporte para `$?`.
- **Señales:** Manejo de `ctrl-C`, `ctrl-D`, y `ctrl-\` como en Bash.
- **Built-ins implementados:** `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

### Requisitos técnicos
- Lenguaje: **C**.
- Funciones autorizadas: `readline`, `fork`, `execve`, `pipe`, entre otras.
- Gestión de memoria: **Sin leaks** (excepto los propios de `readline`).
