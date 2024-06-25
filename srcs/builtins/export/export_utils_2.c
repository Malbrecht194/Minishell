/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:29:29 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/25 18:20:00 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

int	replace_env(char *n_env, char **o_env)
{
	char	*tmp;

	if (!n_env || !o_env || !*o_env)
		return (1);
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
	arg_size = ft_array_len(*o_env);
	tmp = ft_calloc(sizeof(char *), arg_size + 2);
	if (!tmp)
		return (1);
	while ((*o_env) && (*o_env)[i])
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
	if (*o_env)
		free(*o_env);
	*o_env = tmp;
	return (0);
}

void	print_array(int fd_out, char **array)
{
	int	i;

	i = 0;
	while (array[i])
		ft_printf_fd(fd_out, "%s\n", array[i++]);
}

int	export_error(char *str, t_minishell *minish)
{
	char	*error[3];
	int		i;

	i = -1;
	error[0] = "export";
	error[1] = str;
	error[2] = NULL;
	if (!str[0] || ft_isdigit(str[0]) || str[0] == '=')
	{
		error_handle(NOT_VALID_ID, minish, error, NULL);
		return (0);
	}
	while (!(str[++i] == '=' || (str[i] == '+' && str[i + 1] == '=')) && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			error_handle(NOT_VALID_ID, minish, error, NULL);
			return (0);
		}
	}
	return (1);
}
