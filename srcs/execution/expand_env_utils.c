/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:47:36 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/04/29 17:52:18 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Checks if a string contains environment variables that need expansion.
 *
 * @param str The string to check.
 *
 * @returns 1 if the string contains environment variables, 0 otherwise.
 */
int	contains_env_var(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
			return (1);
		i++;
	}
	return (0);
}

int	is_pure_variable(const char *str)
{
	const char	*var_end;

	if (!str || *str != '$')
		return (0);
	var_end = str + 1;
	if (*var_end == '?')
		var_end++;
	else
		while (*var_end && (ft_isalnum((int)*var_end) || *var_end == '_'))
			var_end++;
	return (*var_end == '\0');
}

/**
 * Appends text before a variable
 *
 * @param vars The variables struct
 * @param str The string to process
 * @param i The current position in the string
 */
void	append_prefix(t_expand_vars *vars, char *str, int i)
{
	int		j;
	char	*temp;
	char	*prefix;

	j = vars->var_start - (str + i);
	if (j > 0)
	{
		prefix = ft_substr(str + i, 0, j);
		temp = vars->result;
		vars->result = ft_strjoin(vars->result, prefix);
		free(temp);
		free(prefix);
	}
}

/**
 * Appends remaining text after all variables
 *
 * @param vars The variables struct
 * @param str The string to process
 * @param i The current position in the string
 */
void	append_remainder(t_expand_vars *vars, char *str, int i)
{
	char	*temp;

	temp = vars->result;
	vars->result = ft_strjoin(vars->result, str + i);
	free(temp);
}

/**
 * Processes a variable within a string
 *
 * @param vars The variables struct
 * @param str The string to process
 * @param envp The environment variables array
 * @return The new position in the string
 */
int	process_variable(t_expand_vars *vars, char *str, char **envp)
{
	char	*temp;

	vars->var_end = vars->var_start + 1;
	while (*(vars->var_end) && (ft_isalnum(*(vars->var_end))
			|| *(vars->var_end) == '_'))
		vars->var_end++;
	if (vars->var_start[1] == '?')
		vars->var_end = vars->var_start + 2;
	vars->var_name = ft_substr(vars->var_start, 0,
			vars->var_end - vars->var_start);
	vars->var_value = expand_env_var(vars->var_name, envp);
	temp = vars->result;
	vars->result = ft_strjoin(vars->result, vars->var_value);
	free(temp);
	free(vars->var_name);
	free(vars->var_value);
	return (vars->var_end - str);
}
