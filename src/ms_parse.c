/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:16:44 by davigome          #+#    #+#             */
/*   Updated: 2025/02/01 13:09:21 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

char	**ms_trim(char const *s, char *set)
{
	char	**temp;
	int		strings;
	int		i[3];
	int		count[2];

	count[0] = 0;
	count[1] = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	strings = ms_count_strs(s, set, count);
	if (strings == -1)
		return (NULL);
	temp = malloc((strings + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	temp = ms_separate_matrix(temp, s, set, i);
	temp[strings] = NULL;
	return (temp);
}

char	**ft_matrix_replace_in(char ***big, char **small, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_size_matrix(*big))
		return (NULL);
	aux = ft_calloc(ft_size_matrix(*big) + ft_size_matrix(small), sizeof(char *));
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	ft_free_matrix(*big);
	*big = aux;
	return (*big);
}

void	ms_clean(void *n)
{
	t_command	*node;

	node = n;
	ft_free_matrix(node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

t_list	*ms_break_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, ms_clean);
	ft_free_matrix(temp);
	ft_free_matrix(args);
	return (NULL);
}

int	ms_get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;
	
	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		ft_put_error("Minishell: No such file or directory\n");
	else if (!flags[0] && access(path, R_OK) == -1)
		ft_put_error("Minishell: permission denied: \n");
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		ft_put_error("Minishell: permission denied: \n");
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_command	*ms_out_2(t_command *node, char **args, int *i)
{
	char	*line;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	line = "Minishell : unexpected token 'newline'";
	++(*i);
	if (args[++(*i)])
		node->outfile = ms_get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(line, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_command	*ms_out_1(t_command *node, char **args, int *i)
{
	char	*line;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	line = "Minishell : unexpected token 'newline'";
	++(*i);
	if (args[++(*i)])
		node->outfile = ms_get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(line, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_command	*ms_in_1(t_command *node, char **args, int *i)
{
	char	*line;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	line = "Minishell : unexpected token 'newline'";
	++(*i);
	if (args[++(*i)])
		node->infile = ms_get_fd(node->infile, args[*i], flags);
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(line, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

char	*ms_get_str(char *str[2], size_t len, char *limit, char *warn)
{
	char	*temp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	ms_here_doc(char *str[2], char *aux[2])
{
	int	fd[2];
	
	g_status = 0;
	if (pipe(fd) == -1)
	{
		ft_put_error("Minishell: error creating pipe\n");
		return (-1);
	}
	str[1] = ms_get_str(str, 0, aux[0], aux[1]);
	write(fd[1], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[1]);
	if (g_status == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

t_command	*ms_in_2(t_command *node, char **args, int *i)
{
	char	*line;
	char	*aux[2];
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "Minishell: warning: here-document delimited by end-of-file";
	line = "Minishell : unexpected token 'newline'";
	++(*i);
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		node->infile = ms_here_doc(str, aux);
	}
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(line, 2);
			g_status = 2;
		}
	}
	return (node);
}

t_command	*ms_params(t_command *node, char **temp[2], int *i)
{
	if (temp[0][*i])
	{
		if (temp[0][*i][0] == '>' && temp[0][*i + 1] && temp[0][*i + 1][0] == '>')
			node = ms_out_2(node, temp[1], i);
		else if (temp[0][*i][0] == '>')
			node = ms_out_1(node, temp[1], i);
		else if (temp[0][*i][0] == '<' && temp[0][*i + 1] && \
			temp[0][*i + 1][0] == '<')
			node = ms_in_2(node, temp[1], i);
		else if (temp[0][*i][0] == '>')
			node = ms_in_1(node, temp[1], i);
		else if (temp[0][*i][0] != '|')
			node->full_cmd = ms_add_end_env(node->full_cmd, temp[1][*i]);
		else
		{
			ft_put_error("Minishell: syntax error near unexpected token `|'\n");
			*i = -2;
		}
		return (node);
	}
	ft_put_error("Minishell: syntax error near unexpected token `|'\n");
	*i = -2;
	return (node);
}

void	*ms_parse_and_exec(char **output, t_prompt *prompt)
{
/* 	int	is_exit;
	int	i;
	is_exit = 0; */
	
	output = ms_split_output(output, prompt);
	prompt->cmds = ms_nodes(output, -1);
	int i = -1;
	t_list *aux = prompt->cmds;
	while (prompt->cmds)
	{
		i = -1;
		while (ft_strlen(((t_command *)aux->content)->full_cmd[++i]) != 0)
			printf("%d%s\n", i,((t_command *)aux->content)->full_cmd[i]);
		aux = aux->next;
		if (!aux)
			break;
	}
	return (prompt);
}

void	*parse_ms(char *output, t_prompt *prompt)
{
	char		**aux;
//	t_command	*command;
	if (!output)
	{
		printf("exit\n");
		return (NULL);
	}
	if (output[0] != '\0')
		add_history(output);
	aux = ms_trim(output, " ");
	free(output);
	if (!aux)
		ft_put_error("Minishell could not trim the output");
	if (!aux)
		return ("");
	prompt = ms_parse_and_exec(aux, prompt);
/* 	int i = -1;
	while (aux[++i])
		ft_printf("%s\n", aux[i]); */
	return (prompt);
}
