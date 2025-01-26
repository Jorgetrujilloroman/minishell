/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:51:08 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/26 11:28:18 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

// Initialize all the custom builtins and assign their functions

static void	init_builtins(t_builtin *builtins)
{
	builtins[0] = (t_builtin){"cd", ms_cd};
	//builtins[1] = (t_builtin){"export", ms_export}; //TODO: ms_ funcs
	//builtins[2] = (t_builtin){"unset", ms_unset};
	builtins[3] = (t_builtin){NULL, NULL};
}

// Execute the builtins or exit the minishell if the exit builtin is executed

static int	exec_builtin(t_prompt *prompt, t_list *cmd, int *terminate)
{
	char		**full_cmd;
	t_builtin	builtins[4];
	int			i;

	full_cmd = ((t_command *)cmd->content)->full_cmd;
	i = 0;
	init_builtins(builtins);
	if (full_cmd && !ft_strncmp(*full_cmd, "exit", ft_strlen(*full_cmd))
		&& ft_strlen(*full_cmd) == 4)
	{
		g_status = ms_exit(cmd, terminate);
		return (1);
	}
	while (builtins[i].name)
	{
		if (full_cmd && !ft_strncmp(*full_cmd, builtins[i].name,
				ft_strlen(builtins[i].name)))
		{
			g_status = builtins[i].func(prompt);
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin(t_prompt *prompt, t_list *cmd, int	*terminate)
{
	while (cmd)
	{
		if (!exec_builtin(prompt, cmd, terminate))
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmd); //todo
		}
		cmd = cmd->next;
	}
	return (g_status);
}
