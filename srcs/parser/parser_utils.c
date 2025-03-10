/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:00:28 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/10 11:00:30 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*parse_tokens(t_token *tokens);
t_tree	*parse_command(t_token **tokens);
t_tree	*parse_redirection(t_token **tokens);
t_tree	*parse_pipeline(t_token **tokens);
t_tree	*parse_sequence(t_token **tokens);
