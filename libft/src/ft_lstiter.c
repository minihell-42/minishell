/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:46:20 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/30 09:57:09 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	increment(void *content)
{
	*(int *)content += 1;
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		*a;
// 	int		*b;
// 	int		*c;
// 	t_list	*root;

// 	a = malloc(sizeof(int));
// 	b = malloc(sizeof(int));
// 	c = malloc(sizeof(int));
// 	*a = 1;
// 	*b = 2;
// 	*c = 3;
// 	root = ft_lstnew(a);
// 	// Create a new list with 'a' as the first element
// 	ft_lstadd_back(&root, ft_lstnew(b)); // Add 'b' to the back of the list
// 	ft_lstadd_back(&root, ft_lstnew(c)); // Add 'c' to the back of the list
// 	// Iterate through the list and print each element
// 	for (t_list *curr = root; curr != NULL; curr = curr->next)
// 	{
// 		printf("%d\n", *(int *)curr->content);
// 	}
// 	ft_lstiter(root, increment);
// 	// Apply 'increment' to each element in the list
// 	// Iterate through the list again and print each element
// 	for (t_list *curr = root; curr != NULL; curr = curr->next)
// 	{
// 		printf("%d\n", *(int *)curr->content);
// 	}
// 	ft_lstclear(&root, del);
// 	return (0);
// }
