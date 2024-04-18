/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:05:22 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 17:20:06 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

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
	char	*tmp;
	char	*pwd;
	int		s_pwd;

	s_pwd = 0;
	if (!ft_getenv("OLDPWD", *env))
		return ;
	if (ft_getenv("PWD", *env))
		pwd = ft_getenv("PWD", *env);
	else
		pwd = getcwd(NULL, s_pwd++);
	tmp = ft_strjoin("OLDPWD=", pwd);
	if (!tmp)
		return ;
	if (pwd && s_pwd)
		free(pwd);
	replace_env(tmp, &(*env)[check_env(*env, "OLDPWD")]);
	free(tmp);
}

int	ft_cd(int ac, char **av, t_chris *cmd, t_minishell *minish)
{
	char	*to_move;
	int		cd_state;
	int		state;

	(void) cmd;
	state = 0;
	if (ac == 1 || !ft_strncmp(av[1], "-", 2))
		state++;
	if (ac == 1)
		to_move = ft_strdup(ft_getenv("HOME", minish->env));
	else if (!ft_strncmp(av[1], "-", 2))
		to_move = ft_strdup(ft_getenv("OLDPWD", minish->env));
	else
		to_move = av[1];
	if (!to_move)
		return (1);
	replace_opwd(&minish->env);
	cd_state = chdir(to_move);
	replace_pwd(&minish->env);
	if (state)
		free(to_move);
	return (ft_abs(cd_state));
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**dup_env;

// 	dup_env = dup_array(envp);
// 	printf("CPWD : %s, OPWD : %s\n", ft_getenv("PWD", dup_env),
		// ft_getenv("OLDPWD", dup_env));
// 	ft_cd(ac, av, &dup_env);
// 	printf("NEW CPWD : %s, NEW OPWD : %s\n", ft_getenv("PWD", dup_env),
		// ft_getenv("OLDPWD", dup_env));
// 	ft_free_2d_array((void **)dup_env);
// }
