/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:08:06 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/03 11:29:07 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*check_access(char **paths, char *cmd)
{
	int		i;
	char	*tmp_cmd;
	char	*tmp_path;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	tmp_cmd = ft_strjoin("/", cmd);
	if (!tmp_cmd)
		return (NULL);
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i++], tmp_cmd);
		if (!tmp_path)
			return (NULL);
		if (access(tmp_path, F_OK | X_OK) == 0)
			break ;
		free(tmp_path);
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

char	*test_access(char *command, char **env)
{
	char	**exe_path;
	char	*tmp_path;

	if (access(command, F_OK | X_OK) == 0)
		return (command);
	exe_path = get_path(env);
	if (!exe_path)
		return (NULL);
	tmp_path = check_access(exe_path, command);
	ft_free_2d_array((void **)exe_path);
	free(command);
	if (!tmp_path)
		return (NULL);
	return (tmp_path);
}

