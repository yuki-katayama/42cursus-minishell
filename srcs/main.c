#include "../includes/main.h"
#include "../includes/signal.h"
#include "../includes/utils.h"
#include "../includes/builtin.h"
#include "../includes/lexer.h"
#include "../includes/pipe.h"
#include "../includes/utils.h"
#include "../includes/expansion.h"
#include "../libft/libft.h"

static void	bi_ctrl_d(char *str)
{
	ft_putstr_fd("\033[0A\n", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(0);
}

static t_env *init_env(char **envp)
{
	t_env *head;
	t_env **cur;
	char *str;

	head = NULL;
	cur = &head;
	while (*envp)
	{
		if (!(ft_malloc_p((void **)&*cur, sizeof(t_env))))
			return (NULL);
		str = *envp;
		while (*str && *str != '=')
			++str;
		*str = '\0';
		**cur = (t_env){
			.key = ft_strdup(*envp++),
			.value = ft_strdup(++str)};
		cur = &(*cur)->next;
	}
	return (head);
}

int main(void)
{
	extern char **environ;
	char *argv;
	t_node *node;
	t_env *env;

	env = init_env(environ);
	while (1)
	{
		ft_signal();
		argv = readline("minishell$ ");
		if (argv && ft_strlen(argv) > 0)
			add_history(argv);
		if (argv == NULL)
			bi_ctrl_d("minishell$ exit");
		argv = ft_spaceskip(argv);
		if (*argv != '\0')
		{
			node = nodalize(argv);
			if (node->next != NULL || !(is_msh_bi(*format_command(node->cmd, 0))))
				multi_level_pipe(node, env);
			else if (node && is_msh_bi(*format_command(node->cmd, 0)))
			{
				//ない環境変数が来たらアウト。
				expand_env(&node->cmd, env);
				expand_env(&node->input, env);
				expand_env(&node->output, env);
				marge_token(node);
				run_msh_bi(format_command(node->cmd, 0), env, "adult");
			}
		}
		free(argv);
	}
	return (0);
}