/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:50:01 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/26 19:50:21 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>

//COLORS
# define DEFAULT "\001\033[0;39m\002"
# define ORANGE "\001\033[1;38;5;208m\002"
# define GREEN  "\001\033[1;32m\002"
# define GREEN_OLIVE "\001\033[1;38;5;100m\002" // Definir el color verde oliva

typedef struct s_prompt
{
	t_list	*cmds;
	pid_t	pid;
	char	**envp;
}	t_prompt;

typedef struct s_command
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}	t_command;

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_prompt *);
}	t_builtin;

// UTILS

/* Count how many strings there are in the matrix */
int		ft_size_matrix(char **matrix);
/* Copy matrix and allocate memory */
char	**ft_dup_matrix(char **envp);
void	ft_free_matrix(char **matrix);
/* Write the error in the error console */
void	ft_put_error(char *s);
/* Return the position where the character sent is found */
int		ms_strchr_pos(char *s, int c);
/* Handle when the input is a Ctrl+C signal */
void	if_sigint(int sig);
/* Make substr from set to the next set string*/
char	*strtrim(char const *s1, char const *set);
/* Returns the index of an specific character inside a Sring.
Returns -1 if not exist. */
int		ft_strchr_i(const char *s, int c);

// PARSE

/* Add the new str in the end of the matrix */
char	**ms_add_end_env(char	**matrix, char *new);
/* Add or update an environment variable if already exists */
char	**ms_add_env(char *var, char *value, char **envp);
/* Take the value of the env that you want if it exists */
char	*ms_get_env(char *var, char **envp, int n);
/* Get the prompt to show in the terminal */
char	*ms_get_prompt(t_prompt prompt);
/* Executes a command and saves output to string ending in \n */
void	ms_get_exec(char ***out, char *full, char *args, char **envp);
/* Execute the parse and executor */
void	*parse_ms(char *output, t_prompt *prompt);
/* Checks if an environment variable exists in envp */
int		var_in_envp(char **argv, char **envp, int ij[2]);

// EXECUTE

/* Runs over cmds and execute builtins. Execute the cmd if it isn't a builtin */
int		builtin(t_prompt *prompt, t_list *cmd, int	*terminate);
/* Handling the exit of the program with a status code based on the arguments */
int		ms_exit(t_list *cmd, int *terminate);
/* Changes the currend working directory and update the related env vars */
int		ms_cd(t_prompt *p);
/* Minishell implementation of export builtin */
int		ms_export(t_prompt *p);
#endif