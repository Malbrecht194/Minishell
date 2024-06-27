/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_rl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/27 15:23:40 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>
#include <minishell.h>

void	delete_quote(char **arg)
{
	int	i;
	int	state;

	i = 0;
	while ((*arg)[i])
	{
		state = 1;
		if ((*arg)[i] == -2)
		{
			rm_char(arg, i);
			state = 1;
		}
		else if ((*arg)[i] == '\'' || (*arg)[i] == '\"')
		{
			rm_char(arg, i);
			state = 0;
		}
		i += state;
	}
}

int	to_next_quote(char *arg, char quote)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != quote)
		i++;
	if (arg[i] != quote)
		return (-1);
	else
		return (i);
}

void	check_expand(char **arg, t_minishell *minish)
{
	int	i;
	int	j;

	i = 0;
	while ((*arg)[i])
	{
		j = i - 1;
		if ((*arg)[i] == '\"')
		{
			if (do_quote_expand(arg, &i, minish))
				check_arg_quotes(arg, j + 1, '\"');
		}
		else if ((*arg)[i] == '\'')
			i += to_next_quote((*arg) + i + 1, '\'') + 1;
		else if ((*arg)[i] == '$')
		{
			if (do_simple_expand(arg, &i, minish) >= 0)
				i--;
			while (++j < i + 1)
				(*arg)[j] = check_ifs((*arg)[j]);
		}
		i++;
		if (i >= (int)ft_strlen(*arg) || !(*arg)[i])
			break ;
	}
}

int	check_arg_quotes(char **arg, int index, char quote)
{
	int		i;
	char	minus_two[2];
	char	*tmp;

	i = 0;
	minus_two[0] = -2;
	minus_two[1] = 0;
	tmp = NULL;
	while ((*arg)[index + i] && (*arg)[index + i] != quote)
	{
		if ((*arg)[index + i] == -2)
			i++;
		else if ((*arg)[index + i] == '\'' || (*arg)[index + i] == '\"')
		{
			tmp = join_and_free(ft_substr(*arg, 0, index + i), minus_two, 1, 0);
			tmp = join_and_free(tmp, (*arg) + index + i, 1, 0);
			if (!tmp)
				return (0);
			free(*arg);
			*arg = tmp;
			return (check_arg_quotes(arg, index + i + 2, quote) + i + 2);
		}
		i++;
	}
	return (i);
}

void	format_rl(char **arg, t_minishell *minish)
{
	size_t	i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\"' || (*arg)[i] == '\'')
		{
			if (to_next_quote((*arg) + i + 1, (*arg)[i]) == -1)
			{
				free(*arg);
				*arg = NULL;
				minish->last_error = 2;
				error_handle(NO_END_QUOTE, minish, NULL, NULL);
				return ;
			}
			else
				i += check_arg_quotes(arg, i + 1, (*arg)[i]) + 1;
		}
		(*arg)[i] = check_ifs((*arg)[i]);
		if (i >= ft_strlen(*arg))
			break ;
		i++;
	}
}
