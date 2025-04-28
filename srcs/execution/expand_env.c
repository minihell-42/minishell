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
    if (ft_strcmp(var, "$?") == 0)// Handle $? for exit status - needs to be modified
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
int	contains_env_var(char *str)
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
 * Processes a variable within a string
 *
 * @param vars The variables struct
 * @param str The string to process
 * @param envp The environment variables array
 * @return The new position in the string
 */
int process_variable(t_expand_vars *vars, char *str, char **envp)
{
    char    *temp;
    
    vars->var_end = vars->var_start + 1;
    while (*(vars->var_end) && (ft_isalnum(*(vars->var_end)) || *(vars->var_end) == '_'))
        vars->var_end++;
    if (vars->var_start[1] == '?')
        vars->var_end = vars->var_start + 2;
    vars->var_name = ft_substr(vars->var_start, 0, vars->var_end - vars->var_start);
    vars->var_value = expand_env_var(vars->var_name, envp);
    temp = vars->result;
    vars->result = ft_strjoin(vars->result, vars->var_value);
    free(temp);
    free(vars->var_name);
    free(vars->var_value);
    return (vars->var_end - str);
}

/**
 * Appends text before a variable
 *
 * @param vars The variables struct
 * @param str The string to process
 * @param i The current position in the string
 */
void append_prefix(t_expand_vars *vars, char *str, int i)
{
    int     j;
    char    *temp;
    char    *prefix;
    
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
void append_remainder(t_expand_vars *vars, char *str, int i)
{
    char    *temp;
    
    temp = vars->result;
    vars->result = ft_strjoin(vars->result, str + i);
    free(temp);
}

/**
 * Expands environment variables within a string.
 *
 * @param str The string to process.
 * @param envp The environment variables array.
 *
 * @returns A newly allocated string with the expanded variables, or a copy of
 *          the original string if no variables are found.
 */
char *expand_vars_in_string(char *str, char **envp)
{
    t_expand_vars vars;
    int           i;

    if (!str)
        return (NULL);
    if (str[0] == '$' && !ft_strchr(str + 1, '$'))
        return (expand_env_var(str, envp));
    vars.result = ft_strdup("");
    i = 0;  
    while (str[i])
    {
        vars.var_start = ft_strchr(str + i, '$');     
        if (!vars.var_start)
        {
            append_remainder(&vars, str, i);
            break;
        }   
        append_prefix(&vars, str, i);
        i = process_variable(&vars, str, envp);
    }
    return (vars.result);
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