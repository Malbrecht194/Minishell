/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:29:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/27 15:10:04 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/expand.h"

int	quot_in_expand(char **arg, char *to_check, int index)
{
	int		i;
	char	minus_two[2];
	char	*tmp;

	i = -1;
	minus_two[0] = -2;
	minus_two[1] = 0;
	tmp = NULL;
	while (to_check[++i])
	{
		if (to_check[i] == '\'' || to_check[i] == '\"')
		{
			tmp = ft_substr(*arg, 0, index + i);
			tmp = join_and_free(tmp, minus_two, 1, 0);
			tmp = join_and_free(tmp, (*arg) + index + i, 1, 0);
			if (!tmp)
				return (NULL);
			free(*arg);
			*arg = tmp;
			return (quot_in_expand(arg, (*arg) + index + i + 2, index + i + 2) + 1);
		}
	}
	return (0);
}

void	do_expand(char **arg, int *index, char state, char **env)
{
	char	*search;
	char	*tmp;
	int		i;

	i = *index;
	while ((*arg)[i])
	{
		if (state && (*arg)[i] == state)
			break ;
		if ((*arg)[i] == '$')
		{
			i += expand_env(arg, i, env);
			if (!state)
			{	
				i += quot_in_expand(arg, (*arg) + (*index), 0);
				break ;
			}
		}
		if (i > ft_strlen(*arg))
			break ;
		i++;
	}
	*index = i;
}

void	change_expand(char **arg, char **env)
{
	int		i;
	char	*pre_quot;

	i = 0;
	pre_quot = NULL;
	while ((*arg)[i])
	{
		if (((*arg)[i] == '\"') || ((*arg)[i] == '$'))
			pre_quot = ft_substr((*arg), 0, i);
		if ((*arg)[i] == '\"')
			i += check_e_quot(arg, pre_quot, (*arg) + i, env) - 1;
		else if ((*arg)[i] == '\'')
			i += to_next_quote((*arg) + i + 1, '\'');
		else if ((*arg)[i] == '$')
			i += check_expand(arg, pre_quot, (*arg) + i, env) - 1;
		i++;
	}
}

int	expand_env(char **arg, int index, char **env)
{
	int		len;
	char	*b_expand;
	char	*s_env;
	char	*tmp;

	len = env_len(&(*arg)[(index) + 1]);
	b_expand = ft_substr((*arg), 0, index - 1);
	s_env = ft_substr((*arg), index + 1, len);
	if (!b_expand || !s_env)
	{
		ft_multi_free(2, b_expand, s_env);
		return ;
	}
	tmp = ft_getenv(s_env, env);
	if (!tmp)
		tmp = "";
	free(s_env);
	b_expand = join_and_free(b_expand, tmp, 1, 0);
	free(*arg);
	*arg = join_and_free(b_expand, (*arg) + len + 1, 1, 0);
	return (ft_strlen(tmp) - 1);
}
