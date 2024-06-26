/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:38:09 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/11 18:21:10 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>

int	check_flags(char *av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	if (av[i] == '-' && av[i + 1] == 'n')
		i++;
	while (av[i] == 'n')
		i++;
	if (av[i] == 0)
		return (1);
	else
		return (0);
}

int	ft_echo(int ac, char **av, char ***env)
{
	int		nl;
	int		o_nl;
	int		i;

	(void) env;
	nl = 1;
	o_nl = 1;
	i = 0;
	while (ac > 1 && av[++i])
	{
		nl = check_flags(av[i]);
		if (o_nl == 1 && nl == 1)
			continue ;
		ft_printf("%s", av[i]);
		if (av[i + 1])
			ft_printf(" ");
		o_nl = nl;
	}
	if (ac >= 1 && !check_flags(av[1]))
		ft_printf("\n");
	return (0);
}
