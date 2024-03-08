/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:32:36 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/06 10:01:04 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

t_pipex	*ft_pipe_lstlast(t_pipex *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_pipe_lstadd_back(t_pipex **lst, t_pipex *new)
{
	t_pipex	*tmp;

	if (!(*lst))
		*lst = new;
	else
	{
		tmp = ft_pipe_lstlast(*lst);
		tmp->next = new;
	}
}

void	ft_pipe_lstclear(t_pipex **lst)
{
	t_pipex	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_free_2d_array((void **)(*lst)->cmd.flags);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
