/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:51:08 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/22 14:42:23 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	init_builtins(t_builtin *builtins)
{
	builtins[0] = (t_builtin){"cd", ms_cd};
	builtins[1] = (t_builtin){"export", ms_export}; //TODO: ms_ funcs
	builtins[2] = (t_builtin){"unset", ms_unset};
	builtins[3] = (t_builtin){NULL, NULL};
}

int	exec_builtin(t_prompt *prompt, t_list *cmd, int *terminate)
{
	char		**full_cmd;
	t_builtin	builtins[4];
	int			i;

	full_cmd = ((t_mini *)cmd->content)->full_cmd;
	i = 0;
	init_builtins(builtins);
	
}

int	builtin(t_prompt *prompt, t_list *cmd, int	*terminate)
{
	while (cmd)
	{
		if (!exec_builtin(prompt, cmd, terminate))
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status);
}
