/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:45:34 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/28 15:37:21 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*================================== INCLUDES ================================*/

# include "../Libft/libft.h"
# include "builtins.h"
# include "expand.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>
# include <term.h>
# include "lexor.h"

/*================================ PIPE FD TYPE ==============================*/
# define READ_FD 0
# define WRITE_FD 1

/*=================================== STRUCT =================================*/
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
	struct s_chris	*cmd_line;
	char			*prompt;
	char			**env;
}					t_minishell;

char				*get_prompt(char **env);
t_pipex				*create_link_list(char **commands, char **env);
void				ft_pipe_lstclear(t_pipex **lst);
void				ft_pipe_lstadd_back(t_pipex **lst, t_pipex *new);
t_pipex				*ft_pipe_lstlast(t_pipex *lst);
char				*test_access(char *command, char **env);
char				**get_flags(char *command, char *access);
void				check_args(t_minishell *minish, char *rl_args);
char				**dup_array(char **array);

#endif