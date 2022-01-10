/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:30:50 by nyokota           #+#    #+#             */
/*   Updated: 2022/01/10 20:16:38 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include <stdbool.h>

typedef struct s_node		t_node;
typedef struct s_executor	t_executor;
typedef struct s_env		t_env;

enum e_pipe
{
	READ,
	WRITE,
	PIPE
};

struct s_executor
{
	t_node		*redirect;
	t_node		*command;
	t_executor	*next;
};

void	executor_clear(t_executor *head);
char	**format_command(t_node *node);
char	*format_path(char *cmd, char **path);
bool	here_docs(t_executor *executor, t_env *env);
bool	setup_redirects(t_node *node/*, t_env *env, int read_fd*/);
void	restore_fd(t_node *node);
void	exec_command(t_executor *executor, t_env **env);

#endif