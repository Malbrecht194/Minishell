/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:44:39 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/29 14:27:47 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../Libft/libft.h"

int		env_size(char *env);
int		check_env(char **env, char *av);
int		replace_env(char *n_env, char **o_env);

/*============================= BUILTINS PROTOTYPE ===========================*/
char	*ft_getenv(char *to_get, char **env);
int		ft_echo(int ac, char **av, char ***env);
int		ft_env(int ac, char **av, char ***envp);
int		ft_exit(int ac, char **av, char ***env);
int		ft_pwd(int ac, char **av, char ***env);
int		ft_cd(int ac, char **av, char ***env);
int		ft_export(int ac, char **av, char ***env);
int		ft_unset(int ac, char **av, char ***env);

#endif