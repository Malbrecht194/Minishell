/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:41:46 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 13:52:13 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signals.h>

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
	signals_init();
	rl_buff = "";
	while (rl_buff)
	{
		minish->prompt = get_prompt(minish->env);
		rl_buff = readline(minish->prompt);
		add_history(rl_buff);
		check_args(minish, rl_buff);
		free(minish->prompt);
	}
	free(rl_buff);
}
