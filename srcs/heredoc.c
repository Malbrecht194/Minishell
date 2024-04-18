/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:37:21 by malbrech          #+#    #+#             */
/*   Updated: 2024/04/18 15:15:10 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>
#define BUFF_SIZE 1024

// Fonction pour générer un nom de fichier aléatoire
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
		printf("Message d'erreur");
	r = read(fd, buff, 16);
	if (r == -1)
		printf("Message d'erreur");
	path = ft_strjoin("/tmp/minish_here_doc", buff);
	if (path == NULL)
		printf("Message d'erreur");
	close(fd);
	return (path);
}

// Fonction pour remplacer les variables par leurs valeurs
char	*expand_variables(const char *line)
{
	return (strdup(line));
}

void	heredoc(const char *delimiter)
{
	char	buffer[BUFFER_SIZE];
	char	*filename;
	int		fd;
	int		i;
	ssize_t	bytes_read;

	i = 0;
	filename = rand_path();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier de sortie");
		exit(EXIT_FAILURE);
	}
	printf("Entrez du texte (terminer avec %s)\n", delimiter);
	bytes_read = read(STDIN_FILENO, &buffer[i], 1);
	while ((bytes_read) > 0)
	{
		if (strncmp(buffer, delimiter, strlen(delimiter)) == 0)
			break ;
		write(fd, buffer, strlen(buffer));

		if (i >= BUFF_SIZE - 1)
		{
			printf("Erreur: Dépassement de capacité du buffer\n");
			exit(EXIT_FAILURE);
		}
	}
	close(fd);
	printf("Le texte a été écrit dans le fichier '%s'.\n", filename);
}

int	main(void)
{
	heredoc("FIN\n");
	return (0);
}

// void	generate_random_filename(char *filename)
// {
// 	char	*charset;
// 	int		length;
// 	int		i;

// 	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
// 	length = 15;
// 	i = 0;
// 	while (i < length)
// 	{
// 		filename[i] = charset[rand() % (sizeof(charset) - 1)];
// 		i++;
// 	}
// 	filename[length] = '\0';
// }