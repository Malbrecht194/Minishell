/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:28:33 by malbrech          #+#    #+#             */
/*   Updated: 2024/03/26 15:31:04 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	is_heredoc(char *str, int i)
{
	int	y;

	y = 0;
	while (str[i] == '<' && y <= 2)
		y++;
	if (y == 1)
		return (HEREDOC);
	else
		return (INFILE);
}

int	is_append(char *str, int i)
{
	int	y;

	y = 0;
	while (str[i] == '>' && y <= 2)
		y++;
	if (y == 1)
		return (OUT_A);
	else
		return (OUT_T);
}

int	parenthesis(char *str, int i)
{
	int		count;
	int		y;

	count = 1;
	if (str[i] == '(')
	{
		while (str[i++])
		{
			if (str[i] == '(')
				count++;
		}
	}
	y = 0;
	while (str[y++])
	{
		if (str[y] == ')')
			count--;
	}
	if (count != 0)
	{
		printf("Parenthesis Error\n");
		return (1);
	}
	else
		return (0);
}
