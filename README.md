## Minishell

## As pretty as shell

42 Malaga Project with my colleague [@davigome](https://profile.intra.42.fr/users/davigome)

### Summary
The **Minishell** project aims to create a simple shell from scratch, similar to Bash. Through this project, you will learn about processes, file descriptor handling and other essential operating system concepts.

### Main features
- **Interactive interface:** Command entry with functional history.
- **Command management:** Execution of programs based on PATH or specific paths.
- **Redirections:** Support for `<`, `>`, `<<`, `>>`.
- **Pipes:** Communication between commands using `|`.
- **Environment variables:** Expansion of `$` and support for `$`.
- **Signals:** Handling of `ctrl-C`, `ctrl-D`, and `ctrl-` as in Bash.
- **Built-ins implemented:** `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

### Technical requirements
- Language: **C**.
- Authorized functions: `readline`, `fork`, `execve`, `pipe`, among others.
- Memory management: **No leaks** (except for `readline`).
