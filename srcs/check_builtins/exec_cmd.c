/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:46:32 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 16:57:24 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>
#include <builtins.h>

void	exec_cmd(t_minishell *minish, t_chris *cmd)
{
	char		*command;
	struct stat	s_stat;

	if (cmd->error == 1)
		error_handle(JUST_EXIT, minish, NULL, exit);
	stat(cmd->cmd[0], &s_stat);
	command = cmd->cmd[0];
	cmd->cmd[0] = test_access(cmd->cmd[0], minish);
	if (!cmd->cmd[0])
	{
		cmd->cmd[0] = command;
		error_handle(NO_F_OR_DIR, minish, cmd->cmd[0], exit);
	}
	if (!full_dup(cmd->fd_in, cmd->fd_out))
			error_handle(DUP_ERROR, minish, NULL, exit);
	close_and_execve(&minish, &cmd);
	if (errno == ENOENT)
		error_handle(NO_F_OR_DIR, minish, cmd->cmd[0], exit);
	else if (errno == EACCES && (s_stat.st_mode & __S_IFMT) == __S_IFDIR)
		error_handle(IS_DIR, minish, cmd->cmd[0], exit);
	else if (errno == EACCES)
		error_handle(NO_PERM, minish, cmd->cmd[0], exit);
}

int	fork_exec(t_minishell *minish, t_chris *lst)
{
	int	builtins;
	int	error;

	builtins = is_builtins(lst->cmd[0]);
	error = 0;
	lst->pid = fork();
	if (lst->pid == -1)
		return (0);
	if (!lst->pid)
	{
		if (lst->next)
			try_close(lst->next->fd_in);
		if (builtins == NO_BUILTINS)
			exec_cmd(minish, lst);
		else
		{
			error = exec_builtins(minish, lst, builtins);
			try_close(lst->fd_out);
			free_minish(minish);
			exit(error);
		}
	}
	try_close(lst->fd_out);
	try_close(lst->fd_in);
	return (1);
}

void	wait_loop(t_minishell *minish, t_chris **lst)
{
	t_chris	*tmp;
	int		wait_ret;

	tmp = *lst;
	while (tmp)
	{
		try_close(tmp->fd_in);
		try_close(tmp->fd_out);
		if (!tmp->pid || tmp->pid == -1)
		{
			tmp = tmp->next;
			continue ;
		}
		waitpid(tmp->pid, &wait_ret, 0);
		if (tmp->error)
			minish->last_error = 1;
		else if (WIFEXITED(wait_ret))
			minish->last_error = WEXITSTATUS(wait_ret);
		else if (WIFSIGNALED(wait_ret))
			minish->last_error = WTERMSIG(wait_ret) + 128;
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
			{
				error_handle(PIPE_ERROR, minish, NULL, NULL);
				break ;
			}
			check_cmd_for_loop(&cmd, pipe_fd);
		}
		if (!fork_exec(minish, cmd))
		{
			error_handle(FORK_ERROR, minish, NULL, NULL);
			break ;
		}
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
	if (builtins == -1)
		return ;
	if (count_cmd(lst) == 1)
	{
		if (builtins == NO_BUILTINS)
			fork_exec(minish, lst);
		else
			minish->last_error = exec_builtins(minish, lst, builtins);
		wait_loop(minish, &lst);
	}
	else
		exec_loop(minish, lst);
}
