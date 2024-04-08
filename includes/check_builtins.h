/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:06:32 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/08 13:42:40 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_BUILTINS_H
# define CHECK_BUILTINS_H

# include <builtins.h>
# include <minishell.h>
# include <libft.h>

enum	e_builtins
{
	FT_CD,
	FT_ECHO,
	FT_ENV,
	FT_EXPORT,
	FT_PWD,
	FT_UNSET,
	FT_EXIT,
	NO_BUILTINS
};

void	check_cmd(t_minishell *minish);
int		full_dup(int n_stdin, int n_stdout);
void	exec_builtins(t_minishell *minish, t_chris *cmd, int b_num);
int		is_builtins(char *cmd);

#endif