/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:53:17 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/12 11:53:22 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Determines if a given token is a redirection token.
 *
 * @param type The type of the token.
 *
 * @returns 1 if the token is a redirection token, 0 otherwise.
 */
int	is_redir(int type)
{
	return (type == TKN_REDIR_IN || type == TKN_REDIR_OUT
		|| type == TKN_REDIR_APPEND || type == TKN_HERE_DOC);
}

/**
 * Determines if a given token is a filename token.
 *
 * @param type The type of the token.
 *
 * @returns 1 if the token is a filename token, 0 otherwise.
 */
int	is_filename_token(int type)
{
	if (type == TKN_CMD || type == TKN_ARG)
		return (1);
	return (0);
}
