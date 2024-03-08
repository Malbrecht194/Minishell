/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:25:43 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/07 16:29:21 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	ft_exit(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	exit(EXIT_SUCCESS);
	return (0);
}
