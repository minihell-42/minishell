#include "../../../includes/execution.h"

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	update_pwd(char *old_pwd, char ***envp)
{
	char	cwd[PATH_MAX];
	char	*pwd_var;
	char	*oldpwd_var;

	if (getcwd(cwd, PATH_MAX))
	{
		pwd_var = ft_strjoin("PWD=", cwd);
		oldpwd_var = ft_strjoin("OLDPWD=", old_pwd);
		if (pwd_var && oldpwd_var)
		{
			set_env_var(pwd_var, envp);
			set_env_var(oldpwd_var, envp);
			free(pwd_var);
			free(oldpwd_var);
		}
	}
}

static int	update_existing_var(char *var_string, char *name, char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], name, ft_strlen(name))
			&& (*envp)[i][ft_strlen(name)] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(var_string);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_new_var(char *var_string, int count, char ***envp)
{
	char	**new_env;

	new_env = ft_realloc(*envp, sizeof(char *) * (count + 2));
	if (!new_env)
		return (0);
	new_env[count] = ft_strdup(var_string);
	new_env[count + 1] = NULL;
	*envp = new_env;
	return (1);
}

int	set_env_var(char *var_string, char ***envp)
{
	int		i;
	char	*name;
	char	*equals_pos;

	equals_pos = ft_strchr(var_string, '=');
	if (!equals_pos)
		return (0);
	name = ft_substr(var_string, 0, equals_pos - var_string);
	if (!name)
		return (1);
	if (update_existing_var(var_string, name, envp))
	{
		free(name);
		return (0);
	}
	i = 0;
	while ((*envp)[i])
		i++;
	if (!add_new_var(var_string, i, envp))
	{
		free(name);
		return (1);
	}
	free(name);
	return (0);
}
