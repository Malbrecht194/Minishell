/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:06:32 by mhaouas           #+#    #+#             */
/*   Updated: 2024/04/03 11:13:45 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_BUILTINS_H
# define CHECK_BUILTINS_H

# include "builtins.h"
# include "../Libft/libft.h"
# include "minishell.h"

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
void	exec_builtins(t_minishell *minish, t_pipex *cmd, int b_num);
int		is_builtins(char *cmd);

#endif