/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:51 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/03 15:53:17 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

t_pipex	*creat_and_format_node(char *command/*, char **env*/)
{
	t_pipex	*node;

	if (!command)
		return (NULL);
	node = malloc(sizeof(t_pipex));
	if (!node)
		return (NULL);
	node->cmd.cmd = ft_split(command, -1); //get_cmd(command, node->cmd.cmd[0]);
	if (!node->cmd.cmd)
	{
		free(node);
		return (NULL);
	}
	// node->cmd.cmd[0] = test_access(command, env);
	// if (!node->cmd.cmd[0])
	// {
	// 	free(node);
	// 	return (NULL);
	// }
	node->next = NULL;
	return (node);
}

t_pipex	*create_link_list(char **commands/*, char **env*/)
{
	t_pipex	*first_node;
	t_pipex	*actual_node;
	int		i;

	i = 1;
	first_node = creat_and_format_node(commands[0]/*, env*/);
	if (!first_node)
	{
		printf("command not found !\n");
		exit(0); //error
		//error_handler(LLIST_FAIL);
	}
	while (commands[i])
	{
		actual_node = creat_and_format_node(commands[i]/*, env*/);
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
