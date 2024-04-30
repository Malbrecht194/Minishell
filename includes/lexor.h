/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:37:38 by malbrech          #+#    #+#             */
/*   Updated: 2024/04/30 13:12:31 by mhaouas          ###   ########.fr       */
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

t_chris	*chris_lexor(char *rl_args, t_minishell *minish);
int		check_rl_args(char *rl, t_minishell *minish);
t_init	*init_lexor(t_init **f_init, char *rl_args, t_minishell *minish);
int		check_ambigous(char *str, t_minishell *minish);
int	check_quote(char *arg, int index, t_minishell *minish);
int		check_type(char *arg);
int		open_fd(char *f_name, int type);
void	ft_initadd_back(t_init **lst, t_init *new);
t_init	*ft_initlast(t_init *lst);
void	ft_initclear(t_init **lst);

void	ft_chrisadd_back(t_chris **chris, t_chris *new);
t_chris	*ft_chrislast(t_chris *chris);
void	ft_chrisclear(t_chris **chris);
t_chris	*ft_chrisnew(void);
void	close_all(int fd[2]);
int	add_to_array(char ***args, char *arg, int index);
void	remove_to_array(char ***args, int index);
t_init	*check_init_args(t_init *first, t_init *prev, t_init *node, t_minishell *minish);

#endif