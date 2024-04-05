/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:32:36 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/04 19:17:26 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/check_builtins.h"
#include "../INCLUDES/expand.h"
#include "../INCLUDES/lexor.h"
#include "../INCLUDES/minishell.h"

int	check_type(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '|')
		return (PIPE);
	else if (arg[i] == '<' && arg[i + 1] == '<')
		return (HEREDOC);
	else if (arg[i] == '<')
		return (INFILE);
	else if (arg[i] == '>' && arg[i + 1] == '>')
		return (OUT_A);
	else if (arg[i] == '>')
		return (OUT_T);
	else if (!is_ifs(arg[i]))
		return (ARG);
	else
		return (0);
}

int	open_fd(char *f_name, int type)
{
	int	fd;

	fd = 0;
	if (type == OUT_A)
		fd = open(f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == OUT_T)
		fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == INFILE)
		fd = open(f_name, O_RDONLY);
	return (fd);
}
