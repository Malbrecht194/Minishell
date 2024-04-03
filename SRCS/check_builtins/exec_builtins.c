/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:22:28 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/03 11:04:13 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/check_builtins.h"
#include "../../INCLUDES/minishell.h"

void	exec_builtins(t_minishell *minish, t_pipex *cmd, int b_num)
{
	size_t	array_len;
	int		(*builtins[6])(int, char **, char ***);

	array_len = ft_array_len((void **)(cmd->cmd.cmd));
	builtins[FT_CD] = ft_cd;
	builtins[FT_ECHO] = ft_echo;
	builtins[FT_ENV] = ft_env;
	builtins[FT_EXPORT] = ft_export;
	builtins[FT_PWD] = ft_pwd;
	builtins[FT_UNSET] = ft_unset;
	if (b_num == FT_EXIT)
		return ; //do_exit
	else
		minish->last_error = builtins[b_num](array_len, cmd->cmd.cmd,\
			&minish->env);
}
