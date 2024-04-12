/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:42:44 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/12 11:04:33 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <expand.h>
#include <check_builtins.h>

void	check_args(t_minishell *minish, char *rl_args)
{
	if (!rl_args || !*rl_args)
		return ;
	format_rl(&rl_args);
	if (!rl_args)
		return ;
	// printf("%s\n", rl_args);
	minish->cmd_line = chris_lexor(rl_args, minish->env);

	exec_all_cmd(minish);
	// t_chris	*tmp = minish->cmd_line;
	// int		i;
	// while(tmp)
	// {
	// 	i = 1;
	// 	printf("cmd :\n\t%s\n", tmp->cmd[0]);
	// 	printf("args :\n");
	// 	while (tmp->cmd[i])
	// 	{
	// 		printf("\t%s\n", tmp->cmd[i]);
	// 		i++;
	// 	}
	// 	printf ("redir :\n\tin :%d\n\tout: %d\n", tmp->fd_in, tmp->fd_out);
	// 	tmp = tmp->next;
	// }
}
