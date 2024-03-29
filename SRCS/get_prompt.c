/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:19:24 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/22 09:49:37 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"


char	*first_part(void)
{
	char	*login;
	char	*location;
	char	*tmp;
	char	*error;

	error = ft_strdup("USER@minishell:");
	login = "USER";
	if (getenv("USER"))
		login = getenv("USER");
	location = "\001\033[32m\002minishell";
	tmp = ft_strjoin("\001\033[37m\002", login);
	if (!tmp)
		return (error);
	tmp = join_and_free(tmp, "\001\033[31m\002@");
	if (!tmp)
		return (error);
	tmp = join_and_free(tmp, location);
	tmp = join_and_free(tmp, ":");
	if (!tmp)
		return (error);
	if (error)
		free(error);
	return (tmp);
}

char	*check_home(char *home, char *cwd)
{
	size_t		i;
	char		*pwd;
	char		*tmp;

	i = 0;
	while (home && home[i] == cwd[i])
		i++;
	if (home && i == ft_strlen(home))
	{
		tmp = ft_substr(cwd, i, ft_strlen(pwd) - ft_strlen(home));
		if (!tmp)
			return (NULL);
		pwd = ft_strjoin("\001\033[36m\002~", tmp);
		free(tmp);
	}
	else
		pwd = ft_strjoin("\001\033[36m\002", cwd);
	if (!pwd)
		return (NULL);
	return (pwd);
}

char	*last_part(char **env)
{
	char	*pwd;
	char	*home;
	char	*without_home;
	char	*error;
	int		i;

	i = 0;
	error = ft_strdup("???");
	home = ft_getenv("HOME", env);
	pwd = ft_getenv("PWD", env);
	if (!pwd)
		pwd = getcwd(NULL, i++);
	if (!pwd)
		return (error);
	without_home = check_home(home, pwd);
	if (i)
		free(pwd);
	pwd = join_and_free(without_home, ">\001\033[0m\002 ");
	if (!pwd)
		return (error);
	if (error)
		free(error);
	return (pwd);
}

char	*get_prompt(char **env)
{
	char	*f_part;
	char	*l_part;
	char	*final;
	char	*error;

	error = ft_strdup("USER@minishell: \?\?\?> ");
	f_part = first_part();
	if (!f_part)
		return (error);
	l_part = last_part(env);
	if (!l_part)
	{
		free(f_part);
		return (error);
	}
	final = ft_strjoin(f_part, l_part);
	free(f_part);
	free(l_part);
	if (!final && error)
		return (error);
	if (error)
		free(error);
	return (final);
}
