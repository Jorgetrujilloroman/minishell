#!/bin/bash

# Running Valgrind with full debugging options
valgrind --leak-check=full --track-origins=yes ./bin/minishell
