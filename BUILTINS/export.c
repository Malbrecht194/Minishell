/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:17:29 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/20 11:17:52 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/builtins.h"

int	env_size(char *env)
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

int	replace_env(char *n_env, char **o_env)
{
	char	*tmp;

	tmp = ft_strdup(n_env);
	if (!tmp)
		return (1);
	free(*o_env);
	*o_env = tmp;
	return (0);
}

int	no_env(char *n_env, char ***o_env)
{
	size_t	arg_size;
	char	**tmp;
	int		i;

	i = 0;
	arg_size = ft_array_len(*(void **)o_env);
	tmp = ft_calloc(sizeof(char *), arg_size + 2);
	if (!tmp)
		return (1);
	while ((*o_env)[i])
	{
		tmp[i] = (*o_env)[i];
		i++;
	}
	tmp[i] = ft_strdup(n_env);
	if (!tmp[i])
	{
		free(tmp);
		return (1);
	}
	free(*o_env);
	*o_env = tmp;
	return (0);
}

int	ft_export(int ac, char **av, char ***env)
{
	int	env_len;
	int	i;
	int	j;
	int	error;

	j = 0;
	error = 0;
	(void)ac;
	while (av[++j])
	{
		i = 0;
		env_len = env_size(av[j]);
		if (env_len++ == -1)
			error++;
		if (!env_len || env_len == 1)
			continue ;
		while ((*env)[i] && ft_strncmp((*env)[i], av[j], env_len))
			i++;
		if ((*env)[i] && !ft_strncmp((*env)[i ], av[j], env_len))
			error += replace_env(av[j], &((*env)[i]));
		else
			error += no_env(av[j], env);
	}
	return (error);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	**dupped_env;
// 	int		i;
// 	int		j;

// 	dupped_env = dup_array(env);
// 	i = 1;
// 	j = 0;
// 	while (dupped_env[j++])
// 		printf("%s\n",env[j]);
// 	ft_export(ac, av, &dupped_env);
// 	j = 0;
// 	printf("\n\n");
// 	while (dupped_env[j])
// 		printf("%s\n",dupped_env[j++]);
// 	ft_free_2d_array((void **)dupped_env);
// }
