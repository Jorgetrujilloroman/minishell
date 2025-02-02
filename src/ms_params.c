/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:56:25 by davigome          #+#    #+#             */
/*   Updated: 2025/02/02 08:22:23 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

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
