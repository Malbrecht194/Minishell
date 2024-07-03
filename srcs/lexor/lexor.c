/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

int	arg_format(t_exec **f_exec, t_init *lst, t_exec *node)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_calloc(sizeof(char *), ft_array_len(node->cmd) + 2);
	if (!array)
	{
		ft_execclear(f_exec);
		return (0);
	}
	while (node->cmd && node->cmd[i])
	{
		array[i] = node->cmd[i];
		i++;
	}
	array[i] = ft_strdup(lst->str);
	if (!array[i])
	{
		ft_execclear(f_exec);
		return (0);
	}
	try_free(node->cmd);
	node->cmd = array;
	return (1);
}

int	select_in_out(t_exec **f_exec, t_init *lst, t_exec *node,
		t_minishell *minish)
{
	int	*fd;

	fd = NULL;
	if (!check_ambigous(lst->str, minish))
		node->error = 1;
	if (node->error)
		return (-1);
	if (lst->type == OUT_A || lst->type == OUT_T)
		fd = &node->fd_out;
	else if (lst->type == INFILE || lst->type == HEREDOC)
		fd = &node->fd_in;
	if ((*fd) > 2)
		try_close(*fd);
	(*fd) = open_fd(lst->str, lst->type, minish);
	if ((*fd) == -1)
	{
		node->error = 1;
		error_handle(FAIL_OPEN, minish, lst->str, NULL);
	}
	else if ((*fd) == -2)
	{
		ft_execclear(f_exec);
		return (-2);
	}
	return (1);
}

t_exec	*creat_exec_node(t_exec **f_exec, t_init *lst, t_minishell *minish)
{
	t_exec	*n_node;

	n_node = ft_execnew();
	if (!n_node)
	{
		ft_execclear(f_exec);
		return (NULL);
	}
	if (!f_exec)
		creat_exec(&n_node, lst, n_node, minish);
	else
		creat_exec(f_exec, lst, n_node, minish);
	return (n_node);
}

t_exec	*creat_exec(t_exec **f_exec, t_init *lst, t_exec *node,
		t_minishell *minish)
{
	if (!lst)
		return (NULL);
	if (!node && !lst->error)
		return (creat_exec_node(f_exec, lst, minish));
	else if (lst->type == ARG)
	{
		if (!arg_format(f_exec, lst, node))
		{
			error_handle(MALLOC_ERROR, minish, NULL, NULL);
			return (NULL);
		}
	}
	else if (lst->type == OUT_A || lst->type == OUT_T || lst->type == INFILE
		|| lst->type == HEREDOC)
	{
		if (select_in_out(f_exec, lst, node, minish) == -2)
			return (NULL);
	}
	if (lst->type == PIPE)
		ft_execadd_back(&node, creat_exec(f_exec, lst->next, NULL, minish));
	else
		creat_exec(f_exec, lst->next, node, minish);
	if (!f_exec && node)
		ft_execclear(&node);
	return (node);
}

t_exec	*exec_lexor(char *rl_args, t_minishell *minish)
{
	t_exec	*c_lst;
	t_init	*lst;

	if (!check_rl_args(rl_args, minish))
		return (NULL);
	lst = init_lexor(NULL, rl_args, minish);
	free(rl_args);
	if (!lst)
	{
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	lst = check_init_args(NULL, NULL, lst, minish);
	if (!lst)
		return (NULL);
	c_lst = creat_exec(NULL, lst, NULL, minish);
	ft_initclear(&lst);
	if (!c_lst)
		return (NULL);
	return (c_lst);
}
