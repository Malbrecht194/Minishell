/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaouas <mhaouas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:25:43 by mhaouas           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:49 by mhaouas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <expand.h>
#include <minishell.h>

static void	sign_and_skip(char **str, int *i, int *sign)
{
	while (*str[(*i)] == ' ' || ('\t' <= *str[*i] && *str[*i] <= '\r'))
		(*i)++;
	if (*str[*i] == '-' || *str[*i] == '+')
	{
		if (*str[(*i)++] == '-')
			*sign = 1;
	}
}

unsigned char	convert_ret_exit(char *str, t_minishell *minish)
{
	int				i;
	int				sign;
	unsigned long	nbr;

	i = 0;
	sign = 0;
	nbr = 0;
	while (str[i])
	{
		sign_and_skip(&str, &i, &sign);
		while (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + (str[i++] - '0');
	}
	if (nbr <= (unsigned long)LONG_MAX + sign)
	{
		if (sign == 0)
			return (nbr);
		else
			return (-nbr);
	}
	error_handle(NUM_ARG_REQUIRED, minish, "exit", exit);
	return (2);
}

int	check_exit_arg(char *arg, t_minishell *minish, int ac)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!arg)
		return (minish->last_error);
	else if (arg[i])
	{
		if ((!ft_isdigit(arg[0]) && arg[0] != '+' && arg[0] != '-'))
			error_handle(NUM_ARG_REQUIRED, minish, "exit", exit);
		while (arg[++i])
		{
			if (arg[i] && !ft_isdigit(arg[i]))
				error_handle(NUM_ARG_REQUIRED, minish, "exit", exit);
		}
		ret = convert_ret_exit(arg, minish);
	}
	if (ac > 2)
	{
		error_handle(TOO_MANY_ARGS, minish, "exit", NULL);
		return (-1);
	}
	return (ret);
}

int	ft_exit(int ac, char **av, t_exec *cmd, t_minishell *minish)
{
	int		err_ret;
	char	*tmp;

	(void)cmd;
	err_ret = 2;
	if (ac > 1)
		tmp = av[1];
	if (minish->cmd_line && !minish->cmd_line->next)
		ft_printf_fd(1, "exit\n");
	if (ac == 1)
		err_ret = minish->last_error;
	else
	{
		while (tmp && *tmp && check_ifs(*tmp) == -1)
			tmp++;
		err_ret = check_exit_arg(tmp, minish, ac);
		if (err_ret == -1)
			return (1);
	}
	free_minish(minish);
	exit(err_ret);
}
