/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:57:07 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/01 15:58:25 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_array_len(void **array)
{
	size_t	i;

	i = 0;
	if (!array || !*array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
