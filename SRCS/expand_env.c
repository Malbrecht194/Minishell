/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:29:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/22 13:44:48 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*quot_in_expand(char **arg, char *to_check, int index)
{
	int		i;
	char	minus_two[2];
	char	*tmp;

	i = -1;
	minus_two[0] = -2;
	minus_two[1] = NULL;
	tmp = NULL;
	while (to_check[++i])
	{
		if (to_check[i] == '\'' || to_check[i] == '\"')
		{
			tmp = ft_substr(*arg, 0, index + i);
			tmp = join_and_free(tmp, minus_two);
			tmp = join_and_free(tmp, (*arg) + index + i);
			if (!tmp)
				return (NULL);
			free(*arg);
			*arg = tmp;
			return (quot_in_expand(arg, (*arg) + index + i + 2, index + i + 2));
		}
	}
	return (*arg);
}

int	check_expand(char **arg, char *pre_quot, char *b_quot, char **env)
{
	char	*search;
	char	*final;
	int		i;

	i = 0;
	if (!pre_quot)
		return (1);
	search = ft_strdup(b_quot);
	final = NULL;
	if (!search)
		return (0);
	final = search + 1;
	expand_env(&pre_quot, &final, env);
	free(*arg);
	free(search);
	*arg = quot_in_expand(&final, final, 0);
	i = ft_strlen(final);
	return (i);
}

void	change_expand(char **arg, char **env)
{
	int		i;
	char	*pre_quot;
	char	*tmp;

	i = -1;
	tmp = *arg;
	pre_quot = NULL;
	while (tmp[++i])
	{
		if (tmp[i] == '\"')
		{
			pre_quot = ft_substr(tmp, 0, i);
			i += check_e_quot(&tmp, pre_quot, tmp + i, env) - 1;
		}
		else if (tmp[i] == '\'')
			i += to_next_quote(tmp + i + 1, '\'');
		else if (tmp[i] == '$')
		{
			pre_quot = ft_substr(tmp, 0, i);
			i += check_expand(&tmp, pre_quot, tmp + i, env) - 1;
		}
	}
	*arg = tmp;
}

int	expand_env(char **add_to, char **to_search, char **env)
{
	int		len;
	int		size;
	char	*s_env;
	char	*tmp;

	len = 0;
	if (ft_isalpha((*to_search)[0]) || (*to_search)[len] == '_')
	{
		while(ft_isalnum((*to_search)[len])
			|| (*to_search)[len] == '_')
			len++;
	}
	else
		len++;
	s_env = ft_substr((*to_search), 0, len);
	if (!ft_getenv(s_env, env))
		tmp = join_and_free(*add_to, "");
	else
		tmp = join_and_free(*add_to, ft_getenv(s_env, env));
	size = ft_strlen(ft_getenv(s_env, env));
	free(s_env);
	if (!tmp)
		return (0);
	tmp = join_and_free(tmp, (*to_search) + len);
	if (!tmp)
		return (0);
	*to_search = tmp;
	return (size);
}
