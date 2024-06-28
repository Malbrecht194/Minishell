/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:37:21 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/28 13:37:10 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexor.h>
#include <expand.h>
#include <signals.h>

char	*rand_path(void)
{
	char	buff[16];
	char	*path;
	int		r;
	int		fd;

	r = 0;
	fd = 0;
	path = NULL;
	fd = open("/dev/random", O_RDONLY, 0644);
	if (fd == -1)
		perror("/dev/random");
	r = read(fd, buff, 16);
	if (r == -1)
		printf("Message d'erreur");
	path = ft_strjoin("/tmp/minish_here_doc", buff);
	if (path == NULL)
		printf("Message d'erreur");
	close(fd);
	return (path);
}

static void	expand_heredoc(char **input, t_minishell *minish)
{
	size_t	index;

	index = 0;
	while ((*input)[index])
	{
		if ((*input)[index] == '$')
		{
			rm_char(input, index);
			index += expand_env(input, index, minish) - 1;
		}
		if (index++ > ft_strlen((*input)))
			break ;
	}
}

static void	add_heredoc_name(t_minishell *minish, char *filename)
{
	char	**buff;
	int		i;
	int		len;

	len = ft_array_len((void **)minish->heredocs);
	buff = minish->heredocs;
	minish->heredocs = ft_calloc(sizeof(char *), len + 2);
	if (minish->heredocs == NULL)
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
	i = 0;
	while (i < len)
	{
		minish->heredocs[i] = buff[i];
		i++;
	}
	minish->heredocs[i] = filename;
	free(buff);
}

static void	heredoc_rl(char *delimiter, int fd,
	t_minishell *minish, int need_exp)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("> ");
		if (g_sig == SIGINT)
		{
			free(buffer);
			break ;
		}
		if (buffer == NULL)
		{
			error_handle(FAIL_HEREDOC, minish, delimiter, NULL);
			break ;
		}
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		if (need_exp)
			expand_heredoc(&buffer, minish);
		ft_printf_fd(fd, "%s\n", buffer);
		free(buffer);
	}
}

int	heredoc(char *delimiter, t_minishell *minish)
{
	char	*filename;
	int		fd;

	fd = open_rand(&filename);
	add_heredoc_name(minish, filename);
	g_sig = 0;
	signals_init(4, minish);
	heredoc_rl(delimiter, fd, minish, need_expand(&delimiter));
	close(fd);
	if (g_sig == SIGINT)
	{
		ft_free_2d_array(minish->heredocs, ft_array_len(minish->heredocs));
		return (-2);
	}
	fd = open(filename, O_RDONLY);
	return (fd);
}
