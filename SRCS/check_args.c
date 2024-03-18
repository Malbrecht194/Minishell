/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:48:34 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/18 14:10:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	check_args(t_minishell *minish, char *rl_args)
{
	char	**args;
	char	*no_redir;

	rl_args = skip_quoting(rl_args);
	no_redir = ft_strtrim(rl_args, "<>");
	args = ft_split(no_redir, '|');
	free(no_redir);
	minish->cmd = create_link_list(args, minish->env);
	
	t_pipex	*tmp;
	int		i;
	
	tmp = minish->cmd;
	check_quoting(&tmp, minish->env);
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
