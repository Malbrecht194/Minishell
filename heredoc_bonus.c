/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:07:56 by mhaouas           #+#    #+#             */
/*   Updated: 2023/12/19 14:53:12 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_setup(t_pipex *pipe_struct, int argc, char **argv, char **envp)
{
	int		fd_out;
	char	*limiter;
	char	*content;

	limiter = argv[1];
	content = ft_calloc(1, 1);
	if (!content)
		error_handler(MALLOC_ERROR);
	fd_out = open("TMP_FILE", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_pipe_lstclear(&pipe_struct);
		error_handler(FD_INPUT_ERROR);
	}
	while (ft_strnstr(content, limiter, ft_strlen(limiter)) == 0)
	{
		ft_printf("heredoc> ");
		free(content);
		content = gnl(STDIN_FILENO);
		ft_putstr_fd(content, fd_out);
	}
	free(content);
	close(fd_out);
	here_doc_next(pipe_struct, envp, argv, argc);
}

void	here_doc_next(t_pipex *pipe_struct, char **envp, char **argv, int argc)
{
	int		fd_in_out[2];

	fd_in_out[READ_FD] = open("TMP_FILE", O_RDONLY);
	if (fd_in_out[READ_FD] == -1)
		fd_input_check(fd_in_out, pipe_struct, READ_FD);
	fd_in_out[WRITE_FD] = open(argv[argc - 1], \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_in_out[WRITE_FD] == -1)
		fd_input_check(fd_in_out, pipe_struct, WRITE_FD);
	first_process(pipe_struct, fd_in_out, envp);
	unlink("TMP_FILE");
}

char	*gnl(int fd)
{
	static char	*storage;
	char		*buffer;

	buffer = NULL;
	storage = gnl_loop(storage, fd);
	buffer = dup_to_new_line(storage);
	storage = new_storage(storage);
	if (!storage && !buffer)
		free(storage);
	return (buffer);
}
