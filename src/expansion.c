/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:52:58 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/22 19:22:48 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

char	*expand_parameter(char *token, t_envval *envval)
{
	t_parm	*parm;
	char	*new_token;

	if (!token || (token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
		return (token);
	parm = parameter_init(token);
	if (!parm)
		return (token);
	parm->str = check_parameter(parm, envval);
	if (!parm->str)
		return (token);
	new_token = ft_strdup(parm->str);
	free(parm->str);
	free(parm);
	free(token);
	return (new_token);
}

static void	check_quote(t_quote_status *q_status, char c)
{
	if (c == '\'' && !q_status->d_quote)
	{
		if (!q_status->s_quote)
			q_status->s_quote = true;
		else
			q_status->s_quote = false;
	}
	else if (c == '\"' && !q_status->s_quote)
	{
		if (!q_status->d_quote)
			q_status->d_quote = true;
		else
			q_status->d_quote = false;
	}
	else if (!q_status->s_quote && !q_status->d_quote
		&& (c == '\'' || c == '\"'))
		;
	else
		q_status->result[q_status->i++] = c;
}

char	*delete_quote(char *token)
{
	t_quote_status	*q_status;
	char			*str;
	size_t			i;

	if (!token)
		return (NULL);
	q_status = quote_status_init(token);
	if (!q_status)
		return (NULL);
	i = 0;
	while (i < q_status->len)
	{
		check_quote(q_status, token[i]);
		i++;
	}
	str = ft_strdup(q_status->result);
	free(q_status->result);
	free(q_status);
	free(token);
	return (str);
}

static int	expansion(char **array, t_node *node, t_envval *envval)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		array[i] = check_command(array[i], node, envval);
		array[i] = expand_parameter(array[i], envval);
		array[i] = delete_quote(array[i]);
		i++;
	}
	if (node->args[0] && array[0] && array[0][0] != '\0')
	{
		free(node->name);
		node->name = search_path(array[0], envval->env);
	}
	else
	{
		envval->status = 1;
		return (1);
	}
	return (0);
}

int	check_exp(t_node *node, t_envval *envval)
{
	if (!node)
		return (0);
	if (node->args)
	{
		if (expansion(node->args, node, envval) == 1)
			return (1);
	}
	if (check_redir(node, envval) == 1)
		return (1);
	if (node->left)
	{
		if (check_exp(node->left, envval) == 1)
			return (1);
	}
	if (node->right)
	{
		if (check_exp(node->right, envval) == 1)
			return (1);
	}
	return (0);
}
