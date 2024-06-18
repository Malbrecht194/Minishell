/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:29:30 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/18 13:31:31 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all_fd(t_chris *lst)
{
	while (lst)
	{
		try_close(lst->fd_in);
		try_close(lst->fd_out);
		lst = lst->next;
	}
}
