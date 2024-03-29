/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:40:53 by malbrech          #+#    #+#             */
/*   Updated: 2024/03/28 09:13:20 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"
#include "../INCLUDES/lexor.h"

// t_chris	*lexor(char *str, t_chris *cmd_line)
// {
// 	int	i;

// 	i = 0;
// }

// A REVOIR POUR NOS CAS A NOUS
char	**create_cmd_array(char *str)
{
	int		i;
	char	**cmd_block;
	char	*cmd;
	char	*buff;

	i = 0;
	cmd = NULL;
	buff = NULL;
	while (str[i++])
	{
		if (buff)
			free(buff);
		if (str[i] == ' ')
			i++;
		if (str[i] != ' ' && str[i] != 9)
			buff = extract_from_cmd(str, i);
		while (str[i] != ' ' && str[i] != 9)
			i++;
		if (buff)
			cmd = ft_strcat_m(cmd, buff);
	}
	if (buff)
		free(buff);
	cmd_block = ft_split(cmd, '/');
	return (cmd_block);
}

// Regler le probleme de ce fdp
char	*extract_from_cmd(char *str, int i)
{
	int		tmp;
	int		count;
	int		y;
	char	*buff;

	tmp = i;
	count = 0;
	y = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		count++;
	i = tmp;
	buff = malloc(count + 1 * sizeof(char));
	while (str[i++] && str[i] != ' ' && str[i] != '\t')
	{
		buff[y] = str[i];
		y++;
	}
	buff[y] = 0;
	return (buff);
}

/**************************** TEST *******************************/

int	main(int ac, char **av)
{
	int		i;
	char	**cmd_array;

	i = 0;
	cmd_array = NULL;
	if (ac != 2)
		return (1);
	cmd_array = create_cmd_array(av[1]);
	while (cmd_array[i++])
		printf("%s\n", cmd_array[i]);
	return (0);
}
