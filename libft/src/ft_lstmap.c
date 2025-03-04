/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:46:34 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/26 13:51:16 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}

// #include <stdio.h>

// void	*increment(void *content)
// {
// 	int	*new_content;

// 	new_content = malloc(sizeof(int));
// 	*new_content = *(int *)content + 1;
// 	return (new_content);
// }

// int	main(void)
// {
// 	int		*a;
// 	int		*b;
// 	int		*c;
// 	t_list	*root;
// 	t_list	*new_list;

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
// 	new_list = ft_lstmap(root, increment, del);
// 	// Apply 'increment' to each element in the list
// 	// Iterate through the new list and print each element
// 	for (t_list *curr = new_list; curr != NULL; curr = curr->next)
// 	{
// 		printf("%d\n", *(int *)curr->content); // Should print '2', '3', '4'
// 	}
// 	ft_lstclear(&root, del);
// 	ft_lstclear(&new_list, del);
// 	return (0);
// }
