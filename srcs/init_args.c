/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:42:44 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/06 09:35:25 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <expand.h>
#include <exec.h>
#include <signals.h>

void	init_args(t_minishell *minish, char *rl_args)
{
	if (!rl_args || !*rl_args)
		return ;
	format_rl(&rl_args, minish);
	if (!rl_args)
		return ;
	signal_error(minish);
	minish->cmd_line = exec_lexor(rl_args, minish);
	if (!minish->cmd_line)
		return ;
	exec_all_cmd(minish);
	if (minish->heredocs)
		ft_free_2d_array(minish->heredocs, ft_array_len(minish->heredocs));
	minish->heredocs = NULL;
}
