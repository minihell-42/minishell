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
             if (tree->argv[i] && tree->argv[i][0] == '$')
             {
                 expanded = expand_env_var(tree->argv[i], envp);
                 free(tree->argv[i]);
                 tree->argv[i] = expanded;
             }
             i++;
         }
     }
     if (tree->type == NODE_REDIR)
     {
         if (tree->input_file && tree->input_file[0] == '$')
         {
             expanded = expand_env_var(tree->input_file, envp);
             free(tree->input_file);
             tree->input_file = expanded;
         }
         if (tree->output_file && tree->output_file[0] == '$')
         {
             expanded = expand_env_var(tree->output_file, envp);
             free(tree->output_file);
             tree->output_file = expanded;
         }
     }
     if (tree->left)
         expand_env_vars_in_tree(tree->left, envp);
     if (tree->right)
         expand_env_vars_in_tree(tree->right, envp);
 }