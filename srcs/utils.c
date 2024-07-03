/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:02:49 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:49 by mhaouas          ###   ########.fr       */
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
	len = ft_array_len(array);
	n_array = ft_calloc(sizeof(char *), len + 1);
	if (!n_array)
		return (NULL);
	while (i < len)
	{
		n_array[i] = ft_strdup(array[i]);
		if (!n_array[i])
		{
			ft_free_2d_array(n_array, len + 1);
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

void	unlink_free_heredocs(t_minishell *minishell)
{
	char	*name;
	int		i;

	i = 0;
	while (minishell->heredocs[i] != 0)
	{
		name = minishell->heredocs[i];
		if (name)
			unlink(name);
		i++;
	}
	ft_free_2d_array((void **)(minishell->heredocs), i);
}

void	free_minish(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->cmd_line)
		ft_execclear(&minishell->cmd_line);
	if (minishell->heredocs)
		unlink_free_heredocs(minishell);
	if (minishell->env)
		ft_free_2d_array(minishell->env, ft_array_len(minishell->env));
	try_free(minishell->prompt);
	try_free(minishell);
	rl_clear_history();
}
