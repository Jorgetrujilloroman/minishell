/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:57:49 by davigome          #+#    #+#             */
/*   Updated: 2025/01/22 18:23:50 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_status;

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while(matrix[++i])
			free(matrix[i]);
		free(matrix);
	}
}

int		ft_size_matrix(char **matrix)
{
	int size;
	
	size = 0;
	while(matrix && matrix[size])
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
	while (s[++pos] != '\0')
	{
		if (s[pos] == c_unsigned)
			return (pos);
	}
	if (c_unsigned == '\0')
		return (pos);
	return (-1);
}

void	if_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

char	*strtrim(char const *s1, char const *set)
{
	int	len;
	int	i;
	int	j;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	i = 0;
	j = len -1;
	while (i<= len / 2 && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (j >= len / 2 && ft_strchr(set, s1[j]) != NULL)
		j--;
	if (i > j)
		return (ft_strdup(""));
	len = j - i;
	return (ft_substr(s1, i, len + 1));
}
