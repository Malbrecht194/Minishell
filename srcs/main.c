/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:41:46 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/17 18:45:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	rl_loop(t_minishell *minish)
{
	char	*rl_buff;

	rl_buff = "";
	while (rl_buff)
	{
		minish->prompt = get_prompt(minish);
		if (!minish->prompt)
			rl_buff = readline("\001\033[37m\002USER\001\033[31m\002@\
\001\033[32m\002minishell:\001\033[36m\002\?\?\?> \001\033[0m\002");
		else
			rl_buff = readline(minish->prompt);
		if (rl_buff && *rl_buff)
			add_history(rl_buff);
		check_args(minish, rl_buff);
		if (minish->prompt)
			free(minish->prompt);
		minish->prompt = NULL;
		minish->cmd_line = NULL;
	}
	free_minish(minish);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minish;

	if (ac != 1 || av[1])
		error_handle(TOO_MUCH_ARG, NULL, NULL, exit);
	minish = ft_calloc(sizeof(t_minishell), 1);
	if (!minish)
		error_handle(FAIL_STRUCT, NULL, NULL, exit);
	minish->env = dup_array(envp);
	rl_loop(minish);
}
