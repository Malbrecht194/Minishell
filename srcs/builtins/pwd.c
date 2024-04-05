/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:14 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/05 15:26:08 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

int	ft_pwd(int ac, char **av, char ***env)
{
	char	*pwd;

	(void) ac;
	(void) av;
	(void) env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = "no pwd found...";
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
