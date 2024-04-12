/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:54:21 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/12 10:04:38 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

int	check_rl_args(char *rl)
{
	size_t		i;
	int			j;
	int			type;
	int			state;

	i = 0;
	i += skip_ifs(rl);
	if (rl[i] == '|')
		return (0);
	while (rl[i])
	{
		state = 0;
		type = check_type(&rl[i]);
		if (type == INFILE || type == OUT_T || type == PIPE)
			state = 1;
		else if (type == HEREDOC || type == OUT_A)
			state = 2;
		j = i + skip_ifs(&rl[i + state]);
		if (state && (rl[j + state] == '<' || rl[j + state] == '>' || rl[j + state] == '|'))
			return (0);
		if (skip_ifs(rl + ++i))
			i += skip_ifs(rl + i);
	}
	return (1);
}

void	check_ambigous(char *str, t_init *init)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_ifs(str[i++]) == -1)
		{
			//ambigous redirect
			init->error = 1;
		}
	}
}

int	creat_arg(char *str, char **env, t_init *init)
{
	int		i;
	char	*n_str;

	i = 0;
	if (!str[i])
	{
		free(init);
		return (-1);
	}
	while (str[i] && !is_ifs(str[i]) && str[i] != '|' 
			&& str[i] != '<' && str[i] != '>')
			i++;
	n_str = ft_substr(str, 0, i);
	if (!n_str)
	{
		init->error = 1;
		return (0);
	}
	if (init->type != HEREDOC)
		check_expand(&n_str, env);
	if (!(init->type == ARG || init->type == HEREDOC))
		check_ambigous(n_str, init);
	init->str = n_str;
	return (i);
}

t_init	*init_lexor(char *rl_args, char **env)
{
	int			i;
	int			j;
	t_init	*init;

	if (!rl_args || !*rl_args)
		return (NULL);
	i = skip_ifs(rl_args);
	j = 0;
	init = ft_calloc(sizeof(t_init), 1);
	if (!init)
		return (NULL);
	init->type = check_type(rl_args + i);
	if (init->type == INFILE || init->type == OUT_T || init->type == PIPE)
			j++;
	else if (init->type == HEREDOC || init->type == OUT_A)
		j += 2;
	if (!(init->type == PIPE || init->type == -1))
	{
		i += skip_ifs(rl_args + i + j);
		if (creat_arg(&rl_args[i + j], env, init) == -1)
			return (NULL);
		j += creat_arg(&rl_args[i + j], env, init);
	}
	ft_initadd_back(&init, init_lexor(rl_args + i + j, env));
	return (init);
}
