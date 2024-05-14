/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:56 by malbrech          #+#    #+#             */
/*   Updated: 2024/05/14 17:13:24 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <minishell.h>
# include <termios.h>

/*================================= FUNCTIONS ================================*/
void		signals_init(void);
void		handler_sigint(int sig);
void		suppress_output(void);
// void		handler_sigint_heredoc(int sig);

#endif