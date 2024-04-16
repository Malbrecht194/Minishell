/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:33:07 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 14:06:36 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <check_builtins.h>
#include <lexor.h>

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
