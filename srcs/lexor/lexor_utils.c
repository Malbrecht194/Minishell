/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:32:36 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/20 18:47:45 by xeo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
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

int	add_to_array(char ***args, char *arg, int index)
{
	int		i;
	int		j;
	char	**add;
	char	**n_args;

	i = -1;
	j = 0;
	add = ft_split(arg, -1);
	if (!add)
		return (0);
	n_args = ft_calloc(ft_array_len((void **)add)
			+ ft_array_len((void **)(*args)), sizeof(char *));
	if (!n_args)
	{
		ft_free_2d_array((void **)add, ft_array_len((void **)add));
		return (0);
	}
	while (++i < index)
		n_args[i] = (*args)[i];
	while (add[j])
		n_args[i++] = add[j++];
	while (args[i++])
		n_args[i] = (*args)[i];
	free(*args);
	free(add);
	*args = n_args;
	return (j - 1);
}

void	remove_to_array(char ***args, int index)
{
	int	i;
	int	arr_len;

	i = index - 1;
	arr_len = ft_array_len((void **)(*args));
	free((*args)[index]);
	while (++i < arr_len)
		(*args)[i] = (*args)[i + 1];
}
