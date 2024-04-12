/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:22:28 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/12 10:09:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <minishell.h>

int	exec_builtins(t_minishell *minish, t_chris *cmd, int b_num)
{
	size_t	array_len;
	int		error;
	int		(*builtins[6])(int, char **, char ***);

	if (!dup_builtins(cmd->fd_in, cmd->fd_out, 0))
		return (0);
	array_len = ft_array_len((void **)(cmd->cmd));
	builtins[FT_CD] = ft_cd;
	builtins[FT_ECHO] = ft_echo;
	builtins[FT_ENV] = ft_env;
	builtins[FT_EXPORT] = ft_export;
	builtins[FT_PWD] = ft_pwd;
	builtins[FT_UNSET] = ft_unset;
	if (b_num == FT_EXIT)
		return (0); //do_exit
	error = minish->last_error = builtins[b_num](array_len, cmd->cmd,\
			&minish->env);
	if (!dup_builtins(0, 0, 1))
		return (0);
	dup_builtins(0, 0, 42);
	return (error);
}
