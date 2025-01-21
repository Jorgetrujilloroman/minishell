/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:50:01 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/21 23:42:12 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>

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
}	t_mini;

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

// PARSE
/* Check and add an env */
char	**ms_add_env(char *var, char *value, char **envp);
/* Take the value of the env that you want if it exists */
char	*ms_get_env(char *var, char **envp, int n);

#endif