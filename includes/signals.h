/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:56 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/27 14:47:37 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <minishell.h>
# include <termios.h>

/*================================= FUNCTIONS ================================*/
void		signals_init(int sig, t_minishell *minish);
void		handler_sigint(int sig);
void		handle_sigint_heredoc(int sig);
void		signal_messages(t_minishell *minish, int *bool);
void		signal_error(t_minishell *minish);

#endif