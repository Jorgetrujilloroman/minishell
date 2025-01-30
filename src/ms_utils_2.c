/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:28:21 by jotrujil          #+#    #+#             */
/*   Updated: 2025/01/30 14:41:16 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_status;

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

char	**ms_matrix_replace_n(char ***src, char **add, int n)
{
	char	**tmp;
	int		ijk[3];

	ijk[0] = 0;
	ijk[1] = 0;
	ijk[2] = 0;
	if (!src || !*src || n < 0 || n >= ft_size_matrix(*src))
		return (NULL);
	tmp = ft_calloc(ft_size_matrix(*src) + ft_size_matrix(add), sizeof(char *));
	while (ijk[0] < ft_size_matrix(*src))
	{
		if (ijk[0] == n)
		{
			while (add && add[ijk[1]])
				tmp[ijk[2]++] = ft_strdup(add[ijk[1]++]);
		}
		else
			tmp[++ijk[2]] = ft_strdup(src[0][ijk[0]]);
		ijk[0]++;
	}
	ft_free_matrix(src);
	*src = tmp;
	return (*src);
}

