/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:44:39 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/18 16:35:06 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include <libft.h>

/*
==== ERROR_CODE
*/

typedef enum e_errcode
{
	TOO_MUCH_ARG,
	FAIL_STRUCT,
	NO_END_QUOTE,
	SYNTAX_ERROR,
	MALLOC_ERROR,
	AMBIGOUS_REDIR,
	FAIL_OPEN,
	PIPE_ERROR,
	FORK_ERROR,
	NO_F_OR_DIR,
	DUP_ERROR,
	NO_CMD,
	NO_PERM,
	IS_DIR
}				t_err_code;

/*
==== ERROR_STRUCT
*/

typedef struct s_err_struct
{
	char		*err_msg;
	char		*cmd_name;
	char		*args;
	int			exit_code;
	t_err_code	code;
}				t_err_struct;

/*
==== ERROR_MSG
*/

# define MS_TOO_MUCH_ARG "too much arguments when executing minishell"
# define MS_FAIL_STRUCT "failed to creat malloc minishell's struct"
# define MS_NO_END_QUOTE "there's a quote unclosed"
# define MS_SYNTAX_ERROR "syntax error near unexpected token"
# define MS_MALLOC_ERROR "failed to use malloc()"
# define MS_AMBIGOUS_REDIR "ambigous redirect"
# define MS_PIPE_ERROR "failed to creat a pipe"
# define MS_FORK_ERROR "failed to use fork()"
# define MS_NO_CMD "command not found"
# define MS_IS_DIR "is a directory"
# define MS_DUP_ERROR "failed to use dup2()"

void			error_handle(t_err_code error, void *minish, void *arg,
					void (*exit)(int));
void			print_error(t_err_struct s_error, void *minish);
void			check_exec_error(t_err_code error, void *minish);

#endif