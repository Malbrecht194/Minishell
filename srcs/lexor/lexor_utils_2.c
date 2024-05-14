/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:56:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 14:56:23 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

int	check_syntax_err(int state, int type, char *rl, t_minishell *minish)
{
	if (state && (((type == INFILE || type == OUT_T
					|| type == HEREDOC || type == OUT_A)
				&& (rl[state] == '<' || rl[state] == '>'
					|| rl[state] == '|' || rl[state] == 0))
			|| (type == PIPE && (rl[state] == '|' || rl[state] == 0))))
	{
		minish->last_error = 2;
		if ((type == INFILE || type == OUT_T || type == HEREDOC
				|| type == OUT_A) && rl[state] == 0)
			error_handle(SYNTAX_ERROR, minish, "newline", NULL);
		else
			error_handle(SYNTAX_ERROR, minish, &rl[state], NULL);
		return (0);
	}
	return (1);
}

int	check_str_syntax(char *rl, int i, t_minishell *minish)
{
	int	state;
	int	type;
	int	j;

	while (rl[i])
	{
		state = 0;
		if (rl[i] == '\'' || rl[i] == '\"')
			i += to_next_quote(rl + i + 1, rl[i]) + 1;
		type = check_type(&rl[i]);
		if (type == INFILE || type == OUT_T || type == PIPE)
			state = 1;
		else if (type == HEREDOC || type == OUT_A)
			state = 2;
		j = i + skip_ifs(&rl[i + state]);
		if (!check_syntax_err(state, type, rl + j, minish))
			return (0);
		if (skip_ifs(rl + ++i))
			i += skip_ifs(rl + i);
	}
	return (1);
}

int	check_rl_args(char *rl, t_minishell *minish)
{
	size_t	i;

	i = skip_ifs(rl);
	if (!rl[i])
	{
		free(rl);
		return (0);
	}
	if (rl[i] == '|')
	{
		minish->last_error = 2;
		error_handle(SYNTAX_ERROR, minish, &rl[i], NULL);
		return (0);
	}
	if (!check_str_syntax(rl, i, minish))
		return (0);
	return (1);
}

t_init	*relink_node(t_init *first, t_init *last, \
	t_init *node, t_minishell *minish)
{
	char	**arg;
	char	*str;
	t_init	*new;
	int		i;

	i = 0;
	arg = mini_split(node->str, -1);
	if (!arg)
	{
		ft_initclear(&first);
		ft_initclear(&last);
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	free(node->str);
	node->str = arg[0];
	if (!arg[1])
	{
		free(arg[1]);
		free(arg);
		node->next = last;
		return (first);
	}
	new = ft_calloc(sizeof(t_init), 1);
	if (!new)
	{
		ft_free_2d_array(arg, ft_array_len(arg));
		ft_initclear(&first);
		ft_initclear(&last);
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	new->type = ARG;
	str = ft_unsplit(arg + 1, -1);
	if (!str)
	{
		ft_free_2d_array(arg, ft_array_len(arg));
		ft_initclear(&first);
		ft_initclear(&last);
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	while (arg[++i])
		free(arg[i]);
	free(arg);
	new->str = str;
	node->next = new;
	return (relink_node(first, last, new, minish));
}
