/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:29:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/25 20:15:59 by mhaouas          ###   ########.fr       */
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

int	no_quote(char *state, t_exp *exp, int **index, char ***arg)
{
	if (!(*state))
	{
		exp->i += quote_in_expand(*arg, (**arg) + (**index), (**index),
				exp->exp_size);
		return (1);
	}
	return (0);
}

int	do_simple_expand(char **arg, int *index, t_minishell *minish)
{
	size_t	exp_size;
	
	exp_size = 0;
	if (!(*arg)[*index + 1])
		return (0);
	rm_char(arg, *index);
	if ((*arg)[*index] == '\'' || (*arg)[*index] == '\"')
		return (0);
	else if (ft_isalnum((*arg)[*index]) || (*arg)[*index] == '_'
		|| (*arg)[*index] == '?')
	{
		exp_size += expand_env(arg, *index, minish) - 1;
		(*index) += exp_size - 1;
		*index += quote_in_expand(arg, (*arg) + (*index), (*index),
				exp_size);
	}
	return (1);
}

int	do_quote_expand(char **arg, int *index,  t_minishell *minish)
{
	size_t	i;
	size_t	exp_size;

	i = 0;
	exp_size = 0;
	while ((*arg)[++i + (*index)] && (*arg)[i + (*index)] != '\"')
	{
		if ((*arg)[i + (*index)] == '\"')
			break ;
		if ((*arg)[i + (*index)] == '$')
		{
			if (ft_var_name_is_ok(&arg, i + (*index)))
			{
				rm_char(arg, i  + (*index));
				exp_size = expand_env(arg, i  + (*index), minish);
				i += exp_size - 1;
			}
		}
		if (i  + (*index) > ft_strlen(*arg))
			break ;
	}
	*index += i;
	return (exp_size);
}

// int	do_quote_expand(char **arg, int *index,  t_minishell *minish)
// {
// 	t_exp	exp;

// 	init_exp_var(&exp, &index);
// 	while ((*arg)[exp.i + exp.j] && (*arg)[exp.i + exp.j] != '\"')
// 	{
// 		if ((*arg)[exp.i + exp.j] == '\"')
// 			break ;
// 		if ((*arg)[exp.i + exp.j] == '$')
// 		{
// 			if (ft_var_name_is_ok(&arg, &(exp.i), &(exp.j)))
// 			{
// 				if (!is_first_quote(&arg, &(exp.i), &(exp.j), &index))
// 					return (0);
// 				if (!expand_rm_quote(&arg, &(exp.i), &(exp.j)))
// 					continue ;
// 				exp.exp_size = expand_env(arg, exp.i + exp.j, minish);
// 				exp.i += exp.exp_size - 1;
// 			}
// 			if (no_quote("\"", &exp, &index, &arg))
// 				break ;
// 		}
// 		if ((exp.i)++ + exp.j > ft_strlen(*arg))
// 			break ;
// 	}
// 	*index = exp.i + exp.j;
// 	return (exp.exp_size);
// }

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
