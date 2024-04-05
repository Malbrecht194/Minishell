/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:17:06 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/05 10:56:34 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/check_builtins.h"
#include "../INCLUDES/expand.h"
#include "../INCLUDES/lexor.h"
#include "../INCLUDES/minishell.h"

void	lexor_lstadd_back(t_f_lexor **lst, t_f_lexor *new)
{
	t_f_lexor	*tmp;

	if (!lst || !new)
		return ;
	else if (!(*lst))
		*lst = new;
	else
	{
		tmp = lexor_lstlast(*lst);
		tmp->next = new;
	}
}

t_f_lexor	*lexor_lstlast(t_f_lexor *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	lexor_lstclear(t_f_lexor **lst)
{
	t_f_lexor	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
