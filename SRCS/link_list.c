/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/18 14:10:44 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

t_pipex	*creat_and_format_node(char *command, char **env)
{
	t_pipex	*node;

	node = malloc(sizeof(t_pipex));
	if (!node)
		return (NULL);
	node->cmd.command = test_access(command, env);
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

t_pipex	*create_link_list(char **commands, char **env)
{
	t_pipex	*first_node;
	t_pipex	*actual_node;
	int		i;

	i = 1;
	first_node = creat_and_format_node(commands[0], env);
	if (!first_node)
	{
		printf("command not found !\n");
		exit(0); //error
		//error_handler(LLIST_FAIL);
	}
	while (commands[i])
	{
		actual_node = creat_and_format_node(commands[i], env);
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
