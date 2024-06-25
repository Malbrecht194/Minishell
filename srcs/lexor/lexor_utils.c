/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:32:36 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/25 17:38:40 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

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
		return (-1);
}

int	open_fd(char *f_name, int type, t_minishell *minish)
{
	int		fd;

	fd = 0;
	if (type == OUT_A)
		fd = open(f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == OUT_T)
		fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == INFILE)
		fd = open(f_name, O_RDONLY);
	else if (type == HEREDOC)
		fd = heredoc(f_name, minish);
	return (fd);
}

void	remove_to_array(char ***args, int index)
{
	int	i;
	int	arr_len;

	i = index - 1;
	arr_len = ft_array_len((*args));
	free((*args)[index]);
	while (++i < arr_len)
		(*args)[i] = (*args)[i + 1];
}

int	need_expand(char **arg)
{
	int	i;
	int	exp;

	i = 0;
	exp = 1;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'' || (*arg)[i] == '\"')
		{
			exp = 0;
			rm_char(arg, i);
		}
		else
			i++;
	}
	return (exp);
}

int	open_rand(char	**filename)
{
	int		fd;
	char	*path;

	path = rand_path();
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(path);
		fd = open_rand(filename);
	}
	else
		*filename = path;
	return (fd);
}
