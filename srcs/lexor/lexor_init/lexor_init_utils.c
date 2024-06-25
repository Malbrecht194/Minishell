/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:17:06 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/25 17:38:40 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <lexor.h>
#include <expand.h>
#include <minishell.h>

void	ft_initadd_back(t_init **lst, t_init *new)
{
	t_init	*tmp;

	if (!lst || !new)
		return ;
	else if (!(*lst))
		*lst = new;
	else
	{
		tmp = ft_initlast(*lst);
		tmp->next = new;
	}
}

t_init	*ft_initlast(t_init *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_initclear(t_init **lst)
{
	t_init	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		try_free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_init	*check_init_args(t_init *first, t_init *prev, \
	t_init *node, t_minishell *minish)
{
	t_init	*tmp;

	if (node)
		tmp = node->next;
	if (!prev && !node)
		return (NULL);
	else if (!node)
		return (first);
	if (node->type == ARG && !node->str[0])
	{
		if (prev)
			prev->next = tmp;
		try_free(node->str);
		free(node);
		minish->last_error = 0;
		return (check_init_args(first, prev, tmp, minish));
	}
	if (!first)
		first = node;
	if (node->type == ARG && node->str && ft_strchr(node->str, -1))
		return (check_init_args(first, prev, \
			relink_node(node, node->next, minish), minish));
	if (node->type != HEREDOC && node->type != PIPE)
		delete_quote(&node->str);
	return (check_init_args(first, node, tmp, minish));
}
