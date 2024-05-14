/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:14 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/05 13:38:16 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

int	ft_pwd(int ac, char **av, t_chris *cmd, t_minishell *minish)
{
	char	*pwd;

	(void)ac;
	(void)av;
	(void)minish;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf_fd(cmd->fd_out, "no pwd found...\n", pwd);
		return (1);
	}
	ft_printf_fd(cmd->fd_out, "%s\n", pwd);
	free(pwd);
	return (0);
}
