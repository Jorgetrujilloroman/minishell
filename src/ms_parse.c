/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:16:44 by davigome          #+#    #+#             */
/*   Updated: 2025/01/27 10:31:18 by davigome         ###   ########.fr       */
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



char	*ms_vars(char *str, int i, int j[2], t_prompt *prompt)
{
	j[0] = 0;
	j[1] = 0;
	
	while (str && str[++i])
	{
		if (str [i] == '\'' && j[1] == 0)
		{
			++j[0];
			j[0] = j[0] % 2;
		}
		if (str [i] == '\"' && j[0] == 0)
		{
			++j[1];
			j[1] = j[1] % 2;
		}
		if (str[i] == '$')
			return (ms_vars(ms_get_sub_var(str, ++i, prompt), -1, j, prompt));
	}
	return (str);
}

char	**ms_split_output(char **output, t_prompt **prompt)
{
	char	**split_out;
	int		i;
	int		j[2];

	i = -1;
	while (output && output[++i])
	{
		output[i] = ms_vars(output[i], -1 , j, prompt);
	}
	return (output);
}

void	*ms_parse_and_exec(char **output, t_prompt *prompt)
{
	int	is_exit;
	int	i;
	is_exit = 0;
	
	output = ms_split_output(output, prompt);
	aux = ms_clean_arg(aux); 
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
	free(output);
	if (!aux)
		ft_put_error("Minishell could not trim the output");
	if (!aux)
		return ("");
	prompt = ms_parse_and_exec(aux, prompt);
/* 	int i = -1;
	while (aux[++i])
		ft_printf("%s\n", aux[i]); */
	return (prompt);
}
