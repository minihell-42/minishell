#include "../../../includes/execution.h"

int	builtin_exit(int argc, char **argv)
{
	int status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (argc == 1)
		exit(0);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	status = ft_atoi(argv[1]);
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit(status % 256);
	return (0);
}