/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 07:51:27 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/27 15:30:58 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_error.h>

t_err_struct	other_error(t_err_code error)
{
	t_err_struct	s_error;

	if (error == MALLOC_ERROR)
		s_error.err_msg = MS_MALLOC_ERROR;
	else if (error == PIPE_ERROR)
		s_error.err_msg = MS_PIPE_ERROR;
	else if (error == FORK_ERROR)
		s_error.err_msg = MS_FORK_ERROR;
	s_error.exit_code = 1;
	s_error.cmd_name = NULL;
	return (s_error);
}

t_err_struct	builtins_error(t_err_code error, void *arg)
{
	t_err_struct	s_error;
	char			**args;

	args = (char **)arg;
	if (error == NOT_VALID_ID)
		s_error.err_msg = MS_NOT_VALID_ID;
	else if (error == TOO_MANY_ARGS)
		s_error.err_msg = MS_TOO_MANY_ARGS;
	else if (error == CD_ERROR)
		s_error.err_msg = strerror(errno);
	else if (error == NUM_ARG_REQUIRED)
		s_error.err_msg = MS_NUM_ARG_REQUIRED;
	if (error == NOT_VALID_ID || error == CD_ERROR)
	{
		s_error.cmd_name = args[0];
		s_error.args = args[1];
	}
	else
		s_error.cmd_name = (char *)arg;
	if (error == NUM_ARG_REQUIRED)
		s_error.exit_code = 2;
	else
		s_error.exit_code = 1;
	return (s_error);
}
