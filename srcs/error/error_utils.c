/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:14:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/19 15:55:01 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_error.h>

void	print_s_error(char *s_error)
{
	int	i;

	i = 0;
	write(2, " `", 2);
	if (!ft_strncmp("newline", s_error, 8))
		ft_printf_fd(2, "newline");
	else if (s_error[i] == '|' || s_error[i] == 0)
		write(2, "|", 1);
	else
	{
		while (s_error[i] && (s_error[i] == '<' || s_error[i] == '>'))
			write(2, &s_error[i++], 1);
	}
	write(2, "'", 1);
}

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
	if (s_error.code == NOT_VALID_ID)
		ft_printf_fd(2, "`%s': ", s_error.args);
	else if (s_error.code == NO_F_O_D_CD)
		ft_printf_fd(2, "%s: ", s_error.args);
	ft_printf_fd(2, "%s", s_error.err_msg);
	if (s_error.code == SYNTAX_ERROR)
		print_s_error(s_error.args);
	ft_printf_fd(2, "\n");
}

void	check_exec_error(t_err_code error, void *minish)
{
	t_minishell	*minishell;
	
	minishell = (t_minishell *)minish;
	if (!((NO_F_OR_DIR <= error && error <= IS_DIR) || error == NUM_ARG_REQUIRED))
		return ;
	free_minish(minishell);
}