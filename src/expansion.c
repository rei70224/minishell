/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:52:58 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/14 16:31:51 by fwatanab         ###   ########.fr       */
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

static char	*delete_quote(char *token)
{
	t_quote_status	*q_status;
	char			*str;
	size_t			i;

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
	return (str);
}

//static char	*delete_quote(char *token)
//{
//	size_t	length;
//	char	*result;
//	size_t	i;
//	size_t	j;
//
//	if (token == NULL)
//		return (NULL);
//	length = strlen(token);
//	result = malloc(length + 1);
//	if (result == NULL)
//		return (NULL);
//	i = 0;
//	j = 0;
//	while (i < length)
//	{
//		if (token[i] != '\'' && token[i] != '\"')
//			result[j++] = token[i];
//		i++;
//	}
//	result[j] = '\0';
//	return (result);
//}

char	*expansion(char **array, t_envval *envval)
{
	char	*new_array;
	size_t	i;

	i = 0;
	new_array = NULL;
	while (array[i])
	{
		array[i] = check_command(array[i], envval);
		array[i] = expand_parameter(array[i], envval);
		array[i] = delete_quote(array[i]);
		i++;
	}
	if (array[0])
		return (search_path(array[0], envval->env));
	return (NULL);
}

void	check_exp(t_node *node, t_envval *envval)
{
	size_t	i;

	i = 0;
	if (!node)
		return ;
	if (node->args)
		node->name = expansion(node->args, envval);
	if (node->left)
		check_exp(node->left, envval);
	if (node->right)
		check_exp(node->right, envval);
}
