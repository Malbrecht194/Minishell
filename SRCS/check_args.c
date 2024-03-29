/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:42:44 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/29 09:57:43 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	check_args(t_minishell *minish, char *rl_args)
{
	char	**args;

	if (!rl_args)
		return ;
	format_rl(&rl_args, minish->env);
	if (!rl_args)
		return ;
	// printf("%s\n", rl_args);
	args = ft_split(rl_args, '|');
	// Phase de test du lexor juste en desssous
	//lexor(rl_args);
	minish->cmd = create_link_list(args, minish->env);
	
	t_pipex	*tmp = minish->cmd;
	int		i;
	while(tmp)
	{
		i = 0;
		printf("cmd : %s\n", tmp->cmd.command);
		printf("args :\n");
		while (tmp->cmd.flags[i])
		{
			printf("\t%s\n", tmp->cmd.flags[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
