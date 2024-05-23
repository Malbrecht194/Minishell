/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:31:31 by malbrech          #+#    #+#             */
/*   Updated: 2024/05/16 10:04:15 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>

void	handler_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_sigint_ni(int sig)
{
	(void)sig;
	rl_redisplay();
}

void	clear_signals(void)
{
	int	i;

	i = 0;
	while (i < _NSIG)
	{
		signal(i, SIG_DFL);
		i++;
	}
}

void	signals_init(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}
// void	handle_sigint_heredoc(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	exit(1);
// }
