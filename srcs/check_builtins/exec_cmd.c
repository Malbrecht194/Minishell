/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:46:32 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/08 14:36:15 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <check_builtins.h>
#include <lexor.h>

void	exec_cmd(t_minishell *minish, t_chris *cmd)
{
	if (!full_dup(cmd->fd_in, cmd->fd_out))
		return ;
	if (execve(cmd->cmd[0], cmd->cmd, minish->env) == -1)
		exit(127);
}

void	exec_all_cmd(t_minishell *minish)
{
	t_chris	*lst;
	int		builtins;

	lst = minish->cmd_line;
	builtins = is_builtins(lst->cmd[0]);
	if (!(!lst->pipe && !lst->next && builtins != NO_BUILTINS))
	{	
		while (lst)
		{
			builtins = is_builtins(lst->cmd[0]);
			
		}
	}
	else
		exec_builtins(minish, lst, builtins);
}
