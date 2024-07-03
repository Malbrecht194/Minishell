/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:29:04 by malbrech          #+#    #+#             */
/*   Updated: 2024/05/02 18:26:13 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexor.h>
#include <minishell.h>

t_exec	*ft_execnew(void)
{
	t_exec	*new;

	new = (t_exec *)ft_calloc(sizeof(t_exec), 1);
	if (!new)
		return (NULL);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	return (new);
}

void	ft_execclear(t_exec **exec)
{
	t_exec	*tmp;

	if (!exec || !(*exec))
		return ;
	while ((*exec))
	{
		tmp = (*exec)->next;
		if ((*exec)->cmd)
			ft_free_2d_array((*exec)->cmd,
				ft_array_len((*exec)->cmd));
		try_close((*exec)->fd_in);
		try_close((*exec)->fd_out);
		free(*exec);
		*exec = tmp;
	}
	*exec = NULL;
}

t_exec	*ft_execlast(t_exec *exec)
{
	if (!exec->next)
		return (exec);
	else
		return (ft_execlast(exec->next));
}

void	ft_execadd_back(t_exec **exec, t_exec *new)
{
	t_exec	*tmp;

	if (!exec || !new)
		return ;
	else if (!(*exec))
		*exec = new;
	else
	{
		tmp = ft_execlast(*exec);
		tmp->next = new;
	}
}
