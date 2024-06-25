/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:31:31 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/25 18:44:54 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_sigint(int sig)
{
	g_sig.signals = sig;
	*g_sig.error = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	char	c;

	g_sig.signals = sig;
	*g_sig.error = 130;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_messages(t_minishell *minish, int *bool)
{
	if (minish->last_error == 130 && (*bool) == 0)
	{
		write(1, "\n", 1);
		(*bool)++;
	}
	else if (minish->last_error == 131 && (*bool) == 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		(*bool)++;
	}
}

void	signals_init(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, &handler_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 2)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig == 4)
	{
		signal(SIGINT, &handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 5)
	{
		signal(SIGPIPE, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
