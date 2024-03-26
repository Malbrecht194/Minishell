/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:37:38 by malbrech          #+#    #+#             */
/*   Updated: 2024/03/26 15:36:06 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXOR_H
# define LEXOR_H

# include "minishell.h"

/*================================ STRUCTURES ================================*/
enum e_lexor
{
	CMD,
	ARG,
	PIPE,
	INFILE,
	HEREDOC,
	OUT_T,
	OUT_A,
};

typedef struct s_chris
{
	char				**content;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_chris		*next;
}						t_chris;

/*================================ FONCTIONS ================================*/

int	is_heredoc(char *str, int i);
int	is_append(char *str, int i);
int	parenthesis(char *str, int i);

#endif  