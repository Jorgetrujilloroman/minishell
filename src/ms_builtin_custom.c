/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_custom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:06:50 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/26 12:02:28 by jotrujil         ###   ########.fr       */
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

static void	cd_update_env_vars(t_prompt *p, char *oldpwd)
{
	char	*newpwd;

	p->envp = ms_add_env("OLDPWD", oldpwd, p->envp);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup("");
	p->envp = ms_add_env("PWD", newpwd, p->envp);
	free(newpwd);
}

int	ms_cd(t_prompt *p)
{
	char	**full_cmd;
	char	*home;
	char	*old_pwd;

	g_status = 0;
	full_cmd = ((t_command *)p->cmds->content)->full_cmd;
	home = ms_get_env("HOME", p->envp, 4);
	if (!home)
		home = ft_strdup("");
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		old_pwd = ft_strdup("");
	if (!full_cmd[1] || ft_strncmp(full_cmd[1], "~", 2) == 0)
		g_status = chdir(home);
	else
		g_status = chdir(full_cmd[1]);
	if (g_status != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(full_cmd[1]);
	}
	else
		cd_update_env_vars(p, old_pwd);
	free(home);
	free(old_pwd);
}
