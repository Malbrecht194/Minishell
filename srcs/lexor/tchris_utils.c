/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tchris_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:29:04 by malbrech          #+#    #+#             */
/*   Updated: 2024/04/11 18:26:40 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <lexor.h>

t_chris	*ft_chrisnew(void)
{
	t_chris	*new;

	new = (t_chris *)ft_calloc(sizeof(t_chris), 1);
	if (!new)
		return (NULL);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	return (new);
}

void	ft_chrisclear(t_chris **chris)
{
	if (!chris || !(*chris))
		return ;
	if ((*chris)->cmd)
		ft_free_2d_array((void **)(*chris)->cmd);
	ft_chrisclear(&(*chris)->next);
	free(*chris);
	*chris = NULL;
}

t_chris	*ft_chrislast(t_chris *chris)
{
	if (!chris->next)
		return (chris);
	else
		return (ft_chrislast(chris->next));
}

void	ft_chrisadd_back(t_chris **chris, t_chris *new)
{
	t_chris	*tmp;

	if (!chris || !new)
		return ;
	else if (!(*chris))
		*chris = new;
	else
	{
		tmp = ft_chrislast(*chris);
		tmp->next = new;
	}
}
