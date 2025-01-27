/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:50:01 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/22 23:34:07 by davigome         ###   ########.fr       */
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

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}	t_command;

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
/* Count how many str there are in the output separated with c character */
int		ms_count_strs(const char *s, char *c, int i[2]);
/* Create a matrix from s separated with char set */
char	**ms_separate_matrix(char **aux, char const *s, char *set, int i[3]);

// PARSE
/* Add the new str in the end of the matrix */
char	**ms_add_end_env(char	**matrix, char *new);
/* Check and add an env */
char	**ms_add_env(char *var, char *value, char **envp);
/* Take the value of the env that you want if it exists */
char	*ms_get_env(char *var, char **envp, int n);
/* Get the prompt to show in the terminal */
char	*ms_get_prompt(t_prompt prompt);
/* Executes a command and saves output to string ending in \n */
void	ms_get_exec(char ***out, char *full, char *args, char **envp);
/* Execute the parse and executor */
void	*parse_ms(char *output, t_prompt *prompt);
/* Separate the arguments from output in a matrix */
char	**ms_trim(char const *s, char *set);
/* End the parse and exec the output */
void	*ms_parse_and_exec(char **output, t_prompt *prompt);

#endif