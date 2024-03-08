/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/07 20:41:27 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

t_pipex	*creat_and_format_node(char *command)
{
	t_pipex	*node;

	node = malloc(sizeof(t_pipex));
	if (!node)
		return (NULL);
	node->cmd.command = test_access(command);
	if (!node->cmd.command)
	{
		free(node);
		return (NULL);
	}
	node->cmd.flags = get_flags(command, node->cmd.command);
	if (!node->cmd.flags || !node->cmd.flags[0])
	{
		free(node->cmd.command);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

t_pipex	*create_link_list(char **commands)
{
	t_pipex	*first_node;
	t_pipex	*actual_node;
	int		i;

	i = 1;
	first_node = creat_and_format_node(skip_quoting(commands[0]));
	if (!first_node)
	{
		printf("command not found !\n");
		exit(0); //error
		//error_handler(LLIST_FAIL);
	}
	while (commands[i])
	{
		actual_node = creat_and_format_node(skip_quoting(commands[i]));
		if (!actual_node)
		{
			ft_pipe_lstclear(&first_node);
			exit(0); //error
			//error_handler(LLIST_FAIL);
		}
		ft_pipe_lstadd_back(&first_node, actual_node);
		i++;
	}
	return (first_node);
}
