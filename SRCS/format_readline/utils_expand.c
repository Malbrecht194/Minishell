/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:06:48 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/27 14:07:42 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/expand.h"

size_t	env_len(char *env)
{
	size_t	len;
	
	len = 0;
	if (ft_isalpha(env[0]) || env[len] == '_')
	{
		while(ft_isalnum(env[len]) || env[len] == '_')
			len++;
	}
	else
		len++;
	return (len);
}

char	check_ifs(char a_char)
{
	int		i;
	char	*ifs;

	i = 0;
	ifs = IFS;
	while (ifs[i])
	{
		if (a_char == ifs[i])
			return (-1);
		i++;
	}
	return (a_char);
}
