/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:05:49 by resaito           #+#    #+#             */
/*   Updated: 2023/11/16 17:49:53 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>

int	redir_dup(t_node *node, int *pipefd)
{
	if (!(node->redir != NULL && (node->redir->type == N_REDIR_OUT
				|| node->redir->type == N_REDIR_APPEND)))
		return (0);
	close(pipefd[0]);
	while (node->redir != NULL && (node->redir->type == N_REDIR_OUT
			|| node->redir->type == N_REDIR_APPEND))
	{
		if (node->redir->type == N_REDIR_OUT)
			pipefd[1] = open(node->redir->file[0],
					O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		else
			pipefd[1] = open(node->redir->file[0],
					O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		node->redir = node->redir->next;
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	return (0);
}

int	indirect_exec(t_node *node, int dupout)
{
	if (!(node->redir != NULL && node->redir->type == N_REDIR_IN))
		return (0);
	while (node->redir != NULL && (node->redir->type == N_REDIR_IN))
	{
		if (node->redir->type == N_REDIR_IN)
			dupout = open(node->redir->file[0], O_RDONLY);
		node->redir = node->redir->next;
	}
	dup2(dupout, STDIN_FILENO);
	close(dupout);
	return (0);
}

int	heredoc_exec(char *delimiter)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(-1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

// t_node *make_node(enum e_type node_type, char **args)
// {
//     t_node *node;

//     node = calloc(sizeof(t_node), 1);
//     node->type = node_type;
//     node->name = args[0];
//     node->args = args;
//     return node;
// }

// t_redir *make_redir(enum e_type node_type, char **file)
// {
// 	t_redir *redir;

// 	redir = malloc(sizeof(t_redir) * 1);
// 	redir->file = file;
// 	redir->type = node_type;
// 	redir->next = NULL;
// 	return redir;
// }

// int main()
// {
//     t_node *ast;
// 	t_redir *redir;
// 	t_redir *redir2;
//     // char *args[] = {"/usr/bin/wc", "-l", NULL};
//     // char *args2[] = {"/bin/cat", NULL};
//     // char *args3[] = {"/usr/bin/grep", "hoge", NULL};
//     char *ls[] = {"/bin/ls", NULL};
//     char *cat[] = {"/bin/cat", NULL};
//     char *wc[] = {"/usr/bin/wc", "-l", NULL};
//     char *grep[] = {"/usr/bin/grep", "hoge", NULL};
// 	char *file[] = {"hoge.txt", NULL};
// 	char *file2[] = {"fuga.txt", NULL};
// 	char *file3[] = {"piyo.txt", NULL};
// 	char *eof[] = {"hoge", NULL};

//     // ast = make_node(N_PIPE, ls);
//     ast = make_node(N_COMMAND, cat);
//     // ast->right = make_node(N_PIPE, ls);
//     // ast->right = make_node(N_COMMAND, grep);
//     // ast->right->right = make_node(N_COMMAND, wc);

// 	redir = make_redir(N_REDIR_HERE, eof);
// 	// redir->next = make_redir(N_REDIR_IN, file3);
// 	// redir->next->next = make_redir(N_REDIR_OUT, file2);
// 	ast->redir = redir;
// 	// redir->next = redir2;
//     heredoc_exec(ast->redir->file[0]);
//     // command_exec(args2, true);
//     // command_exec(args3, false);
//     // wait(NULL);
//     // wait(NULL);
// }
