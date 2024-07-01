/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:31:31 by malbrech          #+#    #+#             */
/*   Updated: 2024/07/01 11:11:04 by mhaouas          ###   ########.fr       */
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

void	signal_error(t_minishell *minish)
{
	if (g_sig == SIGINT)
		minish->last_error = 130;
	g_sig = 0;
}

void	signals_init(int sig, t_minishell *minish)
{
	if (sig == 1 || sig == 2 || sig == 4 || sig == 5)
		signal(SIGQUIT, SIG_IGN);
	else if (sig == 3)
		signal(SIGQUIT, SIG_DFL);
	if (sig == 1)
	{
		signal(SIGINT, &handler_sigint);
		signal_error(minish);
	}
	else if (sig == 2)
		signal(SIGINT, SIG_IGN);
	else if (sig == 3)
		signal(SIGINT, SIG_DFL);
	else if (sig == 4)
	{
		signal(SIGINT, &handle_sigint_heredoc);
		signal_error(minish);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 5)
		signal(SIGPIPE, SIG_IGN);
}
