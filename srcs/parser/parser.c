/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:15:04 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/01 19:15:29 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    Command to compile:
    cc -I includes srcs/parser/parser.c -L/opt/homebrew/lib -lreadline -o minishell
*/
#include "shell.h"

int    main(void)
{
    char    *input;

    input = readline("minishell$ ");
    if (input == NULL)
        exit(0);
    lexer_tokenize(input);
    free(input);
    return (0);
}