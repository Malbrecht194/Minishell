/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:47:35 by mhaouas           #+#    #+#             */
/*   Updated: 2024/05/14 17:01:03 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <lexor.h>
# include <libft.h>
# define IFS " \t\n"

void	format_rl(char **arg, t_minishell *minish);
int		do_expand(char **arg, int *index, char state, t_minishell *minish);
void	check_expand(char **arg, t_minishell *minish);
int		to_next_quote(char *arg, char quote);
void	delete_quote(char **arg);
int		quote_in_expand(char **arg, char *to_check, int index, int end_of_exp);
int		expand_env(char **arg, int index, t_minishell *minish);
char	check_ifs(char a_char);
size_t	env_len(char *env);
void	rm_char(char **arg, int index);
size_t	skip_heredoc(char *arg, int index);
int		is_ifs(char a_char);
int		skip_ifs(char *str);
int		check_arg_quotes(char **arg, int index, char quote);

#endif