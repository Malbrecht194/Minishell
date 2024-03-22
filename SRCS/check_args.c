/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:48:34 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/22 09:44:56 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	check_args(t_minishell *minish, char *rl_args)
{
	char	**args;

	if (!rl_args)
		return ;
	rl_args = skip_quoting(rl_args, minish->env);
	if (!rl_args)
		return ;
	// printf("%s\n", rl_args);
	args = ft_split(rl_args, '|');
	minish->cmd = create_link_list(args, minish->env);
	
	t_pipex	*tmp;
	int		i;
	
	tmp = minish->cmd;
	while(tmp)
	{
		i = 0;
		printf("cmd : %s\n", tmp->cmd.command);
		printf("args :\n");
		while(tmp->cmd.flags[i])
		{
			printf("\t%s\n", tmp->cmd.flags[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
