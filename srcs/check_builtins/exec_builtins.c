/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:22:28 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/08 14:18:44 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <minishell.h>

void	exec_builtins(t_minishell *minish, t_chris *cmd, int b_num)
{
	size_t	array_len;
	int		(*builtins[6])(int, char **, char ***);

	if (!full_dup(cmd->fd_in, cmd->fd_out))
		return ;
	array_len = ft_array_len((void **)(cmd->cmd));
	builtins[FT_CD] = ft_cd;
	builtins[FT_ECHO] = ft_echo;
	builtins[FT_ENV] = ft_env;
	builtins[FT_EXPORT] = ft_export;
	builtins[FT_PWD] = ft_pwd;
	builtins[FT_UNSET] = ft_unset;
	if (b_num == FT_EXIT)
		return ; //do_exit
	else
		minish->last_error = builtins[b_num](array_len, cmd->cmd,\
			&minish->env);
	if (!full_dup(STDIN_FILENO, STDOUT_FILENO))
		return ;
}
