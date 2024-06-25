/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:08:06 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/25 17:38:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_access(char **paths, char *cmd)
{
	int		i;
	char	*tmp_cmd;
	char	*tmp_path;

	i = 0;
	tmp_cmd = ft_strjoin("/", cmd);
	if (!tmp_cmd)
		return (NULL);
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], tmp_cmd);
		if (!tmp_path)
			return (NULL);
		if (access(tmp_path, F_OK | X_OK) == 0)
			break ;
		free(tmp_path);
		i++;
	}
	free(tmp_cmd);
	if (!paths[i])
		return (NULL);
	return (tmp_path);
}

char	**get_path(char **env)
{
	char	*paths;
	char	**split_path;

	paths = ft_getenv("PATH", env);
	if (!paths)
		return (NULL);
	split_path = ft_split(paths, ':');
	if (!split_path)
		return (NULL);
	return (split_path);
}

char	*test_access(char *command, t_minishell *minish)
{
	char	**exe_path;
	char	*tmp_path;

	if (!command[0])
		error_handle(NO_CMD, minish, command, exit);
	if (ft_strchr(command, '/'))
		return (command);
	exe_path = get_path(minish->env);
	if (!exe_path)
		error_handle(NO_CMD, minish, command, exit);
	tmp_path = check_access(exe_path, command);
	ft_free_2d_array(exe_path, ft_array_len(exe_path));
	if (!tmp_path)
		error_handle(NO_CMD, minish, command, exit);
	return (tmp_path);
}
