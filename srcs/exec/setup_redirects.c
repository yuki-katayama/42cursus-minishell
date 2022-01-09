/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:18:30 by nyokota           #+#    #+#             */
/*   Updated: 2021/12/23 16:43:06 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "utils.h"
#include "parser.h"
#include "expansion.h"

int	get_fd(t_node *node, t_env *env, int read_fd)
{
	int	fd;

	if (node->kind == TK_RO)
		fd = open(node->str, \
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->kind == TK_DRO)
		fd = open(node->str, \
					O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->kind == TK_RI)
		fd = open(node->str, O_RDONLY);
	if (node->kind == TK_DRI)
		fd = here_doc(node->str, env, read_fd);
	return (fd);
}

static int	change_fd(t_node *node, int fd)
{
	if (fd >= 0)
	{
		node->dup_fd = xdup(node->fd);
		xdup2(fd, node->fd);
		xclose(fd);
	}
	else
		return (true);
	return (false);
}

bool	setup_redirects(t_node *node, t_env *env, int read_fd)
{
	while (node)
	{
		if (change_fd(node, get_fd(node, env, read_fd)))
		{
			xperror(node->str);
			return (true);
		}
		node = node->next;
	}
	return (false);
}
