/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:29:29 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/25 18:05:58 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

int	check_export_type(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || (arg[0] == '+' && arg[1] == '='))
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (- (i + 2));
		else if (arg[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	env_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && (ft_isalnum(env[i]) || env[i] == '_'))
		i++;
	if (env[i] != '=' && !(ft_isalnum(env[i]) || env[i] == '_'))
		return (-1);
	else if (env[i] != '=')
		return (-2);
	return (i);
}

void	swap_string(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**sort_env(char **env)
{
	char	**tmp;
	size_t	size;
	int		i;

	i = 0;
	tmp = dup_array(env);
	if (!tmp)
		return (NULL);
	while (tmp[i] && tmp[i + 1])
	{
		size = ft_strlen(tmp[i]) + 1;
		if (tmp[i + 1] && ft_strncmp(tmp[i], tmp[i + 1], size) > 0)
		{
			swap_string(&tmp[i], &tmp[i + 1]);
			i = -1;
		}
		i++;
	}
	return (tmp);
}

int	declare_x(char ***envp, int i)
{
	int		size;
	char	*n_env;

	if (!(*envp)[i])
		return (0);
	size = env_size((*envp)[i]) + 1;
	if (size == 0 || size == -1)
		size = ft_strlen((*envp)[i]);
	n_env = ft_substr((*envp)[i], 0, size);
	if (!n_env)
		return (1);
	n_env = join_and_free("declare -x ", n_env, 0, 1);
	if (env_size((*envp)[i]) != -1 && env_size((*envp)[i]) != -2)
	{
		n_env = join_and_free(n_env, "\"", 1, 0);
		n_env = join_and_free(n_env, (*envp)[i] + size, 1, 0);
		n_env = join_and_free(n_env, "\"", 1, 0);
	}
	if (!n_env)
		return (1);
	free((*envp)[i]);
	(*envp)[i] = n_env;
	return (declare_x(envp, i + 1));
}
