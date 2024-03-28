/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:47:35 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/27 15:10:43 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

# define IFS " \t\n"

void	format_rl(char **arg, char **env);
void	do_expand(char **arg, int *index, char state, char **env);

int		check_expand(char **arg, char *pre_quot, char *b_quot, char **env);
int		expand_env(char **add_to, char *to_search, char **env);
int		to_next_quote(char *arg, char quot);
int		check_e_quot(char **arg, char *pre_quot, char *b_quot, char **env);
void	change_expand(char **arg, char **env);
char	*delete_quote(char **arg, char *to_check, char a_quote, int index);
char	check_ifs(char a_char);
size_t	env_len(char *env);

#endif