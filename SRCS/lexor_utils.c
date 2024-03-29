/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:28:33 by malbrech          #+#    #+#             */
/*   Updated: 2024/03/27 17:10:58 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"
#include "../INCLUDES/lexor.h"

extern char	**environ;

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

char	*ft_strcat_m(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		j;

	dst = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	if (dst)
	{
		i = 0;
		while (s1[i++])
			dst[i] = s1[i];
		dst[i] = '/';
		i++;
		j = 0;
		while (s2[j++])
			dst[i + j] = s2[j];
	}
	free(s1);
	return (dst);
}

void	free_tab(void **test)
{
	int	i;

	i = 0;
	if (!test || !*test)
		return ;
	while (test[i])
	{
		free(test[i]);
		i++;
	}
	free(test);
}

void	try_cmd(char **cmd)
{
	char	**path;
	char	*str;
	pid_t	pid;
	int		i;

	str = getenv("PATH");
	if (str)
	{
		path = ft_split(str, ':');
		pid = fork();
		i = 0;
		if (pid == 0)
		{
			while (path && path[i])
			{
				path[i] = ft_strcat_m(path[i], cmd[0]);
				if (path[i] && !execve(path[i], cmd, environ))
					return ;
				i++;
			}
		}
		else
			waitpid(pid, NULL, 0);
		//ft_free_2d_array((void **)path);
		free_tab((void **)path);
	}
}

int	redirection(char *str, int i);

// int	parenthesis(char *str, int i)
// {
// 	int		count;
// 	int		y;

// 	count = 1;
// 	if (str[i] == '(')
// 	{
// 		while (str[i++])
// 		{
// 			if (str[i] == '(')
// 				count++;
// 		}
// 	}
// 	y = 0;
// 	while (str[y++])
// 	{
// 		if (str[y] == ')')
// 			count--;
// 	}
// 	if (count != 0)
// 	{
// 		printf("Parenthesis Error\n");
// 		return (1);
// 	}
// 	else
// 		return (0);
// }