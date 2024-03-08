/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:02:49 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/08 16:37:03 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	**dup_array(char **array)
{
	char	**n_array;
	char	*tmp;

	if (!array || !*array)
		return (NULL);
	tmp = ft_unsplit(array, 1);
	if (!tmp)
		return (NULL);
	n_array = ft_split(tmp, 1);
	free(tmp);
	if (!n_array || !*n_array)
		return (NULL);
	return (n_array);
}
