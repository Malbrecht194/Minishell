/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:46:32 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/12 13:00:32 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>

void	exec_cmd(t_minishell *minish, t_chris *cmd)
{
	char	*command;

	// char	*tmp = "";
	// while (tmp)
	// {
	// 	tmp = get_next_line(cmd->fd_in);
	// 	printf("fd %d : %s", i, tmp);
	// 	free(tmp);
	// }
	command = cmd->cmd[0];
	cmd->cmd[0] = test_access(cmd->cmd[0], minish->env);
	if (!cmd->cmd[0])
	{
		cmd->cmd[0] = command;
		ft_free_2d_array((void **)cmd->cmd);
		exit(127);
	}
	if (cmd->error || !full_dup(cmd->fd_in, cmd->fd_out))
	{
		try_close(cmd->fd_in);
		try_close(cmd->fd_out);
		exit(1);
	}
	try_close(cmd->fd_in);
	try_close(cmd->fd_out);
	if (execve(cmd->cmd[0], cmd->cmd, minish->env) == -1)
		exit(1);
}

void	fork_exec(t_minishell *minish, t_chris *lst, int pipe_fd[2])
{
	int		builtins;

	builtins = is_builtins(lst->cmd[0]);
	// printf("fd_in : %d , fd_out : %d\n", lst->fd_in, lst->fd_out);
	lst->pid = fork();
	if (lst->pid == -1)
		return ;
	if (!lst->pid)
	{
		if (pipe_fd)
			try_close(pipe_fd[READ_FD]);
		if (builtins == NO_BUILTINS)
			exec_cmd(minish, lst);
		else
			exit(exec_builtins(minish, lst, builtins));
	}
	if (pipe_fd)
		try_close(pipe_fd[WRITE_FD]);
	try_close(lst->fd_in);
}

void	wait_loop(t_minishell *minish, t_chris **lst)
{
	t_chris	*tmp;
	
	tmp = *lst;
	while (tmp)
	{
		waitpid(tmp->pid, &minish->last_error, 0);
		try_close(tmp->fd_in);
		try_close(tmp->fd_out);
		tmp = tmp->next;
	}
	ft_chrisclear(lst);
}

void	exec_loop(t_minishell *minish, t_chris *lst)
{
	int		pipe_fd[2];
	t_chris	*cmd;

	cmd = lst;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
				return ; //error
			if (cmd->fd_out == STDOUT_FILENO)
				cmd->fd_out = pipe_fd[WRITE_FD];
			else
				try_close(pipe_fd[WRITE_FD]);
			if (cmd->next->fd_in == STDIN_FILENO)
				cmd->next->fd_in = pipe_fd[READ_FD];
			else
				try_close(pipe_fd[READ_FD]);
			fork_exec(minish, cmd, pipe_fd);
		}
		else
			fork_exec(minish, cmd, NULL);
		cmd = cmd->next;
	}
	wait_loop(minish, &lst);
}

void	exec_all_cmd(t_minishell *minish)
{
	t_chris	*lst;
	int		builtins;

	lst = minish->cmd_line;
	builtins = is_builtins(lst->cmd[0]);
	if (count_cmd(lst) == 1)
	{
		if (builtins == NO_BUILTINS)
		{
			fork_exec(minish, lst, NULL);
			waitpid(lst->pid, &minish->last_error, 0);
		}
		else
			minish->last_error = exec_builtins(minish, lst, builtins);
		try_close(lst->fd_in);
		try_close(lst->fd_out);
	}
	else
		exec_loop(minish, lst);
}
