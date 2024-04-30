/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:06:12 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/15 19:23:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <minishell.h>
#include <lexor.h>

int	is_builtins(char *cmd)
{
	char	*builtins[8];
	int		i;

	i = 0;
	if (!cmd)
		return (-1);
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
