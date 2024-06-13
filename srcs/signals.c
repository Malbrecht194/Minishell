/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:31:31 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/13 19:07:37 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_sigint(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	char	c;

	g_sig = sig;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signals_init(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, &handler_sigint);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	if (sig == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		return ;
	}
	if (sig == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return ;
	}
	if (sig == 4)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_sigint_heredoc);
		return ;
	}
}

