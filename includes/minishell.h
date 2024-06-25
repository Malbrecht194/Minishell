/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:45:34 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/19 13:07:45 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*================================== INCLUDES ================================*/

# include <errno.h>
# include <libft.h>
# include <limits.h>
# include <ms_error.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*================================ PIPE FD TYPE ==============================*/
# define READ_FD 0
# define WRITE_FD 1

/*=================================== STRUCT =================================*/

extern int		g_sig;

typedef struct s_minishell
{
	struct s_chris	*cmd_line;
	char			**heredocs;
	char			*location;
	char			*prompt;
	char			**env;
	int				last_error;
}					t_minishell;

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

typedef struct s_exp
{
	size_t	i;
	size_t	j;
	size_t	exp_size;
}					t_exp;

char				**mini_split(char const *s, char sep);
char				*test_access(char *command, t_minishell *minish);
char				*get_prompt(t_minishell *minish);
void				init_args(t_minishell *minish, char *rl_args);
char				**dup_array(char **array);
void				free_minish(t_minishell *minishell);
char				*ft_getenv(char *to_get, char **env);

#endif