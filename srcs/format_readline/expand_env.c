/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:29:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 17:04:24 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <minishell.h>

int	quote_in_expand(char **arg, char *to_check, int index, int end_of_exp)
{
	int		i;
	char	minus_two[2];
	char	*tmp;

	i = 0;
	minus_two[0] = -2;
	minus_two[1] = 0;
	tmp = NULL;
	while (to_check[i] && i < end_of_exp)
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
			return (quote_in_expand(arg, (*arg) + index + i + 2, \
				index + i + 2, end_of_exp) + 1);
		}
		i++;
	}
	return (0);
}

int	do_expand(char **arg, int *index, char state, t_minishell *minish)
{
	size_t	i;
	size_t	j;
	size_t	exp_size;

	j = 0;
	i = *index;
	exp_size = 0;
	if (state)
		j++;
	while ((*arg)[i + j] && (*arg)[i + j] != state)
	{
		if (state && (*arg)[i + j] == state)
			break ;
		if ((*arg)[i + j] == '$')
		{
			if (ft_isalnum((*arg)[i + j + 1]) || (*arg)[i + j + 1] == '_'
				|| (*arg)[i + j + 1] == '\"' || (*arg)[i + j + 1] == '\''
				|| (*arg)[i + j + 1] == '?')
			{
				if (state && (*arg)[i + j + 1] == '\"' && (*arg)[i + j - 1] == '\"')
				{
					*index = i + j;
					return (0);
				}
				rm_char(arg, i + j);
				if (!state && ((*arg)[i + j] == '\"' || (*arg)[i + j] == '\''))
				{
					rm_char(arg, i + j + to_next_quote((*arg) + i + j + 1,
						(*arg)[i + j]) + 1);
					rm_char(arg, i + j);
					return (0);
				}
				exp_size = expand_env(arg, i + j, minish);
				i += exp_size - 1;
			}
			if (!state)
			{
				i += quote_in_expand(arg, (*arg) + (*index), (*index), exp_size);
				break ;
			}
		}
		if (i++ + j > ft_strlen(*arg))
			break ;
	}
	*index = i + j;
	return (exp_size);
}

int	expand_env(char **arg, int index, t_minishell *minish)
{
	int			len;
	size_t		size;
	char		*b_expand;
	char		*s_env;
	char		*tmp;

	len = env_len(&(*arg)[index]);
	b_expand = ft_substr((*arg), 0, index);
	s_env = ft_substr((*arg), index, len);
	if (!b_expand || !s_env)
	{
		ft_multi_free(2, b_expand, s_env);
		return (0);
	}
	if ((*arg)[index] == '?')
		tmp = ft_itoa(minish->last_error);
	else
		tmp = ft_getenv(s_env, minish->env);
	if (!tmp)
		tmp = "";
	free(s_env);
	b_expand = join_and_free(b_expand, tmp, 1, 0);
	b_expand = join_and_free(b_expand, (*arg) + len + index, 1, 0);
	size = ft_strlen(tmp);
	if ((*arg)[index] == '?' && tmp)
		free(tmp);
	free(*arg);
	*arg = b_expand;
	return (size);
}
