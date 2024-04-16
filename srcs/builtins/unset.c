/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:11:26 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 13:29:53 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

void	remake_env(char ***env)
{
	char	**e_tmp;
	int		i;

	i = 0;
	e_tmp = dup_array(*env);
	if (!e_tmp)
		return ;
	*env = e_tmp;
	return ;
}

void	change_env(int to_del, char ***env)
{
	int		i;
	int		env_size;
	char	**e_tmp;

	i = to_del;
	e_tmp = *env;
	env_size = ft_array_len((void **)e_tmp);
	free(e_tmp[i]);
	while (i < env_size)
	{
		e_tmp[i] = e_tmp[i + 1];
		i++;
	}
	*env = e_tmp;
}

int	check_env(char **env, char *av)
{
	int	i;
	int	av_len;

	i = 0;
	av_len = ft_strlen(av);
	while (env[i])
	{
		if (!ft_strncmp(env[i], av, av_len) && env[i][av_len] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	ft_unset(int ac, char **av, t_chris *cmd, t_minishell *minish)
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
		if (!tmp)
		{
			i++;
			continue ;
		}
		change_env(tmp, &minish->env);
	}
	remake_env(&minish->env);
	return (0);
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
// 	ft_unset(ac, av, &dupped_env);
// 	j = 0;
// 	printf("\n\n");
// 	while (dupped_env[j])
// 		printf("%s\n",dupped_env[j++]);
// 	ft_free_2d_array((void **)dupped_env);
// }
