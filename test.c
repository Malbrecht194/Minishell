/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:47:25 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/13 14:57:31 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/minishell.h"

int	main()
{
	printf("%s\n\n",getenv("PWD"));
	printf("%s\n", getcwd(NULL, 0));
}