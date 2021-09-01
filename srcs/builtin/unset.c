#include "../../includes/pipe.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"

int bi_unset(char **key, t_env *env)
{
	int i;
	t_env *mem;

	while(++key && *key)
		env = msh_del_env(*key, env);
	mem = env;
	while (mem)
	{
		printf("%s : %s\n", mem->key, mem->value);
		mem = mem->next;
	}
	return (0);
}