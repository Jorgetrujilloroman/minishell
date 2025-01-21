/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:57:49 by davigome          #+#    #+#             */
/*   Updated: 2025/01/21 22:25:18 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while(matrix[++i])
		free(matrix[i]);
	free(matrix);
}

int		ft_size_matrix(char **matrix)
{
	int size;
	
	size = 0;
	while(matrix[size])
		size++;
	return (size);
}

char	**ft_dup_matrix(char **envp)
{
	int		size;
	char	**cpy;
	int		i;

	i = -1;
	size = ft_size_matrix(envp);
	cpy = malloc(sizeof(char *) * (size + 1));
	if (!cpy)
		return (NULL);
	while (envp[++i])
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			ft_free_matrix(cpy);
			return (NULL);
		}
	}
	cpy[i] = NULL;
	return (cpy);
}

void	ft_put_error(char *s)
{
	write(2, s, ft_strlen(s));
}

int	ms_strchr_pos(char *s, int c)
{
	int				pos;
	unsigned char	c_unsigned;
	
	pos = -1;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while(s[++pos] != '\0')
	{
		if (s[pos] == c_unsigned)
			return (pos);
	}
	if (c_unsigned == '\0')
		return (pos);
	return (-1);
}