/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:44:39 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/27 15:29:49 by mhaouas          ###   ########.fr       */
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
	AMBIGOUS_REDIR,
	FAIL_OPEN,
	FAIL_HEREDOC,
	MALLOC_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
	NO_F_OR_DIR,
	DUP_ERROR,
	NO_CMD,
	NO_PERM,
	IS_DIR,
	NOT_VALID_ID,
	TOO_MANY_ARGS,
	CD_ERROR,
	NUM_ARG_REQUIRED,
	JUST_EXIT
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
# define MS_AMBIGOUS_REDIR "ambiguous redirect"
# define MS_PIPE_ERROR "failed to creat a pipe"
# define MS_FORK_ERROR "failed to use fork()"
# define MS_NO_CMD "command not found"
# define MS_DUP_ERROR "failed to use dup2()"
# define MS_NOT_VALID_ID "not a valid identifier"
# define MS_TOO_MANY_ARGS "too many arguments"
# define MS_NUM_ARG_REQUIRED "numeric argument required"
# define MS_FAIL_HEREDOC "here-document delimited by end-of-file "

void			error_handle(t_err_code error, void *minish, void *arg,
					void (*exit)(int));
void			print_error(t_err_struct s_error, void *minish);
void			check_exec_error(t_err_code error, void *minish);
t_err_struct	other_error(t_err_code error);
t_err_struct	builtins_error(t_err_code error, void *arg);

#endif