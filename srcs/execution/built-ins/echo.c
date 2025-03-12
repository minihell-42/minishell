#include "../../../includes/execution.h"

int	builtin_echo(int argc, char **argv)
{
	int i;
	int n_flag;

	i = 1;
	n_flag = 0;
	if (argc > 1 && !ft_strncmp(argv[1], "-n", 3))
	{
		n_flag = 1;
		i = 2;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}