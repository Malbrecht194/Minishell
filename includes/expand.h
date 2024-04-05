/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:47:35 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/05 16:17:22 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <libft.h>
# include "lexor.h"
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
int		is_ifs(char a_char);
int		skip_ifs(char *str);

/*========== TMP */
typedef struct s_f_lex
{
	int				type;
	char			*str;
	struct s_f_lex	*next;
}					t_f_lexor;

char						*sub_and_trim(char *str, int start, size_t len,
								char *set);
int							check_type(char *arg);
t_f_lexor					*li_to_ss(t_f_lexor *lst);
int							open_fd(char *f_name, int type);
void						free_ss(void *to_free);
t_chris						*wish_lexor(char *rl_args);
void	lexor_lstadd_back(t_f_lexor **lst, t_f_lexor *new);
t_f_lexor	*lexor_lstlast(t_f_lexor *lst);
void	lexor_lstclear(t_f_lexor **lst);


#endif