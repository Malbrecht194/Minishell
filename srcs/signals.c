/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:31:31 by malbrech          #+#    #+#             */
/*   Updated: 2024/04/16 14:38:28 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>

void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

/* Cette fonction est un gestionnaire de signal pour SIGINT, qui est envoyé lorsque l'utilisateur presse Ctrl+C.
Elle écrit un caractère de nouvelle ligne (\n) sur la sortie standard (stdout), puis utilise la bibliothèque readline pour réinitialiser la ligne d'entrée et redisplay.*/
void	handler_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "^C", 2);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

/*Cette fonction est un gestionnaire de signal pour SIGQUIT, qui est envoyé lorsque l'utilisateur presse Ctrl+\.
Elle utilise simplement rl_redisplay() pour réafficher la ligne d'entrée.*/
void	handler_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	signals_init(void)
{
	suppress_output();
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
}
