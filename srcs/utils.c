/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:02:49 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/11 17:57:36 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <expand.h>

int	skip_ifs(char *str)
{
	int	i;

	i = 0;
	while (str[i] == -1)
		i++;
	return (i);
}

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

int	try_close(int fd)
{
	if (fd > 2)
		return (close(fd));
	return (-1);
}
