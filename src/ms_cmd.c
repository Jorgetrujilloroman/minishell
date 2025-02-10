/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:47:08 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/10 15:24:00 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	*exec_cmd(t_prompt *prompt, t_list *cmd)
{
/* 	t_command	*current_cmd;
	t_command	*next_cmd;
	int			fd[2];

	current_cmd = (t_command *)cmd->content;
	if (cmd->next)
		next_cmd = (t_command *)cmd->next->content;
	else
		next_cmd = NULL;
	prepare_command(prompt, cmd, NULL, NULL); //To review
	if (pipe(fd) == -1)
		ms_handle_error("minishell: error creating pipe\n", NULL, 1);
	if (!fork_check(prompt, cmd, fd)) // to_create
		return (NULL);
	close(fd[PIPE_WRITE_END]);
	if (next_cmd && !next_cmd->in_file)
		next_cmd->in_file = fd[PIPE_READ_END];
	else
		close(fd[PIPE_READ_END]);
	if (current_cmd->in_file > 2)
		close(current_cmd->in_file);
	if (current_cmd->out_file > 2)
		close(current_cmd->out_file); */
	return (NULL);
}
