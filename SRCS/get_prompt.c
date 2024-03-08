/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:19:24 by mhaouas           #+#    #+#             */
/*   Updated: 2024/03/04 20:48:34 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

char	*get_prompt(void)
{
	t_prompt	prompt;

	prompt.login = getenv("USER");
	prompt.location = "\001\033[32m\002minishell";
	prompt.cwd = getcwd(NULL, 0);
	prompt.tmp_prompt = ft_strjoin("\001\033[37m\002", prompt.login);
	prompt.tmp_prompt2 = ft_strjoin(prompt.tmp_prompt, "\001\033[31m\002@");
	free(prompt.tmp_prompt);
	prompt.tmp_prompt = ft_strjoin(prompt.tmp_prompt2, prompt.location);
	free(prompt.tmp_prompt2);
	prompt.tmp_prompt2 = ft_strdup(ft_strnstr(prompt.cwd, prompt.login,
		ft_strlen(prompt.cwd)) + ft_strlen(prompt.login));
	prompt.pwd = ft_strjoin(":\001\033[36m\002~", prompt.tmp_prompt2);
	free(prompt.tmp_prompt2);
	prompt.tmp_prompt2 = ft_strjoin(prompt.tmp_prompt, prompt.pwd);
	prompt.final_prompt = ft_strjoin(prompt.tmp_prompt2, ">\001\033[0m\002 ");
	free(prompt.tmp_prompt2);
	free(prompt.pwd);
	free(prompt.cwd);
	free(prompt.tmp_prompt);
	return(prompt.final_prompt);
}
