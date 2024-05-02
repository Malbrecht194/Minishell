/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:29:29 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/02 22:59:29 by xeo              ###   ########.fr       */
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
