/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:42:44 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 16:51:33 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <expand.h>
#include <check_builtins.h>

void	check_args(t_minishell *minish, char *rl_args)
{
	if (!rl_args || !*rl_args)
		return ;
	format_rl(&rl_args, minish);
	if (!rl_args)
		return ;
	minish->cmd_line = chris_lexor(rl_args, minish);
	if (!minish->cmd_line)
		return ;
	exec_all_cmd(minish);
}
