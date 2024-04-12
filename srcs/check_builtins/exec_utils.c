/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:33:07 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/12 10:14:47 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <check_builtins.h>
#include <lexor.h>

int	dup_builtins(int n_in, int n_out, int state)
{
	static int	in_out[2];

	if (!state)
	{	
		in_out[0] = dup(STDIN_FILENO);
		in_out[1] = dup(STDOUT_FILENO);
	}
	else if (state == 1)
	{
		n_in = in_out[0];
		n_out = in_out[1];
	}
	if ((in_out[0] == -1 || in_out[1] == -1) || state > 1)
	{
		close_all(in_out);
		return (0);
	}
	if (dup2(n_in, STDIN_FILENO) == -1 || dup2(n_out, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

int	full_dup(int n_in, int n_out)
{
	if (dup2(n_in, STDIN_FILENO) == -1 || dup2(n_out, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

size_t	count_cmd(t_chris *lst)
{
	if (lst->next)
		return (count_cmd(lst->next) + 1);
	else
		return (1);
}

void	close_all(int fd[2])
{
	try_close(fd[0]);
	try_close(fd[1]);
}
