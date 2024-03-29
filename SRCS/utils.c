/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:02:49 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/28 15:37:30 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	**dup_array(char **array)
{
	char	**n_array;
	int		len;
	int		i;

	if (!array || !*array)
		return (NULL);
	i = 0;
	len = ft_array_len((void **)array);
	n_array = ft_calloc(sizeof(char *), len + 1);
	if (!n_array)
		return (NULL);
	while (i < len)
	{
		n_array[i] = ft_strdup(array[i]);
		if (!n_array[i])
		{
			ft_free_2d_array((void **)n_array);
			return (NULL);
		}
		i++;
	}
	return (n_array);
}
