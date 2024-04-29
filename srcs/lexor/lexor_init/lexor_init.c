/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:54:21 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/24 13:20:25 by xeo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

int	check_rl_args(char *rl, t_minishell *minish)
{
	size_t	i;
	int		j;
	int		type;
	int		state;

	i = skip_ifs(rl);
	if (rl[i] == '|')
	{
		minish->last_error = 2;
		error_handle(SYNTAX_ERROR, minish, &rl[i], NULL);
		return (0);
	}
	while (rl[i])
	{
		state = 0;
		if (!check_quote(rl, i, minish))
			return (0);
		if (rl[i] == '\'' || rl[i] == '\"')
			i += to_next_quote(rl + i + 1, rl[i]) + 1;
		type = check_type(&rl[i]);
		if (type == INFILE || type == OUT_T || type == PIPE)
			state = 1;
		else if (type == HEREDOC || type == OUT_A)
			state = 2;
		j = i + skip_ifs(&rl[i + state]);
		if (state && (((type == INFILE || type == OUT_T || type == HEREDOC
						|| type == OUT_A) && (rl[j + state] == '<' || rl[j
						+ state] == '>' || rl[j + state] == '|' || rl[j + state] == 0)) || (type == PIPE
					&& (rl[j + state] == '|' || rl[j + state] == 0))))
		{
			minish->last_error = 2;
			if ((type == INFILE || type == OUT_T || type == HEREDOC
					|| type == OUT_A) && rl[j + state] == 0)
				error_handle(SYNTAX_ERROR, minish, "newline", NULL);
			else
				error_handle(SYNTAX_ERROR, minish, &rl[j + state], NULL);
			return (0);
		}
		if (skip_ifs(rl + ++i))
			i += skip_ifs(rl + i);
	}
	return (1);
}

int	check_ambigous(char *str, t_minishell *minish)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_ifs(str[i++]))
		{
			error_handle(AMBIGOUS_REDIR, minish, NULL, NULL);
			return (0);
		}
	}
	return (1);
}

int	creat_arg(t_init **f_init, char *str, t_minishell *minish, t_init *init)
{
	int	i;

	i = 0;
	if (!str[i])
	{
		free(init);
		return (-1);
	}
	while (str[i] && !is_ifs(str[i]) && str[i] != '|' && str[i] != '<'
		&& str[i] != '>')
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += to_next_quote(str + i + 1, str[i]) + 1;
		i++;
	}
	init->str = ft_substr(str, 0, i);
	if (!init->str)
	{
		ft_initclear(f_init);
		return (-2);
	}
	if (init->type != HEREDOC)
	{
		check_expand(&init->str, minish);
		delete_quote(&init->str);
	}
	return (i);
}

t_init	*init_lexor(t_init **f_init, char *rl_args, t_minishell *minish)
{
	int		i;
	int		j;
	int		k;
	t_init	*init;

	i = skip_ifs(rl_args);
	if (!rl_args || !rl_args[i])
		return (NULL);
	j = 0;
	init = ft_calloc(sizeof(t_init), 1);
	if (!init)
	{
		ft_initclear(f_init);
		return (NULL);
	}
	init->type = check_type(rl_args + i);
	if (init->type == INFILE || init->type == OUT_T || init->type == PIPE)
		j++;
	else if (init->type == HEREDOC || init->type == OUT_A)
		j += 2;
	k = j;
	if (!(init->type == PIPE || init->type == -1))
	{
		i += skip_ifs(rl_args + i + j);
		j += creat_arg(f_init, &rl_args[i + j], minish, init);
		if (j - k < 0)
			return (NULL);
	}
	if (!f_init)
		ft_initadd_back(&init, init_lexor(&init, rl_args + i + j, minish));
	else
		ft_initadd_back(&init, init_lexor(f_init, rl_args + i + j, minish));
	return (init);
}
