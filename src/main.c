/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:35:57 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/20 20:29:45 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*out;

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
