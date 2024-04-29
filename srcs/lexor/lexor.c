/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/23 12:03:57 by xeo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

int	arg_format(t_chris **f_chris, t_init *lst, t_chris *node)
{
	int			i;
	char		**array;

	i = 0;
	array = ft_calloc(sizeof(char *), ft_array_len((void **)node->cmd) + 2);
	if (!array)
	{
		ft_chrisclear(f_chris);
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
		ft_chrisclear(f_chris);
		return (0);
	}
	if (node->cmd)
		free(node->cmd);
	node->cmd = array;
	return (1);
}

void	select_in_out(t_init *lst, t_chris *node, t_minishell *minish)
{
	int	*fd;	

	fd = NULL;
	if (!check_ambigous(lst->str, minish))
		node->error = 1;
	if (node->error)
		return ;
	if (lst->type == OUT_A || lst->type == OUT_T)
		fd = &node->fd_out;
	else if (lst->type == INFILE)
		fd = &node->fd_in;
	if ((*fd))
		try_close((*fd));
	(*fd) = open_fd(lst->str, lst->type);
	if ((*fd) == -1)
	{	
		node->error = 1;
		error_handle(FAIL_OPEN, minish, lst->str, NULL);
	}
}

t_chris	*creat_chris(t_chris **f_chris, t_init *lst, t_chris *node, t_minishell *minish)
{
	t_chris	*n_node;
	
	n_node = NULL;
	if (!lst)
		return (NULL);
	if (!node && !lst->error)
	{
		n_node = ft_chrisnew();
		if (!n_node)
		{
			ft_chrisclear(f_chris);
			return (NULL);
		}
		if (!f_chris)
			creat_chris(&n_node, lst, n_node, minish);
		else
			creat_chris(f_chris, lst, n_node, minish);
		return (n_node);
	}
	else if (lst->type == ARG)
	{
		if (!arg_format(f_chris, lst, node))
			return (NULL);
	}
	else if (lst->type == OUT_A || lst->type == OUT_T || lst->type == INFILE)
		select_in_out(lst, node, minish);
	if (lst->type == PIPE)
		ft_chrisadd_back(&node, creat_chris(f_chris, lst->next, NULL, minish));
	else
		creat_chris(f_chris, lst->next, node, minish);
	return (node);
}

void	last_cmd_check(t_chris *chris)
{
	int		i;
	int		j;
	char	*new_arr;
	t_chris	*tmp;

	if (!chris)
		return ;
	tmp = chris;
	new_arr = NULL;
	while (tmp)
	{
		i = 0;
		j = 0;
		if (!*tmp->cmd[0])
			remove_to_array(&tmp->cmd, 0);
		while (tmp->cmd[i])
		{
			if (ft_count_word(tmp->cmd[i], -1) > 1)
			{
				new_arr = ft_strdup(tmp->cmd[i]);
				if (!new_arr)
				{
					ft_chrisclear(&chris);
					return ;
				}
				free(tmp->cmd[i]);
				j = add_to_array(&tmp->cmd, new_arr, i);
				if (j == 0)
				{
					ft_chrisclear(&chris);
					return ;
				}
				i += j;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

t_chris	*chris_lexor(char *rl_args, t_minishell *minish)
{
	t_chris	*c_lst;
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
	c_lst = creat_chris(NULL, lst, NULL, minish);
	ft_initclear(&lst);
	last_cmd_check(c_lst);
	if (!c_lst)
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
	return (c_lst);
}
