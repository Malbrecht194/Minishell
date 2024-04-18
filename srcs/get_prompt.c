/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:42:06 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/17 16:53:35 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*first_part(t_minishell *minish)
{
	char	*login;
	char	*tmp;

	login = "USER";
	minish->location = "minishell";
	if (getenv("USER"))
		login = getenv("USER");
	if (ft_getenv("MINISHELL", minish->env))
		minish->location = ft_getenv("MINISHELL", minish->env);
	tmp = ft_strjoin("\001\033[37m\002", login);
	tmp = join_and_free(tmp, "\001\033[31m\002@", 1, 0);
	tmp = join_and_free(tmp, "\001\033[32m\002", 1, 0);
	tmp = join_and_free(tmp, minish->location, 1, 0);
	tmp = join_and_free(tmp, ":", 1, 0);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*check_home(char *home, char *cwd)
{
	size_t		i;
	char		*pwd;
	char		*tmp;

	i = 0;
	while (home && home[i] && cwd[i] && home[i] == cwd[i])
		i++;
	if (home && i == ft_strlen(home) && (cwd[i] == '/' || !cwd[i]))
	{
		tmp = ft_substr(cwd, i, ft_strlen(cwd) - ft_strlen(home));
		if (!tmp)
			return (NULL);
		pwd = join_and_free("\001\033[36m\002~", tmp, 0, 1);
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
	int		i;

	i = 0;
	home = ft_getenv("HOME", env);
	pwd = ft_getenv("PWD", env);
	if (!pwd)
		pwd = getcwd(NULL, i++);
	if (!pwd)
		return (NULL);
	without_home = check_home(home, pwd);
	if (i)
		free(pwd);
	pwd = join_and_free(without_home, ">\001\033[0m\002 ", 1, 0);
	if (!pwd)
		return (NULL);
	return (pwd);
}

char	*get_prompt(t_minishell *minish)
{
	char	*f_part;
	char	*l_part;
	char	*final;

	f_part = first_part(minish);
	if (!f_part)
		return (NULL);
	l_part = last_part(minish->env);
	if (!l_part)
	{
		free(f_part);
		return (NULL);
	}
	final = join_and_free(f_part, l_part, 1, 1);
	if (!final)
		return (NULL);
	return (final);
}
