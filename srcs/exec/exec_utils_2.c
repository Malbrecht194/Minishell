/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:29:30 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/21 22:53:27 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <exec.h>

void	close_all_fd(t_chris *lst)
{
	while (lst)
	{
		try_close(lst->fd_in);
		try_close(lst->fd_out);
		lst = lst->next;
	}
}
