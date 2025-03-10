/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:00:02 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/10 11:00:06 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*create_ast_node(t_node_type type, char *value);
void	print_ast(t_tree *root, int depth);
void	free_ast(t_tree *root);
