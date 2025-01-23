/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_custom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:06:50 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/23 17:34:59 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ms_exit(t_list *cmd, int *terminate)
{
	t_command	*node;
	long		status;

	node = cmd->content;
	*terminate = !cmd->next;
	if (*terminate)
		ft_putstr_fd("exit\n", 2);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	status = ft_atoi(node->full_cmd[1]);
	if (status == 0 && node->full_cmd[1][0] != '0')
	{
		ft_putstr_fd("minishell: exit invalid argument: ", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (node->full_cmd[2])
	{
		*terminate = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (status);
}
