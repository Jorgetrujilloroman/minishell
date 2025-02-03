/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:06:50 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/03 17:53:16 by jotrujil         ###   ########.fr       */
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

// Update the env vars after doing a cd builtin
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

/* Export and updates or adds environment variables in prompt->envp as needed */
static void	export_update_envp(t_prompt *p, char **argv)
{
	int	ij[2];
	int	pos;

	ij[0] = 1;
	while (argv[ij[0]])
	{
		pos = ms_var_in_envp(argv[ij[0]], p->envp, ij);
		if (pos == 1)
		{
			free(p->envp[ij[1]]);
			p->envp[ij[1]] = ft_strdup(argv[ij[0]]);
		}
		else if (!pos)
			p->envp = ms_add_end_env(p->envp, argv[ij[0]]);
		ij[0]++;
	}
}

int	ms_export(t_prompt *p)
{
	char	**argv;
	int		i;

	argv = ((t_command *)p->cmds->content)->full_cmd;
	if (ft_size_matrix(argv) == 1)
	{
		i = 0;
		while (p->envp[i])
			printf("declare -x %s\n", p->envp[i++]);
	}
	else
		export_update_envp(p, argv);
	return (0);
}
