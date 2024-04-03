/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:05:22 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/29 14:20:58 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/builtins.h"
#include "../INCLUDES/minishell.h"

void	replace_pwd(char ***env)
{
	int		i_env;
	char	*tmp;
	char	*pwd;
	
	if (!ft_getenv("PWD", *env))
		return ;
	i_env = check_env(*env, "PWD");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	tmp = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!tmp)
		return ;
	replace_env(tmp, &(*env)[i_env]);
	free(tmp);
}

void	replace_opwd(char ***env)
{
	int		i_env;
	char	*tmp;
	int		cwd;
	char	*pwd;

	i_env = 0;
	cwd = 0;
	if (!ft_getenv("OLDPWD", *env))
		return ;
	pwd = ft_getenv("PWD", *env);
	if (!pwd)
	{
		pwd = getcwd(NULL, cwd++);
		if (!pwd)
			return ;
	}
	i_env = check_env(*env, "OLDPWD");
	tmp = ft_strjoin("OLDPWD=", pwd);
	if (!tmp)
		return;
	if (cwd == 1)
		free(pwd);
	replace_env(tmp, &(*env)[i_env]);
	free(tmp);
}

int	ft_cd(int ac, char **av, char ***env)
{
	char	*to_move;
	int		cd_state;
	
	replace_opwd(env);
	if (ac == 1)
	{
		to_move = ft_getenv("HOME", *env);
		if (!to_move)
			return (1);
	}
	else
		to_move = av[1];
	cd_state = chdir(to_move);
	replace_pwd(env);
	return (cd_state);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**dup_env;
	
// 	dup_env = dup_array(envp);
// 	printf("CPWD : %s, OPWD : %s\n", ft_getenv("PWD", dup_env), ft_getenv("OLDPWD", dup_env));
// 	ft_cd(ac, av, &dup_env);
// 	printf("NEW CPWD : %s, NEW OPWD : %s\n", ft_getenv("PWD", dup_env), ft_getenv("OLDPWD", dup_env));
// 	ft_free_2d_array((void **)dup_env);
// }
