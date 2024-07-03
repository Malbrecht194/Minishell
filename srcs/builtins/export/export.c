/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:57:49 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <expand.h>

void	new_env(char ***env, char *av, int b_count, int *error)
{
	int		i_env;
	char	*env_name;

	env_name = ft_substr(av, 0, b_count - 1);
	if (!env_name)
	{
		*error = 1;
		return ;
	}
	i_env = check_env(*env, env_name);
	free(env_name);
	if (i_env == -1)
	{
		if (no_env(av, env))
			*error = 1;
	}
	else if (!ft_strchr(av, '='))
		return ;
	else if (replace_env(av, &((*env)[i_env])))
		*error = 1;
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
	if (i_env == -1)
		new_env(env, av, b_count, error);
	else
	{
		if (!ft_strchr((*env)[i_env], '='))
			env_name = join_and_free(ft_strjoin((*env)[i_env], "="),
					av + b_count - 1, 1, 0);
		else
			env_name = ft_strjoin((*env)[i_env], av + b_count - 1);
		if (!(env_name && !replace_env(env_name, &((*env)[i_env]))))
			*error = 1;
		free(env_name);
	}
}

int	no_arg(t_exec *cmd, t_minishell *minish)
{
	char	**n_arg;

	n_arg = sort_env(minish->env);
	if (!n_arg)
		return (1);
	if (check_env(n_arg, "_") != -1)
		change_env(check_env(n_arg, "_"), &n_arg);
	if (declare_x(&n_arg, 0))
	{
		ft_free_2d_array(n_arg, ft_array_len(n_arg));
		return (1);
	}
	print_array(cmd->fd_out, n_arg);
	ft_free_2d_array(n_arg, ft_array_len(n_arg));
	return (0);
}

int	export_type(char **av, char ***env, t_minishell *minish)
{
	int	i;
	int	error;
	int	content;

	i = 0;
	error = 0;
	while (av[++i])
	{
		if (!export_error(av[i], minish))
		{
			error = 1;
			continue ;
		}
		content = check_export_type(av[i]);
		if (content == -1)
			error = 1;
		else if (content < 0)
			cat_env(env, av[i], ft_abs(content), &error);
		else if (content > 0)
			new_env(env, av[i], content, &error);
		else if (!content)
			new_env(env, av[i], ft_strlen(av[i]) + 1, &error);
	}
	return (error);
}

int	ft_export(int ac, char **av, t_exec *cmd, t_minishell *minish)
{
	int		error;

	error = 0;
	if (ac == 1)
		error = no_arg(cmd, minish);
	else
		error = export_type(av, &minish->env, minish);
	return (error);
}
