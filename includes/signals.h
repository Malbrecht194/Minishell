/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:56 by malbrech          #+#    #+#             */
/*   Updated: 2024/06/13 17:15:06 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <minishell.h>
# include <termios.h>

/*================================= FUNCTIONS ================================*/
int			signals_init(int sig);
void		handler_sigint(int sig);
void		clear_signals(void);
void		handle_sigint_heredoc(int sig);

#endif