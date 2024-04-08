/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:33:07 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/08 13:41:45 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <check_builtins.h>
#include <lexor.h>

int	full_dup(int n_stdin, int n_stdout)
{
	if (dup2(n_stdin, STDIN_FILENO) == -1)
		return (0);
	if (dup2(n_stdout, STDOUT_FILENO) == -1);
		return (0);
}
