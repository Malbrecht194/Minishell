/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:08:06 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/07 20:42:46 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*check_access(char **paths, char *cmd)
{
	int		i;
	int		access_state;
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
		access_state = access(tmp_path, F_OK | X_OK);
		if (access_state == 0)
			break ;
		free(tmp_path);
	}
	free(tmp_cmd);
	if (access_state == -1)
		return (NULL);
	return (tmp_path);
}

char	**get_flags(char *command, char *access)
{
	char	**flags;

	flags = ft_split(command, 1);
	if (!flags || !*flags)
		return (NULL);
	free(flags[0]);
	flags[0] = access;
	return (flags);
}

char	**get_path(void)
{
	char	*paths;
	char	**split_path;

	paths = ft_strjoin("./BUILTINS:", getenv("PATH"));
	if (!paths)
		return(NULL);
	split_path = ft_split(paths, ':');
	if (!split_path)
		return (NULL);
	free(paths);
	return (split_path);
}

char	*test_access(char *command)
{
	char	**exe_path;
	char	*tmp_path;
	char	**if_flags;

	if_flags = ft_split(command, 1);
	if (!if_flags)
		return (NULL);
	if (access(if_flags[0], F_OK | X_OK) == 0)
	{
		tmp_path = ft_strdup(if_flags[0]);
		if (!tmp_path)
			return (NULL);
		ft_free_2d_array((void **)if_flags);
		return (tmp_path);
	}
	exe_path = get_path();
	if (!exe_path)
		return (NULL);
	tmp_path = check_access(exe_path, if_flags[0]);
	ft_free_2d_array((void **)if_flags);
	ft_free_2d_array((void **)exe_path);
	if (!tmp_path)
		return (NULL);
	return (tmp_path);
}

