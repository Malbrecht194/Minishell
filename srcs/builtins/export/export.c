/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:57:49 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 14:02:33 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <expand.h>

void	new_env(char ***env, char *av, int b_count, int *error)
{
	int		i_env;
	char	*env_name;

	env_name = ft_substr(av, 0, b_count - 2);
	if (!env_name)
	{
		*error = 1;
		return ;
	}
	i_env = check_env(*env, env_name);
	free(env_name);
	if (!i_env)
	{
		if (no_env(av, env))
		{
			*error = 1;
			return ;
		}
	}
	else if (replace_env(av, &((*env)[i_env])))
	{
		*error = 1;
		return ;
	}
}

void	cat_env(char ***env, char *av, int b_count, int *error)
{
	int		i_env;
	char	*env_name;

	rm_char(&av, b_count - 2);
	env_name = ft_substr(av, 0, b_count - 2);
	if (!env_name)
	{
		*error = 1;
		return ;
	}
	i_env = check_env(*env, env_name);
	free (env_name);
	if (!i_env)
		new_env(env, av, b_count, error);
	else
	{
		env_name = ft_strjoin((*env)[i_env], av + b_count - 1);
		if (!env_name || replace_env(env_name, &((*env)[i_env])))
		{
			*error = 1;
			return ;
		}
		free(env_name);
	}
}

int	export_type(char **av, char ***env)
{
	int	i;
	int	error;
	int	content;

	i = 0;
	error = 0;
	while (av[++i])
	{
		content = check_export_type(av[i]);
		if (!content)
			continue ;
		else if (content == -1)
			error = 1;
		else if (content < 0)
			cat_env(env, av[i], ft_abs(content), &error);
		else if (content > 0)
			new_env(env, av[i], content, &error);
	}
	return (error);
}

int	no_arg(t_chris *cmd, t_minishell *minish)
{
	char	**n_arg;

	n_arg = sort_env(minish->env);
	if (!n_arg)
		return (1);
	if (check_env(n_arg, "_"))
		change_env(check_env(n_arg, "_"), &n_arg);
	if (declare_x(&n_arg, 0))
	{
		ft_free_2d_array((void **)n_arg);
		return (1);
	}
	print_array(cmd->fd_out, n_arg);
	ft_free_2d_array((void **)n_arg);
	return (0);
}

int	ft_export(int ac, char **av, t_chris *cmd, t_minishell *minish)
{
	int	error;
	int	i;
	int	j;

	i = 0;
	j = -1;
	error = 0;
	while (av[++i])
	{
		if (ft_isdigit(av[i][0]))
			return (1);
		while (!(av[i][++j] == '='
			|| (av[i][j] == '+' && av[i][j + 1] == '=')) && av[i][j])
		{
			if (!ft_isalnum(av[i][j]) && av[i][j] != '_')
				return (1);
		}
	}
	if (ac == 1)
		error = no_arg(cmd, minish);
	else
		error = export_type(av, &minish->env);
	return (error);
}

