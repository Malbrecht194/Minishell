/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:02:49 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/16 14:09:13 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <expand.h>

int	skip_ifs(char *str)
{
	int	i;

	i = 0;
	while (str[i] == -1)
		i++;
	return (i);
}

char	**dup_array(char **array)
{
	char	**n_array;
	int		len;
	int		i;

	if (!array || !*array)
		return (NULL);
	i = 0;
	len = ft_array_len((void **)array);
	n_array = ft_calloc(sizeof(char *), len + 1);
	if (!n_array)
		return (NULL);
	while (i < len)
	{
		n_array[i] = ft_strdup(array[i]);
		if (!n_array[i])
		{
			ft_free_2d_array((void **)n_array);
			return (NULL);
		}
		i++;
	}
	return (n_array);
}

int	try_close(int fd)
{
	if (fd > 2)
		return (close(fd));
	return (-1);
}

void	free_minish(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->cmd_line)
		ft_chrisclear(&minishell->cmd_line);
	if (minishell->env)
		ft_free_2d_array((void **)minishell->env);
	if (minishell->prompt)
		free(minishell->prompt);
	free(minishell);
	clear_history();
}

void	close_all_fd()
{
	int	i;
	
	i = 2;
	while (++i < 1024)
		try_close(i);
}