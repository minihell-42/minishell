#include "../../../includes/execution.h"

int	builtin_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
