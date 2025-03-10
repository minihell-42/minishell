#include "../../../includes/execution.h"

void	unset_env_var(char *name, char ***envp)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	len = ft_strlen(name);
	i = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * i + 1);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) != 0 || (*envp)[i][len] != '=')
			new_env[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_free_array(*envp);
	*envp = new_env;
}

void	ft_free_array(char **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}