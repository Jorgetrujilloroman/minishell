/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:35:57 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/27 13:16:35 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

/* Get pid to minishell process */
static void	ft_ms_get_pid(t_prompt *prompt)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_put_error("Minishell fork failed\n");
		ft_free_matrix(prompt->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(prompt->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid; // Posible restar 1 pero de momento no es necesario
}
/* Initialize the envs and create if doesn't exist */

static t_prompt	ms_init_envp(t_prompt prompt, char **argv)
{
	char	*str;
	char	*num;

	str = getcwd(NULL, 0);
	prompt.envp = ms_add_env("PWD", str, prompt.envp);
	free(str);
	str = ms_get_env("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envp = ms_add_env("SHLVL", num, prompt.envp);
	free(num);
	str = ms_get_env("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = ms_add_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp);
	free(str);
	str = ms_get_env("_", prompt.envp, 1);
	if (!str)
		prompt.envp = ms_add_env("_", argv[0], prompt.envp);
	free(str);
	return (prompt);
}

/* This function initializes the prompt, copies the environment variables
and gets the pid */

static t_prompt	ft_start_ms(char **argv, char **envp)
{
	t_prompt	prompt;

	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_status = 0;
	ft_ms_get_pid(&prompt);
	prompt = ms_init_envp(prompt, argv);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*output;
	char		*str;

	if (argc > 100)
		return (0);
	prompt = ft_start_ms(argv, envp);
	while (argc && argv)
	{
		signal(SIGINT, if_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = ms_get_prompt(prompt);
		if (str)
			output = readline(str);
		else
			output = readline("guest@minishell $ ");
		free(str);
		if (!parse_ms(output, &prompt))
			break ;
	}
}
