/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:45:34 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 14:19:09 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*================================== INCLUDES ================================*/

# include <errno.h>
# include <lexor.h>
# include <libft.h>
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

typedef struct s_minishell
{
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
void				free_minish(t_minishell *minishell);
char				*ft_getenv(char *to_get, char **env);

#endif