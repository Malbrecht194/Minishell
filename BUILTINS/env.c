/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:10:46 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/28 15:10:51 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/builtins.h"

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

int	ft_env(int ac, char **av, char ***envp)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	while (envp[i])
		printf("%s\n", (*envp)[i++]);
	return (0);
}
