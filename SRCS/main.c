/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:33:20 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/07 18:05:33 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minish;
	char		*rl_buff;

	if (ac != 1 || av[1])
		return (1);
	minish = malloc(sizeof(t_minishell));
	if (!minish)
		exit(0); //error
	minish->env = dup_array(envp);
	if (!minish->env)
		exit(1); //error
	rl_buff = ft_calloc(1, 1);
	while (rl_buff)
	{
		free(rl_buff);
		minish->prompt = get_prompt();
		rl_buff = readline(minish->prompt);
		add_history(rl_buff);
		check_args(minish, rl_buff);
		free(minish->prompt);
	}
	
}
