#include "shell.h"

int	check_unmatched_quotes(char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*input == '\"' && single_quote == 0)
			double_quote = !double_quote;
		input++;
	}
	if (single_quote || double_quote)
		return (1);
	return (0);
}

int	main(void)
{
	char	*input;
	char	*new_input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		while (check_unmatched_quotes(input))
		{
			new_input = readline("quote> ");
			if (new_input == NULL)
			{
				free(input);
				exit(0);
			}
			input = ft_strjoin(input, new_input);
			free(new_input);
		}
		tokens = lexer_tokenizer(input);
		print_tokens(tokens);
		// parse_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}