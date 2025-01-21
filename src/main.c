/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:35:57 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/21 13:56:36 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

/* Get pid to minishell process */
static void ft_ms_get_pid(t_prompt *prompt)
{
	pid_t pid;

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
	prompt->pid = pid - 1;
}

/* Initialize the envs and create if doesn't exist */

static t_prompt	ms_init_envp(t_prompt prompt, char *argv)
{
	char	*str;
	char	*num;

	str = getcwd(NULL,0);
	
}

/* This function initializes the prompt, copies the environment variables
and gets the pid */

static t_prompt	ft_start_shell(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_status = 0;
	ft_ms_get_pid(&prompt); //TODO: get minishell pid
	prompt = ms_init_envp(prompt, argv, str); //TODO: init_vars func
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*output;
	char		*str;

	prompt = ft_start_ms(argv, envp);
	while (argc && argv)
	{
		output = readline("anon@minishell $ ");
		if (output[0] != '\0')
			add_history(output);
		if (!output)
		{
			printf("exit\n");
			return (0);
		}
		(void)output;
		(void)envp;
	}
}
