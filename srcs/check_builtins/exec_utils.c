/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:33:07 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 17:16:15 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <check_builtins.h>
#include <lexor.h>
#include <expand.h>

int	full_dup(int n_in, int n_out)
{
	if (dup2(n_in, STDIN_FILENO) == -1 || dup2(n_out, STDOUT_FILENO) == -1)
	{
		try_close(n_in);
		try_close(n_out);
		return (0);
	}
	return (1);
}

size_t	count_cmd(t_chris *lst)
{
	if (lst->next)
		return (count_cmd(lst->next) + 1);
	else
		return (1);
}

void	close_all(int fd[2])
{
	try_close(fd[0]);
	try_close(fd[1]);
}

void	close_and_execve(t_minishell **minish, t_chris **cmd)
{
	try_close((*cmd)->fd_in);
	try_close((*cmd)->fd_out);
	execve((*cmd)->cmd[0], (*cmd)->cmd, (*minish)->env);
}

void	check_cmd_for_loop(t_chris **cmd, int pipe_fd[2])
{
	if ((*cmd)->fd_out == STDOUT_FILENO)
		(*cmd)->fd_out = pipe_fd[WRITE_FD];
	else
		try_close(pipe_fd[WRITE_FD]);
	if ((*cmd)->next->fd_in == STDIN_FILENO)
		(*cmd)->next->fd_in = pipe_fd[READ_FD];
	else
		try_close(pipe_fd[READ_FD]);
}
void	close_all_fd(t_chris *lst)
{
	while (lst)
	{
		try_close(lst->fd_in);
		try_close(lst->fd_out);
		lst = lst->next;
	}
}

