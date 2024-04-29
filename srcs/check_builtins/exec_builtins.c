/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:22:28 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/23 12:36:08 by xeo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <minishell.h>

int	exec_builtins(t_minishell *minish, t_chris *cmd, int b_num)
{
	size_t	array_len;
	int		(*builtins[8])(int, char **, t_chris *, t_minishell *);

	if (!cmd || cmd->error)
		return (1);
	array_len = ft_array_len((void **)(cmd->cmd));
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
