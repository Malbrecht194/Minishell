/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:37:38 by malbrech          #+#    #+#             */
/*   Updated: 2024/04/11 17:46:18 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXOR_H
# define LEXOR_H

# include <minishell.h>

/*================================ STRUCTURES ================================*/
enum				e_lexor
{
	ARG,
	PIPE,
	INFILE,
	HEREDOC,
	OUT_T,
	OUT_A,
};

typedef struct s_chris
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	int				error;
	struct s_chris	*next;
}					t_chris;

typedef struct s_f_lex
{
	int				type;
	char			*str;
	int				error;
	struct s_f_lex	*next;
}					t_init;

/*================================ FONCTIONS ================================*/

t_chris				*chris_lexor(char *rl_args, char **env);
int					check_rl_args(char *rl);
t_init				*init_lexor(char *rl_args, char **env);

int					check_type(char *arg);
int					open_fd(char *f_name, int type);
void				ft_initadd_back(t_init **lst, t_init *new);
t_init				*ft_initlast(t_init *lst);
void				ft_initclear(t_init **lst);

void				ft_chrisadd_back(t_chris **chris, t_chris *new);
t_chris				*ft_chrislast(t_chris *chris);
void				ft_chrisclear(t_chris **chris);
t_chris				*ft_chrisnew(void);
void				close_all(int fd[2]);

#endif