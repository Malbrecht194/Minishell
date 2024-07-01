/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:29:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/01 11:14:04 by mhaouas          ###   ########.fr       */
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
			return (quote_in_expand(arg, (*arg) + index + i + 2, index + i + 2,
					end_of_exp) + 1);
		}
		i++;
	}
	return (0);
}

int	do_simple_expand(char **arg, int *index, t_minishell *minish)
{
	size_t	exp_size;

	exp_size = 0;
	if (!(*arg)[*index + 1])
		return (-1);
	rm_char(arg, *index);
	if ((*arg)[*index] == '\'' || (*arg)[*index] == '\"')
		return (0);
	else if (ft_isalnum((*arg)[*index]) || (*arg)[*index] == '_'
		|| (*arg)[*index] == '?')
	{
		exp_size += expand_env(arg, *index, minish);
		(*index) += quote_in_expand(arg, (*arg) + (*index), (*index), exp_size);
		if (exp_size)
			exp_size--;
		(*index) += exp_size;
	}
	return (1);
}

int	do_quote_expand(char **arg, int *index, t_minishell *minish)
{
	size_t	i;
	size_t	exp_size;

	i = *index;
	exp_size = 0;
	while ((*arg)[++i] && (*arg)[i] != '\"')
	{
		if ((*arg)[i] == '$')
		{
			if (ft_isalnum((*arg)[i + 1]) || (*arg)[i + 1] == '_' || (*arg)[i
				+ 1] == '?')
			{
				rm_char(arg, i);
				exp_size = expand_env(arg, i, minish);
				if (exp_size)
					exp_size--;
				i += exp_size;
			}
		}
		if (i > ft_strlen(*arg))
			break ;
	}
	*index = i;
	return (exp_size);
}

static void	expand_env_part(char **tmp, char **s_env, char **b_expand)
{
	if (!(*tmp))
		*tmp = "";
	free(*s_env);
	*b_expand = join_and_free(*b_expand, *tmp, 1, 0);
}

int	expand_env(char **arg, int index, t_minishell *minish)
{
	size_t	len;
	char	*b_expand;
	char	*s_env;
	char	*tmp;

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
	expand_env_part(&tmp, &s_env, &b_expand);
	b_expand = join_and_free(b_expand, (*arg) + len + index, 1, 0);
	len = ft_strlen(tmp);
	if ((*arg)[index] == '?' && tmp)
		free(tmp);
	free(*arg);
	*arg = b_expand;
	return (len);
}
