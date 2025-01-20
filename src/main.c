/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:35:57 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/20 23:39:59 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

Esta función inicializa el prompt, copia las variables de entorno

t_prompt	ft_start_shell(char **argv, char **envp)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt	prompt;
	char		*imput;
	char		*str;
	
	prompt = ft_start_shell(argv, envp);
	while (argc && argv)
	{
		out = readline("anon@minishell $ ");
		if (out[0] != '\0')
			add_history(out);
		if (!out)
		{
			printf("exit\n");
			return (0);
		}
		(void)out;
		(void)envp;
	}
}
