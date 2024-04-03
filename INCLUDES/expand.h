/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:47:35 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/29 15:27:14 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../Libft/libft.h"
# define IFS " \t\n"

void	format_rl(char **arg, char **env);
void	do_expand(char **arg, int *index, char state, char **env);
void	check_expand(char **arg, char **env);
int		to_next_quote(char *arg, char quot);
void	delete_quote(char **arg);
int		quot_in_expand(char **arg, char *to_check, int index);
int		expand_env(char **arg, int index, char **env);
char	check_ifs(char a_char);
size_t	env_len(char *env);
void	rm_char(char **arg, int index);
size_t	skip_heredoc(char *arg, int index);

#endif