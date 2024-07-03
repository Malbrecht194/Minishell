/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:41:46 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:00:44 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <signals.h>

int	g_sig;

char	*get_line(t_minishell *minish)
{
	char	*rl_buff;

	minish->prompt = get_prompt(minish);
	if (!minish->prompt)
		rl_buff = readline("\001\033[37m\002USER\001\033[31m\002@\
\001\033[32m\002minishell:\001\033[36m\002\?\?\?> \001\033[0m\002");
	else
		rl_buff = readline(minish->prompt);
	if (rl_buff && *rl_buff)
		add_history(rl_buff);
	return (rl_buff);
}

void	rl_loop(t_minishell *minish)
{
	char	*rl_buff;

	rl_buff = "";
	while (rl_buff)
	{
		rl_buff = get_line(minish);
		if (rl_buff && !(*rl_buff))
		{
			free(rl_buff);
			if (minish->prompt)
				free(minish->prompt);
			continue ;
		}
		init_args(minish, rl_buff);
		if (minish->prompt)
			free(minish->prompt);
		minish->prompt = NULL;
		minish->cmd_line = NULL;
		minish->heredocs = NULL;
	}
	ft_printf_fd(1, "exit\n");
	ft_exit(1, NULL, NULL, minish);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minish;

	if (ac != 1 || av[1])
		error_handle(TOO_MUCH_ARG, NULL, NULL, exit);
	minish = ft_calloc(sizeof(t_minishell), 1);
	if (!minish)
		error_handle(FAIL_STRUCT, NULL, NULL, exit);
	minish->heredocs = NULL;
	if (envp && *envp)
	{
		minish->env = dup_array(envp);
		if (!minish->env)
			error_handle(MALLOC_ERROR, NULL, NULL, exit);
	}
	signals_init(1, minish);
	rl_loop(minish);
	signals_init(2, minish);
}
