/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexor.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:37:38 by malbrech          #+#    #+#             */
/*   Updated: 2024/03/28 09:08:24 by malbrech         ###   ########.fr       */
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
	char				**cmd;
	int					fd_in;
	int					fd_out;
	int					redirection;
	pid_t				pid;
	struct s_chris		*pipe;
	struct s_chris		*next;
}						t_chris;

/*================================ FONCTIONS ================================*/

int		is_heredoc(char *str, int i);
int		is_append(char *str, int i);
void	try_cmd(char **cmd);
char	**create_cmd_array(char *str);
char	*ft_strcat_m(char *s1, char *s2);
char	*extract_from_cmd(char *str, int i);
// int	parenthesis(char *str, int i);

#endif  