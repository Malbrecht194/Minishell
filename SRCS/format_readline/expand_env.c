/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:29:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/05 11:26:32 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/expand.h"
#include "../../INCLUDES/minishell.h"

int	quot_in_expand(char **arg, char *to_check, int index)
{
	int		i;
	char	minus_two[2];
	char	*tmp;

	i = 0;
	minus_two[0] = -2;
	minus_two[1] = 0;
	tmp = NULL;
	while (to_check[i])
	{
		if (to_check[i] == '\'' || to_check[i] == '\"')
		{
			tmp = ft_substr(*arg, 0, index + i);
			tmp = join_and_free(tmp, minus_two, 1, 0);
			tmp = join_and_free(tmp, (*arg) + index + i, 1, 0);
			if (!tmp)
				return (0);
			free(*arg);
			*arg = tmp;
			return (quot_in_expand(arg, (*arg) + index + i + 2, index + i + 2) + 1);
		}
		i++;
	}
	return (0);
}

void	do_expand(char **arg, int *index, char state, char **env)
{
	size_t	i;
	size_t	j;
	
	i = *index;
	j = 0;
	if (state)
		j++;
	while ((*arg)[i + j] && (*arg)[i + j] != state)
	{
		if (state && (*arg)[i + j] == state)
			break ;
		if ((*arg)[i + j] == '$')
		{
			rm_char(arg, i + j);
			i += expand_env(arg, i + j, env);
			if (!state)
			{	
				i += quot_in_expand(arg, (*arg) + (*index), (*index));
				break ;
			}
		}
		if (i++ + j > ft_strlen(*arg))
			break ;
	}
	*index = i + j;
}

int	expand_env(char **arg, int index, char **env)
{
	int		len;
	char	*b_expand;
	char	*s_env;
	char	*tmp;

	len = env_len(&(*arg)[(index)]);
	b_expand = ft_substr((*arg), 0, index);
	s_env = ft_substr((*arg), index, len);
	if (!b_expand || !s_env)
	{
		ft_multi_free(2, b_expand, s_env);
		return (0);
	}
	tmp = ft_getenv(s_env, env);
	if (!tmp)
		tmp = "";
	free(s_env);
	b_expand = join_and_free(b_expand, tmp, 1, 0);
	b_expand = join_and_free(b_expand, (*arg) + len + index, 1, 0);
	free(*arg);
	*arg = b_expand;
	return (ft_strlen(tmp));
}
