/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:12:01 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/18 13:23:53 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_count_word(char const *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == sep)
		i++;
	if ((s[i] == 0))
		return (0);
	count = 1;
	while (s[i])
	{
		if ((s[i] == sep) && (s[i + 1] != sep))
		{
			count += 1;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static int	mini_count_char(char *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((s[i] != sep) && s[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char	**mini_split_format(char **buff, char const *s, char sep)
{
	int	i;
	int	g;
	int	count;

	i = 0;
	g = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i] == '\0')
			break ;
		count = mini_count_char((char *)s + i, sep);
		buff[g] = ft_substr(s, i, count);
		if (!buff[g])
			return (NULL);
		i += count;
		g++;
	}
	buff[g] = NULL;
	return (buff);
}

char	**mini_split(char const *s, char sep)
{
	char	**buff;

	if (!s)
		return (NULL);
	buff = ft_calloc(sizeof(char *), mini_count_word(s, sep) + 1);
	if (!buff)
		return (NULL);
	buff = mini_split_format(buff, s, sep);
	return (buff);
}
