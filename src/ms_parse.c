/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:16:44 by davigome          #+#    #+#             */
/*   Updated: 2025/01/22 21:22:39 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ms_trim(char const *s, char *set)
{
	char	**temp;
	int		strings;
	int		i[3];
	int		count[2];

	count[0] = 0;
	count[1] = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	strings = ms_count_strs(s, set, count);
	if (strings == -1)
		return (NULL);
	temp = malloc((strings + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	temp = ms_separate_matrix(temp, s, set, i);
	temp[strings] = NULL;
	return (temp);
}

void	*parse_ms(char *output, t_prompt *prompt)
{
	char		**aux;
//	t_command	*command;

	if (!output)
	{
		printf("exit\n");
		return (NULL);
	}
	if (output[0] != '\0')
		add_history(output);
	aux = ms_trim(output, " ");
/* 	int i = -1;
	while (aux[++i])
		ft_printf("%s\n", aux[i]); */
	return (prompt);
}
