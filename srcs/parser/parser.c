/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:15:04 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/04 13:03:46 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Command to compile:
cc -I includes srcs/parser/parser.c -L/opt/homebrew/lib -lreadline -o minishell
*/
#include "parser.h"

t_tree	*parse_tokens(t_token *tokens);
t_tree	*parse_command(t_token **tokens);
t_tree	*parse_redirection(t_token **tokens);
t_tree	*parse_pipeline(t_token **tokens);
t_tree	*parse_sequence(t_token **tokens);
