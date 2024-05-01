/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:05:22 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/01 20:10:08 by xeo              ###   ########.fr       */
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

char	*find_to_move(int ac, char *av, char **env, int fd)
{
	char	*to_move;

	if (ac == 1)
		to_move = ft_strdup(ft_getenv("HOME", env));
	else if (!ft_strncmp(av, "-", 2) && ft_getenv("OLDPWD", env))
	{
		to_move = ft_strdup(ft_getenv("OLDPWD", env));
		ft_printf_fd(fd, "%s\n", to_move);
	}
	else
		to_move = av;
	return (to_move);
}

int	ft_cd(int ac, char **av, t_chris *cmd, t_minishell *minish)
{
	char	*to_move;
	int		cd_state;

	if (ac > 2)
	{
		error_handle(TOO_MANY_ARGS, minish, av[0], NULL);
		return (1);
	}
	to_move = find_to_move(ac, av[1], minish->env, cmd->fd_out);
	if (!to_move)
		return (1);
	replace_opwd(&minish->env);
	cd_state = chdir(to_move);
	if (ac == 1 || !ft_strncmp(av[1], "-", 2))
		free(to_move);
	if (cd_state == -1)
	{
		error_handle(NO_F_O_D_CD, minish, av, NULL);
		return (1);
	}
	replace_pwd(&minish->env);
	return (ft_abs(cd_state));
}
