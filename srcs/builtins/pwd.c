/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:14 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 13:36:43 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

int	ft_pwd(int ac, char **av, t_chris *cmd, t_minishell *minish)
{
	char	*pwd;

	(void)ac;
	(void)av;
	(void)cmd;
	(void)minish;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = "no pwd found...";
	ft_printf_fd(cmd->fd_out, "%s\n", pwd);
	free(pwd);
	return (0);
}
