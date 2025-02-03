/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_funcs_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:54 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/03 18:15:04 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ms_unset(t_prompt	*p)
{
	char	**argv;
	char	*aux;
	int		i;
	int		index;

	i = 1;
	argv = ((t_command *)p->cmds->content)->full_cmd;
	if (ft_size_matrix(argv) < 2)
		return (0);
	while (argv[i])
	{
		if (argv[i][ft_strlen(argv[i]) - 1] != '=')
		{
			aux = ft_strjoin(argv[i], "=");
			free(argv[i]);
			argv[i] = aux;
		}
		if (ms_var_in_envp(argv[i], p->envp, &index))
			ms_matrix_replace_n(&p->envp, NULL, index);
		i++;
	}
	return (0);
}
