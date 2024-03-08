/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:20:52 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/08 14:11:29 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*================================== INCLUDES ================================*/

# include "../Libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>
# include <term.h>

/*================================ PIPE FD TYPE ==============================*/
# define READ_FD 0
# define WRITE_FD 1

/*=================================== STRUCT =================================*/

# define IFS " \t\n"

typedef struct s_prompt
{
	char			*login;
	char			*location;
	char			*pwd;
	char			*cwd;
	char			*tmp_prompt;
	char			*tmp_prompt2;
	char			*final_prompt;
}					t_prompt;

typedef struct s_exec
{
	char			*command;
	char			**flags;
	char			**envp;
	int				in;
	int				out;
}					t_exec;

typedef struct s_pipex
{
	struct s_exec	cmd;
	int				cmd_number;
	int				total_number_of_cmd;
	pid_t			pid;
	int				redir;
	struct s_pipex	*next;
}					t_pipex;

typedef struct s_minishell
{
	struct s_pipex	*cmd;
	char			*prompt;
	char			**env;
}					t_minishell;

char				*get_prompt(void);
int					array_len(void **array);
t_pipex				*create_link_list(char **commands);
void				ft_pipe_lstclear(t_pipex **lst);
void				ft_pipe_lstadd_back(t_pipex **lst, t_pipex *new);
t_pipex				*ft_pipe_lstlast(t_pipex *lst);
char				*test_access(char *command);
char				**get_flags(char *command, char *access);
void				check_args(t_minishell *minish, char *rl_args);
char	**dup_array(char **array);
char	*skip_quoting(char *arg);
void	check_quoting(t_pipex **l_list);

#endif