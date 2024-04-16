/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/15 21:22:25 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

void	arg_format(t_init *lst, t_chris **node)
{
	int			i;
	char		**array;
	size_t		a_size;

	i = 0;
	a_size = ft_array_len((void **)(*node)->cmd);
	array = ft_calloc(sizeof(char *), a_size + 2);
	if (!array)
		return ; //error
	while ((*node)->cmd && (*node)->cmd[i])
	{
		array[i] = (*node)->cmd[i];
		i++;
	}
	array[i] = ft_strdup(lst->str);
	if (!array[i])
		return ; //error
	if ((*node)->cmd)
		free((*node)->cmd);
	(*node)->cmd = array;
}

void	select_in_out(t_init *lst, t_chris **node)
{
	int	*fd;	

	fd = NULL;
	if ((*node)->error)
		return ;
	if (lst->type == OUT_A || lst->type == OUT_T)
		fd = &(*node)->fd_out;
	else if (lst->type == INFILE)
		fd = &(*node)->fd_in;
	if ((*fd))
		try_close((*fd));
	(*fd) = open_fd(lst->str, lst->type);
	if ((*fd) == -1)
	{	
		(*node)->error = 1; //error
		//failed to open file
	}
}

t_chris	*creat_chris(t_init *lst, t_chris **node)
{
	t_chris	*n_node;
	
	n_node = NULL;
	if (!lst)
		return (NULL);
	if (!node && !lst->error)
	{
		n_node = ft_chrisnew();
		if (!n_node)
			return (NULL);
		return (creat_chris(lst, &n_node));
	}
	else if (lst->type == ARG)
		arg_format(lst, node);
	else if (lst->type == OUT_A || lst->type == OUT_T || lst->type == INFILE)
		select_in_out(lst, node);
	if (lst->type == PIPE)
		(*node)->next = creat_chris(lst->next, NULL);
	else
		creat_chris(lst->next, node);
	return (*node);
}

void	last_cmd_check(t_chris *chris)
{
	int		i;
	t_chris	*tmp;
	
	tmp = chris;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			delete_quote(&tmp->cmd[i]);
			if (ft_count_word(tmp->cmd[i], -1) > 1)
				add_to_array(&tmp->cmd, tmp->cmd[i], &i);
			i++;
		}
		tmp = tmp->next;
	}
}

t_chris	*chris_lexor(char *rl_args, char **env)
{
	t_chris	*c_lst;
	t_init	*lst;

	if (!check_rl_args(rl_args))
		return (NULL); //error
	lst = init_lexor(rl_args, env);
	c_lst = creat_chris(lst, NULL);
	ft_initclear(&lst);
	free(rl_args);
	last_cmd_check(c_lst);
	return (c_lst);
}
