/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:14:42 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/07 16:29:12 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	ft_env(int ac, char **av, char **envp)
{
	int	i;
	
	(void)ac;
	(void)av;
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (0);
}
