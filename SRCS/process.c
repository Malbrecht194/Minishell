/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:40:57 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/04 13:21:54 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	process(t_pipex *pipe_struct)
{
	if (dup2(pipe_struct->cmd.in, STDIN_FILENO) == -1)
	{
		free_2d_array(pipe_struct->cmd.envp);
		close(pipe_struct->cmd.in);
		// error_handler(DUP_ERROR);
	}
	if (dup2(pipe_struct->cmd.out, STDOUT_FILENO) == -1)
	{
		free_2d_array(pipe_struct->cmd.envp);
		close(pipe_struct->cmd.out);
		// error_handler(DUP_ERROR);
	}
	if (execve(pipe_struct->cmd.command, pipe_struct->cmd.flags,\
		pipe_struct->cmd.envp) == -1)
	{
		free_2d_array(pipe_struct->cmd.envp);
		// error_handler(EXECVE_ERROR);
	}
}
