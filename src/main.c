/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:35:57 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/21 11:56:00 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

/* This function initializes the prompt, copies the environment variables
and gets the pid */

static t_prompt	ft_start_shell(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp); //TODO ft_dup_matrix
	g_status = 0;
	ms_get_pid(&prompt); //TODO: get minishell pid
	prompt = init_vars(prompt, argv, str); //TODO: init_vars func
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*output;
	char		*str;

	prompt = ft_start_shell(argv, envp);
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
