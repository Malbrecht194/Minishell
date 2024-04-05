/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:06:12 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/04 17:58:27 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/check_builtins.h"
#include "../../INCLUDES/minishell.h"
#include "../../INCLUDES/lexor.h"

int	is_builtins(char *cmd)
{
	char	*builtins[8];
	int		i;

	i = 0;
	builtins[FT_CD] = "cd";
	builtins[FT_ECHO] = "echo";
	builtins[FT_ENV] = "env";
	builtins[FT_EXPORT] = "export";
	builtins[FT_PWD] = "pwd";
	builtins[FT_UNSET] = "unset";
	builtins[FT_EXIT] = "exit";
	builtins[7] = NULL;
	while (builtins[i]\
		&& ft_strncmp(builtins[i], cmd, ft_strlen(builtins[i]) + 1))
		i++;
	if (!builtins[i])
		return (NO_BUILTINS);
	else
		return (i);
}

void	check_cmd(t_minishell *minish)
{
	t_chris	*tmp;
	int		builtins;

	tmp = minish->cmd;
	while (tmp)
	{
		builtins = is_builtins(tmp->cmd[0]);
		if (builtins == NO_BUILTINS)
			tmp->cmd[0] = test_access(tmp->cmd[0], minish->env);
		tmp = tmp->next;
	}
	
	while (minish->cmd)
	{
		printf("%s\n", minish->cmd->cmd.cmd[0]);
		minish->cmd = minish->cmd->next;
	}
}
