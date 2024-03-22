/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:08:04 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/22 13:48:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/builtins.h"

int	ft_pwd(int ac, char **av, char ***env)
{
	(void) ac;
	(void) av;
	(void) env;
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = "no pwd found...";
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
