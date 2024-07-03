/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:10:46 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

static int	envp_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && (ft_isalnum(env[i]) || env[i] == '_'))
		i++;
	if (env[i] != '=' && !(ft_isalnum(env[i]) || env[i] == '_'))
		return (-1);
	else if (env[i] != '=')
		return (1);
	return (i);
}

char	*ft_getenv(char *to_get, char **env)
{
	int		i;

	i = 0;
	if (!to_get || !env || !*env)
		return (NULL);
	while (env[i] && ft_strncmp(to_get, env[i], ft_strlen(to_get)))
		i++;
	if (env[i] && !ft_strncmp(to_get, env[i], ft_strlen(to_get))
		&& env[i][ft_strlen(to_get)] == '=')
		return (env[i] + envp_size(env[i]) + 1);
	else if (env[i] && !ft_strncmp(to_get, env[i], ft_strlen(to_get))
		&& env[i][ft_strlen(to_get)] != '=')
		return (ft_getenv(to_get, &env[i + 1]));
	else
		return (NULL);
}

int	ft_env(int ac, char **av, t_exec *cmd, t_minishell *minish)
{
	int	i;

	i = -1;
	if (ac > 1)
	{
		error_handle(TOO_MANY_ARGS, minish, av[0], NULL);
		return (1);
	}
	if (!minish->env)
		return (1);
	while (minish->env[++i])
	{
		if (ft_strchr(minish->env[i], '='))
			ft_printf_fd(cmd->fd_out, "%s\n", minish->env[i]);
	}
	return (0);
}
