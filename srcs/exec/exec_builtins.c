/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:22:28 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <minishell.h>
#include <expand.h>

int	exec_builtins(t_minishell *minish, t_exec *cmd, int b_num)
{
	size_t	array_len;
	int		(*builtins[8])(int, char **, t_exec *, t_minishell *);

	if (!cmd || cmd->error)
		return (1);
	array_len = ft_array_len((cmd->cmd));
	builtins[FT_CD] = ft_cd;
	builtins[FT_ECHO] = ft_echo;
	builtins[FT_ENV] = ft_env;
	builtins[FT_EXPORT] = ft_export;
	builtins[FT_PWD] = ft_pwd;
	builtins[FT_UNSET] = ft_unset;
	builtins[FT_EXIT] = ft_exit;
	builtins[7] = NULL;
	minish->last_error = builtins[b_num](array_len, cmd->cmd, cmd, minish);
	return (minish->last_error);
}
