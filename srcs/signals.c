/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:31:31 by malbrech          #+#    #+#             */
/*   Updated: 2024/05/14 16:16:03 by malbrech         ###   ########.fr       */
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
// void	handle_sigint_heredoc(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	exit(1);
// }
