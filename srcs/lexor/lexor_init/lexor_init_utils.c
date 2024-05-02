/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeo <xeo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:17:06 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/02 23:58:01 by xeo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check_builtins.h>
#include <lexor.h>
#include <expand.h>
#include <minishell.h>

void	ft_initadd_back(t_init **lst, t_init *new)
{
	t_init	*tmp;

	if (!lst || !new)
		return ;
	else if (!(*lst))
		*lst = new;
	else
	{
		tmp = ft_initlast(*lst);
		tmp->next = new;
	}
}

t_init	*ft_initlast(t_init *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_initclear(t_init **lst)
{
	t_init	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	tmp_count_word(char const *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == sep)
		i++;
	if ((s[i] == 0))
		return (0);
	count = 1;
	while (s[i])
	{
		if ((s[i] == sep) && (s[i + 1] != sep))
		{
			count += 1;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static int	tmp_count_char(char *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((s[i] != sep) && s[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char	**tmp_split_format(char **buff, char const *s, char sep)
{
	int	i;
	int	g;
	int	count;

	i = 0;
	g = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i] == '\0')
			break ;
		count = tmp_count_char((char *)s + i, sep);
		buff[g] = ft_substr(s, i, count);
		if (!buff[g])
			return (NULL);
		i += count;
		g++;
	}
	buff[g] = NULL;
	return (buff);
}

char	**tmp_split(char const *s, char sep)
{
	char	**buff;

	if (!s)
		return (NULL);
	buff = ft_calloc(sizeof(char *), tmp_count_word(s, sep) + 1);
	if (!buff)
		return (NULL);
	buff = tmp_split_format(buff, s, sep);
	return (buff);
}

t_init	*relink_node(t_init *first, t_init *last, t_init *node, t_minishell *minish)
{
	char	**arg;
	char	*str;
	t_init	*new;
	int		i;

	i = 0;
	arg = tmp_split(node->str, -1);
	if (!arg)
	{
		ft_initclear(&first);
		ft_initclear(&last);
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	free(node->str);
	node->str = arg[0];
	if (!arg[1])
	{
		free(arg[1]);
		free(arg);
		node->next = last;
		return (first);
	}
	new = ft_calloc(sizeof(t_init), 1);
	if (!new)
	{
		ft_free_2d_array(arg, ft_array_len(arg));
		ft_initclear(&first);
		ft_initclear(&last);
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	new->type = ARG;
	str = ft_unsplit(arg + 1, -1);
	if (!str)
	{
		ft_free_2d_array(arg, ft_array_len(arg));
		ft_initclear(&first);
		ft_initclear(&last);
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	while (arg[++i])
		free(arg[i]);
	free(arg);
	new->str = str;
	node->next = new;
	return (relink_node(first, last, new, minish));
}

t_init	*check_init_args(t_init *first, t_init *prev, t_init *node, t_minishell *minish)
{
	t_init	*tmp;

	if (node)
		tmp = node->next;
	if (!prev && !node)
		return (NULL);
	else if (!node)
		return (first);
	if (node->type == ARG && !node->str[0])
	{
		if (prev)
			prev->next = tmp;
		if (node->str)
			free(node->str);
		free(node);
		minish->last_error = 0;
		return (check_init_args(first, prev, tmp, minish));
	}
	if (!first)
		first = node;
	if (node->type == ARG && node->str && ft_strchr(node->str, -1))
		return (check_init_args(first, prev, relink_node(node, node->next, node, minish), minish));
	if (node->type != HEREDOC && node->type != PIPE)
		delete_quote(&node->str);
	return (check_init_args(first, node, tmp, minish));
}
