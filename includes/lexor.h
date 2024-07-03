/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:37:38 by malbrech          #+#    #+#             */
/*   Updated: 2024/07/03 18:08:52 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXOR_H
# define LEXOR_H

# include <fcntl.h>
# include <minishell.h>
/*================================ STRUCTURES ================================*/
enum	e_lexor
{
	ARG,
	PIPE,
	INFILE,
	HEREDOC,
	OUT_T,
	OUT_A,
};

/*================================ FONCTIONS ================================*/

t_exec	*exec_lexor(char *rl_args, t_minishell *minish);
int		check_rl_args(char *rl, t_minishell *minish);
t_init	*init_lexor(t_init **f_init, char *rl_args, t_minishell *minish);
int		check_ambigous(char *str, t_minishell *minish);
int		check_type(char *arg);
int		open_fd(char *f_name, int type, t_minishell *minish);
void	ft_initadd_back(t_init **lst, t_init *new);
t_init	*ft_initlast(t_init *lst);
void	ft_initclear(t_init **lst);
void	ft_execadd_back(t_exec **exec, t_exec *new);
t_exec	*ft_execlast(t_exec *exec);
void	ft_execclear(t_exec **exec);
t_exec	*ft_execnew(void);
void	close_all(int fd[2]);
void	remove_to_array(char ***args, int index);
t_init	*check_init_args(t_init *first, t_init *prev, t_init *node,
			t_minishell *minish);
t_init	*relink_node(t_init *first, t_init *last, t_minishell *minish);
t_exec	*creat_exec(t_exec **f_exec, t_init *lst, t_exec *node,
			t_minishell *minish);

/*================================ HEREDOC ================================*/

char	*rand_path(void);
int		heredoc(char *delimiter, t_minishell *minish);
int		need_expand(char **arg);
int		open_rand(char **filename);

#endif