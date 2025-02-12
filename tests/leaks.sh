#!/bin/bash

# Ejecutar Valgrind con opciones de depuración completas
valgrind --leak-check=full --track-origins=yes ./bin/minishell
