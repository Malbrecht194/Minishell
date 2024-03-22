/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:47:25 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/22 09:47:00 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**dup_env;
	char	*tmp;
	int		i;

	i = 1;
	// (void) ac;
	// (void) av;
	dup_env = dup_array(env);
	if (ac == 1)
		return (1);
	while (av[i])
	{
		tmp = ft_strdup(av[i]);
		tmp = skip_quoting(tmp, dup_env);
		printf("%s\n", tmp);
		free(tmp);
		i++;
	}
	ft_free_2d_array((void **)dup_env);
	// char	*test[4];
	
	// test[0] = "/usr/bin/cat";
	// test[1] = "\'a";
	// test[2] = "b\'";
	// test[3] = NULL;
	// execve(test[0], test, dup_env);
	printf("fshfjkshfjk");
}