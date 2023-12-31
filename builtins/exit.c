/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:46:50 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/28 08:09:17 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

static bool	is_numeric_str(char *str)
{
	if (!str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit((int)*str) == 0)
			return (false);
		str++;
	}
	return (true);
}

static int	check_args_size(t_node *node, t_envval *envval)
{
	size_t	len;

	len = 0;
	while (node->args[len])
		len++;
	if (2 < len)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		envval->status = 1;
		return (1);
	}
	return (0);
}

void	ft_exit(t_node *node, t_envval *envval)
{
	int		status;

	status = 0;
	if (ft_strcmp(node->args[0], "exit") == 0)
	{
		write(1, "exit\n", 5);
		if (node->args[1] && is_numeric_str(node->args[1]))
		{
			if (check_args_size(node, envval) == 1)
				return ;
			else
				status = ft_atoi(node->args[1]);
		}
		else if (node->args[1])
		{
			write(2, "minishell: exit: numeric argument required\n", 43);
			status = 255;
		}
		else
			status = envval->status;
		node_free(node);
		exit(status);
	}
}
