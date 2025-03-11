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

// TODO: Gives back the type of the command
t_cmd_type	is_builtin(char *cmd);

// TODO: Checks for syntax errors before parsing (e.x | |, > <, etc)
int			validate_syntax(t_token *tokens);
