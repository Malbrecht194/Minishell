/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:44:39 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/19 16:18:48 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <libft.h>
# include <lexor.h>
# include <minishell.h>

int		env_size(char *env);
int		check_env(char **env, char *av);
int		replace_env(char *n_env, char **o_env);
void	swap_string(char **a, char **b);
char	**sort_env(char **env);
void	change_env(int to_del, char ***env);
int		declare_x(char ***envp, int i);
int		check_export_type(char *arg);
int		no_env(char *n_env, char ***o_env);
void	print_array(int fd_out, char **array);

/*============================= BUILTINS PROTOTYPE ===========================*/
int		ft_echo(int ac, char **av, t_chris *cmd, t_minishell *minish);
int		ft_env(int ac, char **av, t_chris *cmd, t_minishell *minish);
int		ft_exit(int ac, char **av, t_chris *cmd, t_minishell *minish);
int		ft_pwd(int ac, char **av, t_chris *cmd, t_minishell *minish);
int		ft_cd(int ac, char **av, t_chris *cmd, t_minishell *minish);
int		ft_export(int ac, char **av, t_chris *cmd, t_minishell *minish);
int		ft_unset(int ac, char **av, t_chris *cmd, t_minishell *minish);

#endif