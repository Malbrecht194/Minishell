/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:40:53 by malbrech          #+#    #+#             */
/*   Updated: 2024/03/26 15:31:08 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

t_chris	*lexor(char *str, t_chris *cmd_line)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			parenthesis(str, i);
		if (str[i] == '<')
			is_heredoc(str, i);
		if (str[i] == '>')
			is_append(str, i);
		i++;
	}
}
/************************* TEST PARENTHESIS ***************************/

// int	main(int ac, char **av)
// {
// 	int	test; 
// 	int	i;

// 	i = 0;
// 	if (ac != 2)
// 		return (1);
// 	while (av[1][i++])
// 	{
// 		if (av[1][i] == '(')
// 		{
// 			test = parenthesis(av[1], i);
// 			break ;
// 		}
// 	}
// 	printf("%d\n", test);
// 	return (0);
// }
