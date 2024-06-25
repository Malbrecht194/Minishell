/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:54:21 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/25 17:38:40 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

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
		check_expand(&init->str, minish);
	return (i);
}

static int	set_init(t_init **f_init, t_init *init, t_minishell *minish,
		char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (init->type == INFILE || init->type == OUT_T || init->type == PIPE)
		i++;
	else if (init->type == HEREDOC || init->type == OUT_A)
		i += 2;
	j = i;
	if (!(init->type == PIPE || init->type == -1))
	{
		k = skip_ifs(str + i);
		i += creat_arg(f_init, &str[k + i], minish, init);
		if (i - j < 0)
			return (-1);
	}
	return (i + k);
}

t_init	*init_lexor(t_init **f_init, char *rl_args, t_minishell *minish)
{
	int		i;
	int		j;
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
	j = set_init(f_init, init, minish, rl_args + i);
	if (!f_init)
		f_init = &init;
	ft_initadd_back(&init, init_lexor(f_init, rl_args + i + j, minish));
	if (!f_init && init)
		ft_initclear(&init);
	return (init);
}
