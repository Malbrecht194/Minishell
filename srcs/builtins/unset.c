/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:26 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

void	remake_env(t_minishell *minish)
{
	char	**e_tmp;

	e_tmp = dup_array(minish->env);
	if (!e_tmp)
		return ;
	ft_free_2d_array(minish->env, ft_array_len(minish->env));
	minish->env = e_tmp;
	return ;
}

void	change_env(int to_del, char ***env)
{
	int		i;
	int		env_size;

	i = to_del;
	env_size = ft_array_len(*env);
	free((*env)[i]);
	while (i < env_size)
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
}

int	check_env(char **env, char *av)
{
	int	i;
	int	av_len;

	i = 0;
	if (!env)
		return (-1);
	av_len = ft_strlen(av);
	while (env[i])
	{
		if (!ft_strncmp(env[i], av, av_len) && \
			(env[i][av_len] == '=' || !env[i][av_len]))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unset(int ac, char **av, t_exec *cmd, t_minishell *minish)
{
	int	i;
	int	tmp;

	i = 0;
	(void)cmd;
	if (ac == 1)
		return (0);
	while (av[++i])
	{
		tmp = check_env(minish->env, av[i]);
		if (tmp == -1)
			continue ;
		change_env(tmp, &minish->env);
	}
	remake_env(minish);
	return (0);
}
