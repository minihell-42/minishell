/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:45:53 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/26 13:35:40 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *content)
{
	free(content);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int *a = malloc(sizeof(int));
// 	int *b = malloc(sizeof(int));
// 	int *c = malloc(sizeof(int));

// 	*a = 1;
// 	*b = 2;
// 	*c = 3;

// 	t_list *root = ft_lstnew(a);
// 		// Create a new list with 'a' as the first element

// 	ft_lstadd_back(&root, ft_lstnew(b)); // Add 'b' to the back of the list
// 	ft_lstadd_back(&root, ft_lstnew(c)); // Add 'c' to the back of the list

// 	// Iterate through the list and print each element
// 	for (t_list *curr = root; curr != NULL; curr = curr->next)
// 	{
// 		printf("%d\n", *(int *)curr->content);
// 	}

// 	ft_lstdelone(root->next, del); // Delete the second element in the list

// 	// Iterate through the list again and print each element
// 	for (t_list *curr = root; curr != NULL; curr = curr->next)
// 	{
// 		printf("%d\n", *(int *)curr->content);
// 	}

// 	return (0);
// }