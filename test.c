/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:47:25 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/02 18:26:13 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/minishell.h"
// #include "includes/expand.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>
# include <term.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	test;
	test = -1;
	printf("%d\n", test);
	
	// char	**dup_env;
	// char	*tmp;
	// int		i;

	// i = 1;
	// // (void) ac;
	// // (void) av;
	// dup_env = dup_array(env);
	// (void) av;
	// if (ac != 1)
	// 	return (1);
	// tmp = "";
	// while (tmp)
	// {
	// 	tmp = readline("> ");
	// 	add_history(tmp);
	// 	format_rl(&tmp, dup_env);
	// 	delete_quote(&tmp);
	// 	printf("%s\n", tmp);
	// 	free(tmp);
	// 	i++;
	// }
	// free(tmp);
	// ft_free_2d_array(dup_env);
	// char	*test[4];
	
	// test[0] = "/usr/bin/cat";
	// test[1] = "\'a";
	// test[2] = "b\'";
	// test[3] = NULL;
	// execve(test[0], test, dup_env);
}