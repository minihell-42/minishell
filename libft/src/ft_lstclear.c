/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:16:09 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/26 13:46:38 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	while (*lst)
	{
		curr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = curr;
	}
	free(*lst);
	*lst = NULL;
}

// #include <stdio.h>

// void	del(void *content)
// {
// 	free(content);
// }

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

// 	ft_lstclear(&root, del); // Clear the list

// 	if (root == NULL)
// 	{
// 		printf("List cleared successfully\n");
// 	}

// 	return (0);
// }