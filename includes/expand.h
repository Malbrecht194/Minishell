/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:47:35 by mhaouas           #+#    #+#             */
/*   Updated: 2024/06/26 00:14:10 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <lexor.h>
# include <libft.h>
# define IFS " \t\n"

void	format_rl(char **arg, t_minishell *minish);
int		do_simple_expand(char **arg, int *index, t_minishell *minish);
int		do_quote_expand(char **arg, int *index, t_minishell *minish);
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
int		ft_var_name_is_ok(char ***arg, size_t i);

#endif