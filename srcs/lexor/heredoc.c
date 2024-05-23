/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:37:21 by malbrech          #+#    #+#             */
/*   Updated: 2024/05/16 10:30:40 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexor.h>
#include <expand.h>

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

char	*expand_variables(char *input, t_minishell *minish)
{
	char	*expanded_line;
	int		index;

	expanded_line = ft_strdup(input);
	if (!expanded_line)
	{
		error_handle(MALLOC_ERROR, minish, NULL, NULL);
		return (NULL);
	}
	index = 0;
	while (expanded_line[index])
	{
		if (expanded_line[index] == '\'' || \
			expanded_line[index] == '\"' || expanded_line[index] == '$')
			do_expand(&expanded_line, &index, 0, minish);
		else
			index++;
	}
	return (expanded_line);
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

static void	heredoc_rl(char *delimiter, int fd, t_minishell *minish)
{
	char	*buffer;
	char	*expanded_line;

	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
		{
			ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		expanded_line = expand_variables(buffer, minish);
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(buffer);
		free(expanded_line);
	}
}

int	heredoc(char *delimiter, t_minishell *minish)
{
	char	*filename;
	int		fd;

	filename = rand_path();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Heredoc");
		exit(EXIT_FAILURE);
	}
	add_heredoc_name(minish, filename);
	heredoc_rl(delimiter, fd, minish);
	return (fd);
}
