/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/22 16:43:50 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*delete_quote(char **arg, char *to_check, char a_quote, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	while (to_check[i])
	{
		if (to_check[i] == '\'' || to_check[i] == '\"' || to_check[i] == -2)
		{
			free(to_check[i]);
			if (!tmp)
				return (NULL);
			free(*arg);
			*arg = tmp;
			return (quot_in_expand(arg, (*arg) + index + i + 2, index + i + 2));
		}
	}
}

int	check_e_quot(char **arg, char *pre_quot, char *b_quot, char **env)
{
	char	*search;
	char	*final;
	int		i;

	i = 0;
	if (!pre_quot)
		return (to_next_quote(b_quot + 1, '\"'));
	search = ft_strdup(b_quot);
	if (!search)
		return (0);
	while (search[i] == '\"')
	{
		if (search[i++] == '$')
			i += expand_env(&search, &search + i, env);
	}
	final = join_and_free(pre_quot, search);
	if (!final)
		return (0);
	free(search);
	*arg = final;
	return (i);
}

int		to_next_quote(char *arg, char quot)
{
	int		i;

	i = 0;
	while (arg[i] != quot)
		i++;
	if (arg[i] != quot)
		return (-1);
	else
		return (i + 1);
}
char	*skip_quoting(char *arg, char **env)
{
	int	i;
	
	i = 0;
	change_expand(&arg, env);
	while (arg[i])
	{
		if (arg[i] == -2)
			i++;
		else if (arg[i] == '\"' || arg[i] == '\'')
		{
			if (to_next_quote(arg + i + 1, arg[i]) == -1)
				return (NULL); //error
			else
				i += to_next_quote(arg + i + 1, arg[i]);
		}
		arg[i] = check_ifs(arg[i]);
		i++;
	}
	return (arg);
}
