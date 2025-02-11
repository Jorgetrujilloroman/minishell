/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_funcs_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:54 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/11 15:35:50 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

/* Count the times that a char is in a str */
static int	ft_countchar(char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

int	ms_echo(t_list *cmd)
{
	int			newline;
	int			i[2];
	char		**argv;
	t_command	*command;

	i[0] = 0;
	i[1] = 0;
	newline = 1;
	command = cmd->content;
	argv = command->full_cmd;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && \
			(ft_countchar(argv[i[0]], 'n') == \
			(int)(ft_strlen(argv[i[0]]) - 1)))
			newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}

int	ms_pwd(void)
{
	char	*buf;
	
	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	ms_unset(t_prompt	*p)
{
	char	**argv;
	char	*aux;
	int		i;
	int		index[2];

	i = 1;
	argv = ((t_command *)p->cmds->content)->full_cmd;
	if (ft_size_matrix(argv) < 2)
		return (0);
	while (argv[i])
	{
		if (argv[i][ft_strlen(argv[i]) - 1] != '=')
		{
			aux = ft_strjoin(argv[i], "=");
			free(argv[i]);
			argv[i] = aux;
		}
		if (ms_var_in_envp(argv[i], p->envp, index))
			ms_matrix_replace_n(&p->envp, NULL, index[1]);
		i++;
	}
	return (0);
}
