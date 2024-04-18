/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:25:43 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/18 21:25:37 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

unsigned char	convert_ret_exit(char *str)
{
	int	i;
	int	sign;
	long long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i])
	{
		while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
			i++;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i++] == '-')
				sign *= -1;
		}
		while (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + (str[i++] - '0');
		return (nbr * sign);
	}
	return (0);
}

int	ft_exit(int ac, char **av, t_chris *cmd, t_minishell *minish)
{
	(void) cmd;
	free_minish(minish);
	ft_printf_fd(2, "exit\n");
	if (ac == 1)
		exit(EXIT_SUCCESS);
		
	return (0);
}
