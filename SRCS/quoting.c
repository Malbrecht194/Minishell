/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:43:02 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/08 16:35:52 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	change_quoting(char **to_change)
{
	int		i;
	int		len;
	char	**tmp;
	char	*s_env;

	i = 1;
	tmp = ft_split(*to_change, '$');
	while (tmp[i])
	{
		len = 0;
		while(ft_isalnum(tmp[i][len]))
			len++;
		s_env = ft_substr(tmp[i], 0, len);
		if (!getenv(s_env))
			tmp[0] = join_and_free(tmp[0], "");
		else
			tmp[0] = join_and_free(tmp[0], getenv(s_env));
		tmp[0] = join_and_free(tmp[0], tmp[i] + len);
		free(s_env);
		i++;
	}
	free(*to_change);
	*to_change = ft_strdup(tmp[0]);
	ft_free_2d_array((void **)tmp);
}

void	check_quoting(t_pipex **l_list)
{
	int		i;
	int		j;
	t_pipex	*tmp;

	tmp = *l_list;
	i = 1;
	while (tmp)
	{
		j = 0;
		while (tmp->cmd.flags[i])
		{
			if (ft_strstr(tmp->cmd.flags[i], "\""))
				change_quoting(&tmp->cmd.flags[i]);
			else if (!ft_strstr(tmp->cmd.flags[i], "\"")
				&& !ft_strstr(tmp->cmd.flags[i], "\'"))
				change_quoting(&tmp->cmd.flags[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

char	check_ifs(char a_char)
{
	int		i;
	char	*ifs;

	i = 0;
	ifs = IFS;
	while (ifs[i])
	{
		if (a_char == ifs[i])
			return (1);
		i++;
	}
	return (a_char);
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
char	*skip_quoting(char *arg)
{
	int	i;
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
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
