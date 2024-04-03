/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:42:44 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/03 15:16:18 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"
#include "../INCLUDES/expand.h"
#include "../INCLUDES/check_builtins.h"

void	check_args(t_minishell *minish, char *rl_args)
{
	char	**args;

	args = NULL;
	if (!rl_args)
		return ;
	format_rl(&rl_args, minish->env);
	if (!rl_args)
		return ;
	// printf("%s\n", rl_args);
	args = ft_split(rl_args, '|');
	// Phase de test du lexor juste en desssous
	//lexor(rl_args);
	minish->cmd = create_link_list(args/*, minish->env*/);

	check_cmd(minish);
	// t_pipex	*tmp = minish->cmd;
	// int		i;
	// while(tmp)
	// {
	// 	i = 1;
	// 	printf("cmd :\t%s\n", tmp->cmd.cmd[0]);
	// 	printf("args :\n");
	// 	while (tmp->cmd.cmd[i])
	// 	{
	// 		printf("\t%s\n", tmp->cmd.cmd[i]);
	// 		i++;
	// 	}
	// 	tmp = tmp->next;
	// }
	free(rl_args);
}
