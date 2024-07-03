/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:06:32 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 17:14:42 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <builtins.h>
# include <libft.h>
# include <minishell.h>

enum	e_builtins
{
	FT_CD,
	FT_ECHO,
	FT_ENV,
	FT_EXPORT,
	FT_PWD,
	FT_UNSET,
	FT_EXIT,
	NO_BUILTINS
};

void	close_and_execve(t_minishell **minish, t_exec **cmd);
void	check_cmd_for_loop(t_exec **cmd, int pipe_fd[2]);
int		full_dup(int n_stdin, int n_stdout);
int		exec_builtins(t_minishell *minish, t_exec *cmd, int b_num);
void	check_cmd_for_loop(t_exec **cmd, int pipe_fd[2]);
int		is_builtins(char *cmd);
size_t	count_cmd(t_exec *lst);
void	exec_all_cmd(t_minishell *minish);
void	close_all_fd(t_exec *lst);

#endif