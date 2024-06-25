/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:46:48 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/25 20:08:08 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <minishell.h>

void	expand_env_part(char **tmp, char **s_env, char **b_expand)
{
	if (!(*tmp))
		*tmp = "";
	free(*s_env);
	*b_expand = join_and_free(*b_expand, *tmp, 1, 0);
}

void	init_exp_var(t_exp *exp, int **index)
{
	exp->i = **index;
	exp->j = 1;
	exp->exp_size = 0;
}

int	is_first_quote(char ***arg, size_t *i, size_t *j, int **index)
{
	if ((**arg)[*i + *j - 1] == '\"' && (**arg)[*i + *j + 1] == '\"')
	{
		**index = *i + *j;
		return (0);
	}
	return (1);
}

int	expand_rm_quote(char ***arg, size_t *i, size_t *j)
{
	rm_char(*arg, *i + *j);
	if (((**arg)[*i + *j] == '\"'
		|| (**arg)[*i + *j] == '\''))
		return (0);
	return (1);
}

int	ft_var_name_is_ok(char ***arg, size_t i)
{
	if (ft_isalnum((**arg)[i + 1]) || (**arg)[i + 1] == '_'
				|| (**arg)[i + 1] == '?')
		return (1);
	return (0);
}
