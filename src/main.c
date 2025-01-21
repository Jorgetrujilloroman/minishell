/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:35:57 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/21 11:46:59 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

//Esta función inicializa el prompt, copia las variables de entorno

t_prompt	ft_start_shell(char **argv, char **envp)
{

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
