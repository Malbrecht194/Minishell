/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_rl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/05 11:27:01 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/expand.h"
#include "../../INCLUDES/minishell.h"

void	delete_quote(char **arg)
{
	int		i;
	int		to_quote;
	int		state;
	char	quote;
	
	i = 0;
	state = 0;
	while ((*arg)[i])
	{
		quote = -3;
		if ((*arg)[i] == -2)
			rm_char(arg, i);
		else if ((*arg)[i] == '\'' || (*arg)[i] == '\"')
		{
			if (state++ % 2 == 0)
				quote = (*arg)[i];
			to_quote = to_next_quote((*arg) + i + 1, quote);
			if (to_quote == -1)
				to_quote = 0;
			rm_char(arg, i);
			i += to_quote - 1;
		}
		i++;
	}
}

int		to_next_quote(char *arg, char quot)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != quot)
		i++;
	if (arg[i] != quot)
		return (-1);
	else
		return (i);
}

void	check_expand(char **arg, char **env)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '<' && (*arg)[i + 1] == '<')
			i += skip_heredoc(*arg, i);
		if ((*arg)[i] == '\"')
			do_expand(arg, &i, '\"', env);
		else if ((*arg)[i] == '\'')
			i += to_next_quote((*arg) + i + 1, '\'') + 1;
		else if ((*arg)[i] == '$')
			do_expand(arg, &i, 0, env);
		i++;
		if (i >= (int)ft_strlen(*arg))
			break ;
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
				i += to_next_quote((*arg) + i + 1, (*arg)[i]) + 1;
		}
		(*arg)[i] = check_ifs((*arg)[i]);
		if (i >= ft_strlen(*arg))
			break ;
		i++;
	}
	delete_quote(arg);
	return ;
}
