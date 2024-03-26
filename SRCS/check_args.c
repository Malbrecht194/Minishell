/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:48:34 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/25 11:50:19 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	check_args(t_minishell *minish, char *rl_args)
{
	char	**args;
	char	*no_redir;
	t_pipex	*tmp;
	int		i;

	rl_args = skip_quoting(rl_args);
	// Phase de test du lexor juste en desssous
	//lexor(rl_args);
	no_redir = ft_strtrim(rl_args, "<>");
	args = ft_split(no_redir, '|');
	free(no_redir);
	minish->cmd = create_link_list(args, minish->env);
	tmp = minish->cmd;
	check_quoting(&tmp, minish->env);
	while (tmp)
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
