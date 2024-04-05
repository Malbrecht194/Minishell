/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/05 15:54:58 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <expand.h>
#include <lexor.h>
#include <minishell.h>

int	check_rl_args(char *rl)
{
	size_t		i;
	int			j;
	int			state;

	i = 0;
	i += skip_ifs(rl);
	if (i >= ft_strlen(rl))
		return (1);
	if (rl[i] == '|')
		return (0);
	while (rl[i])
	{
		state = 0;
		if (check_type(&rl[i]) == INFILE || check_type(&rl[i]) == OUT_T
			|| check_type(&rl[i]) == PIPE)
			state = 1;
		else if (check_type(&rl[i]) == HEREDOC || check_type(&rl[i]) == OUT_A)
			state = 2;
		j = i + skip_ifs(&rl[i + state]);
		if (state && (rl[j] == '<' || rl[j] == '>' || rl[j] == '|'))
			return (0);
		if (skip_ifs(rl + ++i))
			i += skip_ifs(rl + i);
	}
	return (1);
}

t_f_lexor	*w_lexor_sort(char *rl_args)
{
	int			i;
	int			j;
	t_f_lexor	*f_lexor;

	i = 0;
	j = 1;
	if (!rl_args || !*rl_args)
		return (NULL);
	f_lexor = ft_calloc(sizeof(t_f_lexor), 1);
	i += skip_ifs(rl_args);
	f_lexor->type = check_type(rl_args + i);
	if (!(f_lexor->type == PIPE || f_lexor->type == 0))
	{
		if (f_lexor->type == HEREDOC || f_lexor->type == OUT_A)
			j++;
		i += skip_ifs(rl_args + i + j);
		while (rl_args[i + j] && !is_ifs(rl_args[i + j]))
			j++;
		f_lexor->str = sub_and_trim(rl_args, i, j, "<>");
		if (!f_lexor->str)
			return (NULL);
	}
	lexor_lstadd_back(&f_lexor, w_lexor_sort(rl_args + i + j));
	return (f_lexor);
}

int	arg_format(t_f_lexor *lst, t_chris **node)
{
	int			i;
	char		**array;
	size_t		a_size;

	i = 0;
	a_size = ft_array_len((void **)(*node)->cmd);
	array = ft_calloc(sizeof(char *), a_size + 2);
	if (!array)
		return (0); //error
	while ((*node)->cmd && (*node)->cmd[i])
	{
		array[i] = (*node)->cmd[i];
		i++;
	}
	array[i] = lst->str;
	if ((*node)->cmd)
		free((*node)->cmd);
	(*node)->cmd = array;
	return (1);
}

int	select_in_out(t_f_lexor *lst, t_chris **node, int *n_pipe)
{
	if (lst->type == OUT_A || lst->type == OUT_T)
	{
		if ((*node)->fd_out)
			close((*node)->fd_out);
		(*n_pipe) = 0;
		(*node)->fd_out = open_fd(lst->str, lst->type);
		if ((*node)->fd_out == -1)
			return (0); //error
	}
	else if (lst->type == INFILE)
	{
		if ((*node)->fd_in)
			close((*node)->fd_in);
		(*node)->fd_in = open_fd(lst->str, lst->type);
		if ((*node)->fd_in == -1)
			return (0); //error
	}
	return (1);
}

t_chris	*creat_chris(t_f_lexor *lst, t_chris **node, int pipe)
{
	t_chris	*n_node;
	
	n_node = NULL;
	if (!lst)
		return (NULL);
	if (!node)
	{
		n_node = ft_calloc(sizeof(t_chris), 1);
		if (!n_node)
			return (NULL);
		return (creat_chris(lst, &n_node, pipe));
	}
	else if (lst->type == ARG)
	{
		if (!arg_format(lst, node))
			return (NULL); //error
	}
	else if (lst->type == OUT_A || lst->type == OUT_T || lst->type == INFILE)
	{
		if (!select_in_out(lst, node, &pipe))
			return (NULL); //error
	}
	if (pipe == 1 && lst->type == PIPE)
		(*node)->pipe = creat_chris(lst->next, NULL, 1);
	else if (!pipe && lst->type == PIPE)
		(*node)->next = creat_chris(lst->next, NULL, 1);
	else
		creat_chris(lst->next, node, pipe);
	return (*node);
}

t_chris	*wish_lexor(char *rl_args)
{
	t_chris		*c_lst;
	t_f_lexor	*lst;

	if (!check_rl_args(rl_args))
		return (NULL); //error
	lst = w_lexor_sort(rl_args);
	c_lst = creat_chris(lst, NULL, 1);
	lexor_lstclear(&lst);
	return (c_lst);
}
