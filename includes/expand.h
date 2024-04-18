/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:47:35 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/18 13:52:04 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <libft.h>
# include <lexor.h>
# define IFS " \t\n"

void	format_rl(char **arg);
void	do_expand(char **arg, int *index, char state, t_minishell *minish);
void	check_expand(char **arg, t_minishell *minish);
int		to_next_quote(char *arg, char quote);
void	delete_quote(char **arg);
int		quote_in_expand(char **arg, char *to_check, int index);
int	expand_env(char **arg, int index, t_minishell *minish);
char	check_ifs(char a_char);
size_t	env_len(char *env);
void	rm_char(char **arg, int index);
size_t	skip_heredoc(char *arg, int index);
int		is_ifs(char a_char);
int		skip_ifs(char *str);

#endif