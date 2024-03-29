/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:47:25 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/29 09:35:27 by mhaouas          ###   ########.fr       */
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
	(void) av;
	if (ac != 1)
		return (1);
	tmp = "";
	while (tmp)
	{
		tmp = readline("> ");
		add_history(tmp);
		format_rl(&tmp, dup_env);
		tmp = delete_quote(&tmp, tmp, 0, 0);
		printf("%s\n", tmp);
		free(tmp);
		i++;
	}
	free(tmp);
	ft_free_2d_array((void **)dup_env);
	// char	*test[4];
	
	// test[0] = "/usr/bin/cat";
	// test[1] = "\'a";
	// test[2] = "b\'";
	// test[3] = NULL;
	// execve(test[0], test, dup_env);
}