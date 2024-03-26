/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tchris_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:29:04 by malbrech          #+#    #+#             */
/*   Updated: 2024/03/26 15:38:11 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

//Creer un chris vide
t_chris	*ft_chrisnew(int index)
{
	t_chris	*new;

	new = (t_chris *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

//Clear mon chris
void	ft_chrisclear(t_chris **chris)
{
	if (!chris)
		return ;
	if (!(*chris))
		return ;
	ft_chrisclear(&(*chris)->next);
	free(*chris);
	*chris = NULL;
}

//Renvoie le dernier node de chris
t_chris	*ft_chrislast(t_chris *chris)
{
	t_chris	*tmp;

	tmp = chris;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

//Renvoie l'avant dernier chris
t_chris	*ft_chris_before_last(t_chris *chris)
{
	while (chris && chris->next && chris->next->next != NULL)
		chris = chris->next;
	return (chris);
}

//Ajoute un node a la fin de chris
void	ft_chrisadd_back(t_chris **chris, t_chris *new)
{
	t_chris	*tmp;

	if (chris)
	{
		if (*chris == NULL)
			*chris = new;
		else
		{
			tmp = ft_chrislast(*(chris));
			tmp->next = new;
		}
	}
}
