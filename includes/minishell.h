/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:45:34 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/15 09:44:25 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*================================== INCLUDES ================================*/

# include <builtins.h>
# include <errno.h>
# include <lexor.h>
# include <libft.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signals.h>
# include <sys/wait.h>
# include <term.h>
# include <stdio.h>

/*================================ PIPE FD TYPE ==============================*/
# define READ_FD 0
# define WRITE_FD 1

/*=================================== STRUCT =================================*/

typedef struct s_minishell
{
	struct s_pipex	*cmd;
	struct s_chris	*cmd_line;
	char			*prompt;
	char			**env;
	int				last_error;
}					t_minishell;

char				*test_access(char *command, char **env);

char				*get_prompt(char **env);
void				check_args(t_minishell *minish, char *rl_args);
char				**dup_array(char **array);
int					try_close(int fd);

#endif