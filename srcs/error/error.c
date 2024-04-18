/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:58:31 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/18 17:24:08 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_error.h>

t_err_struct	exec_error(t_err_code error, void *arg)
{
	t_err_struct	s_error;

	if (error == NO_F_OR_DIR)
		s_error.err_msg = strerror(errno);
	else if (error == DUP_ERROR)
		s_error.err_msg = MS_DUP_ERROR;
	else if (error == NO_CMD)
		s_error.err_msg = MS_NO_CMD;
	else if (error == NO_PERM)
		s_error.err_msg = strerror(errno);
	else if (error == IS_DIR)
		s_error.err_msg = MS_IS_DIR;
	if (error == NO_F_OR_DIR || error == NO_CMD)
		s_error.exit_code = 127;
	else if (error == NO_PERM || error == IS_DIR)
		s_error.exit_code = 126;
	else
		s_error.exit_code = 1;
	s_error.cmd_name = (char *)arg;
	return (s_error);
}

t_err_struct	open_error(t_err_code error, void *arg)
{
	t_err_struct	s_error;

	if (error == AMBIGOUS_REDIR)
		s_error.err_msg = MS_AMBIGOUS_REDIR;
	else if (error == FAIL_OPEN)
		s_error.err_msg = strerror(errno);
	s_error.cmd_name = (char *)arg;
	s_error.exit_code = 1;
	return (s_error);
}

t_err_struct	line_error(t_err_code error, void *arg)
{
	t_err_struct	s_error;

	if (error == NO_END_QUOTE)
		s_error.err_msg = MS_NO_END_QUOTE;
	else if (error == SYNTAX_ERROR)
	{
		s_error.err_msg = MS_SYNTAX_ERROR;
		s_error.args = (char *)arg;
	}
	s_error.cmd_name = NULL;
	s_error.exit_code = 1;
	return (s_error);
}

t_err_struct	ms_init_err(t_err_code error)
{
	t_err_struct	s_error;

	if (error == TOO_MUCH_ARG)
		s_error.err_msg = MS_TOO_MUCH_ARG;
	else if (error == FAIL_STRUCT)
		s_error.err_msg = MS_FAIL_STRUCT;
	s_error.exit_code = 1;
	s_error.cmd_name = NULL;
	return (s_error);
}

void	error_handle(t_err_code error, void *minish, void *arg,
		void (*exit)(int))
{
	t_err_struct	s_error;

	s_error.exit_code = 1;
	if (error == TOO_MUCH_ARG || error == FAIL_STRUCT)
		s_error = ms_init_err(error);
	else if (error == NO_END_QUOTE || error == SYNTAX_ERROR)
		s_error = line_error(error, arg);
	else if (error == MALLOC_ERROR)
		s_error.err_msg = MS_MALLOC_ERROR;
	else if (error == AMBIGOUS_REDIR || error == FAIL_OPEN)
		s_error = open_error(error, arg);
	else if (error == PIPE_ERROR)
		s_error.err_msg = MS_PIPE_ERROR;
	else if (error == FORK_ERROR)
		s_error.err_msg = MS_FORK_ERROR;
	else if (NO_F_OR_DIR <= error && error <= IS_DIR)
		s_error = exec_error(error, arg);
	s_error.code = error;
	print_error(s_error, minish);
	check_exec_error(error, minish);
	if (exit)
		exit(s_error.exit_code);
}
