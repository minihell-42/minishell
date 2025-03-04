/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:34:43 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/26 13:44:21 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	if (!lst)
		return (NULL);
	curr = lst;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	*a;
// 	int	*b;
// 	int	*c;

// 	a = malloc(sizeof(int));
// 	b = malloc(sizeof(int));
// 	c = malloc(sizeof(int));
// 	*a = 1;
// 	*b = 2;
// 	*c = 3;
// 	t_list *root = ft_lstnew(a);
// 		// Create a new list with 'a' as the first element
// 	ft_lstadd_back(&root, ft_lstnew(b)); // Add 'b' to the back of the list
// 	ft_lstadd_back(&root, ft_lstnew(c)); // Add 'c' to the back of the list
// 	t_list *last = ft_lstlast(root); // Get the last element of the list
// 	printf("Last element: %d\n", *(int *)last->content); // Should print '3'
//  ft_lstclear(&root, del);
// 	return (0);
// }
