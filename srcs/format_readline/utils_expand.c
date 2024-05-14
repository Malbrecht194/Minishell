/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:06:48 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 17:15:33 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <minishell.h>

void	rm_char(char **arg, int index)
{
	int	i;

	i = 0;
	while ((*arg)[index + i])
	{
		(*arg)[index + i] = (*arg)[index + i + 1];
		i++;
	}
}

size_t	env_len(char *env)
{
	size_t	len;

	len = 0;
	if (ft_isalpha(env[0]) || env[len] == '_')
	{
		while (ft_isalnum(env[len]) || env[len] == '_')
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

int	is_ifs(char a_char)
{
	if (a_char == -1)
		return (1);
	return (0);
}

size_t	skip_heredoc(char *arg, int index)
{
	size_t	i;

	i = 0;
	while (arg[i + index + 2] && check_ifs(arg[i + index + 2]) == -1)
		i++;
	while (arg[i + index + 2] && check_ifs(arg[i + index + 2]))
		i++;
	return (i + 2);
}
