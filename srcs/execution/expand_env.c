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
    int         i;
    t_expand_vars vars;

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
 * Expands environment variables in command arguments
 *
 * @param tree The command tree to process
 * @param envp The environment variables array
 */
void expand_cmd_args(t_tree *tree, char **envp)
{
    int     i;
    char    *expanded;
    
    i = 0;
    while (i < tree->argc)
    {
        if (tree->argv[i] && 
            (!tree->arg_quotes || tree->arg_quotes[i] != QUOTE_SINGLE) && 
            contains_env_var(tree->argv[i]))
        {
            expanded = expand_vars_in_string(tree->argv[i], envp);
            free(tree->argv[i]);
            tree->argv[i] = expanded;
        }
        i++;
    }
}
 
 /**
  * Expands environment variables in redirection files
  *
  * @param tree The command tree to process
  * @param envp The environment variables array
  */
 void expand_redir_files(t_tree *tree, char **envp)
 {
     char    *expanded;
     
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
 
 /**
  * Recursively expands all environment variables in a command tree.
  *
  * @param tree The command tree to process.
  * @param envp The environment variables array.
  */
 void expand_env_vars_in_tree(t_tree *tree, char **envp)
 {
     if (!tree || !envp)
         return;
     if (tree->type == NODE_CMD && tree->argv)
         expand_cmd_args(tree, envp);
     if (tree->type == NODE_REDIR)
         expand_redir_files(tree, envp);
     if (tree->left)
         expand_env_vars_in_tree(tree->left, envp);
     if (tree->right)
         expand_env_vars_in_tree(tree->right, envp);
 }