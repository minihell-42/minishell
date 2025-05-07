#include "../../../includes/execution.h"

void	print_dir_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

// TODO: make shorter than 25 lines
int	builtin_cd(int argc, char **argv, char ***envp)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = getcwd(cwd, PATH_MAX);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (argc == 1)
	{
		path = ft_getenv("HOME", *envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		print_dir_error(path);
		return (1);
	}
	if (old_pwd)
		update_pwd(old_pwd, envp);
	return (0);
}
