#include "execution.h"

/**
 * Expands an environment variable to its value.
 *
 * @param var The environment variable string (including the $ prefix).
 * @param envp The environment variables array.
 *
 * @returns A newly allocated string with the expanded value, or a copy of
 *          the original string if the variable is not found.
 */
char	*expand_env_var(char *var, char **envp)
{
    char	*var_name;
    char	*var_value;
    int		i;

    if (!var || !envp)
        return (ft_strdup(""));
    if (var[0] != '$')
        return (ft_strdup(var));
    // Handle $? for exit status - needs to be modified
    if (ft_strcmp(var, "$?") == 0)
        return (ft_strdup("0"));
    var_name = var + 1;
    if (!*var_name)
        return (ft_strdup("$"));
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0 
            && envp[i][ft_strlen(var_name)] == '=')
        {
            var_value = envp[i] + ft_strlen(var_name) + 1;
            return (ft_strdup(var_value));
        }
        i++;
    }
    return (ft_strdup(""));
}

/**
 * Checks if a string contains environment variables that need expansion.
 *
 * @param str The string to check.
 *
 * @returns 1 if the string contains environment variables, 0 otherwise.
 */
static int	contains_env_var(char *str)
{
    int i;
    
    if (!str)
        return (0);
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && 
            (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
            return (1);
        i++;
    }
    return (0);
}

/**
 * Expands environment variables within a string.
 * 
 * @param str The string that may contain environment variables.
 * @param envp The environment variables array.
 * 
 * @returns A newly allocated string with variables expanded.
 */
static char *expand_vars_in_string(char *str, char **envp)
{
    char *result;
    char *var_start;
    char *var_end;
    char *var_name;
    char *var_value;
    char *temp;
    int i, j;
    
    if (!str)
        return (NULL);
    
    // If it's just a variable, use the existing function
    if (str[0] == '$' && !ft_strchr(str + 1, '$'))
        return (expand_env_var(str, envp));
    
    // Otherwise, we need to handle embedded variables
    result = ft_strdup("");
    i = 0;
    
    while (str[i])
    {
        // Find the next $ sign
        var_start = ft_strchr(str + i, '$');
        
        // If no more $ signs, append the rest of the string and break
        if (!var_start)
        {
            temp = result;
            result = ft_strjoin(result, str + i);
            free(temp);
            break;
        }
        
        // Append everything up to the $ sign
        j = var_start - (str + i);
        if (j > 0)
        {
            char *prefix = ft_substr(str + i, 0, j);
            temp = result;
            result = ft_strjoin(result, prefix);
            free(temp);
            free(prefix);
        }
        
        // Find the end of the variable name
        var_end = var_start + 1;
        while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
            var_end++;
        
        // Special case for $?
        if (var_start[1] == '?')
            var_end = var_start + 2;
        
        // Extract the variable name
        var_name = ft_substr(var_start, 0, var_end - var_start);
        
        // Get the variable value
        var_value = expand_env_var(var_name, envp);
        
        // Append the variable value to the result
        temp = result;
        result = ft_strjoin(result, var_value);
        free(temp);
        
        // Free temporary strings
        free(var_name);
        free(var_value);
        
        // Move past the variable
        i = var_end - str;
    }
    
    return (result);
}

/**
 * Recursively expands all environment variables in a command tree.
 *
 * @param tree The command tree to process.
 * @param envp The environment variables array.
 */
void	expand_env_vars_in_tree(t_tree *tree, char **envp)
{
    int		i;
    char	*expanded;

    if (!tree || !envp)
        return ;
    
    if (tree->type == NODE_CMD && tree->argv)
    {
        i = 0;
        while (i < tree->argc)
        {
            if (tree->argv[i])
            {
                if (tree->arg_quotes && tree->arg_quotes[i] == QUOTE_SINGLE)
                {
                    // do nothing
                }
                else if (contains_env_var(tree->argv[i]))
                {
                    expanded = expand_vars_in_string(tree->argv[i], envp);
                    free(tree->argv[i]);
                    tree->argv[i] = expanded;
                }
            }
            i++;
        }
    }
    if (tree->type == NODE_REDIR)
    {
        if (tree->input_file && tree->input_quote != QUOTE_SINGLE && 
            contains_env_var(tree->input_file))
        {
            expanded = expand_vars_in_string(tree->input_file, envp);
            free(tree->input_file);
            tree->input_file = expanded;
        }
        if (tree->output_file && tree->output_quote != QUOTE_SINGLE && 
            contains_env_var(tree->output_file))
        {
            expanded = expand_vars_in_string(tree->output_file, envp);
            free(tree->output_file);
            tree->output_file = expanded;
        }
    }
    if (tree->left)
        expand_env_vars_in_tree(tree->left, envp);
    if (tree->right)
        expand_env_vars_in_tree(tree->right, envp);
}