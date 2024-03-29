/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_rl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/29 09:49:23 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/expand.h"

char	*delete_quote(char **arg, char *to_check, char a_quote, int index)
{
	int		i;
	int		j;
	int		to_n_quot;

	i = 0;
	j = -1;
	while (to_check[i])
	{
		if ((a_quote == 0 && (to_check[i] == '\'' || to_check[i] == '\"'
			|| to_check[i] == -2)) || to_check[i] == a_quote)
		{
			to_n_quot = to_next_quote(&to_check[i + 1], to_check[i]) - 1;
			while ((*arg)[index + i + ++j])
				(*arg)[index + i + j] = (*arg)[index + i + j + 1];
			return (delete_quote(arg, (*arg) + index + i + to_n_quot,
				(*arg)[i + index + to_n_quot], index + i + to_n_quot));
		}
		i++;
	}
	return (*arg);
}

int		to_next_quote(char *arg, char quot)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != quot)
		i++;
	if (arg[i] && arg[i] != quot)
		return (-1);
	else
		return (i + 1);
}

void	check_expand(char **arg, char **env)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '<' && (*arg)[i + i] == '<')
			i += skip_heredoc(*arg, i);
		if ((*arg)[i] == '\"')
			do_expand(arg, &i, '\"', env);
		else if ((*arg)[i] == '\'')
			i += to_next_quote((*arg) + i + 1, '\'');
		else if ((*arg)[i] == '$')
			do_expand(arg, &i, 0, env);
		if (i >= (int)ft_strlen(*arg))
			break ;
		i++;
	}
}

void	format_rl(char **arg, char **env)
{
	size_t	i;
	
	i = 0;
	check_expand(arg, env);
	while ((*arg)[i])
	{
		if ((*arg)[i] == -2)
			i++;
		else if ((*arg)[i] == '\"' || (*arg)[i] == '\'')
		{
			if (to_next_quote((*arg) + i + 1, (*arg)[i]) == -1)
				return ; //error
			else
				i += to_next_quote((*arg) + i + 1, (*arg)[i]);
		}
		(*arg)[i] = check_ifs((*arg)[i]);
		if (i >= ft_strlen(*arg))
			break ;
		i++;
	}
	return ;
}
