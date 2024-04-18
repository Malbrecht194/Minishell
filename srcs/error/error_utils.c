/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:14:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/18 13:35:16 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_error.h>

void	print_error(t_err_struct s_error, void *minish)
{
	t_minishell	*minishell;
	char		*location;

	minishell = (t_minishell *)minish;
	if (minish && minishell->location)
		location = minishell->location;
	else
		location = "minishell";
	ft_printf_fd(2, "%s: ", location);
	if (s_error.cmd_name)
		ft_printf_fd(2, "%s: ", s_error.cmd_name);
	ft_printf_fd(2, "%s", s_error.err_msg);
	if (s_error.code == SYNTAX_ERROR)
		ft_printf_fd(2, " `%c'", s_error.args[0]);
	ft_printf_fd(2, ".\n");
}

void	check_exec_error(t_err_code error, void *minish)
{
	t_minishell	*minishell;
	
	minishell = (t_minishell *)minish;
	if (!(NO_F_OR_DIR <= error && error <= IS_DIR))
		return ;
	free_minish(minishell);
}