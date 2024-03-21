/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:29:13 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/18 15:34:07 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

void	expand_env(char **add_to, char **to_search, char **env)
{
	int		len;
	char	*s_env;

	len = 0;
	if ((*to_search)[0] == '$')
		*to_search += 1;
	while (ft_isalnum((*to_search)[len]) || (*to_search)[len] == '_')
		len++;
	s_env = ft_substr((*to_search), 0, len);
	if (add_to)
	{
		if (!ft_getenv(s_env, env))
			*add_to = join_and_free(*add_to, "");
		else
			*add_to = join_and_free(*add_to, ft_getenv(s_env, env));
		*add_to = join_and_free(*add_to, (*to_search) + len);
	}
	else
	{
		if (!ft_getenv(s_env, env))
			*to_search = ft_strdup("");
		else
			*to_search = ft_strdup(ft_getenv(s_env, env));
	}
	free(s_env);
}
