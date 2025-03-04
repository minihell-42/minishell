/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:45 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/30 09:56:48 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*curr;

// 	// if the first node is NULL we need to assign it to the new node.
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	// dereference pointer to pointer to first node of the list.
// 	curr = *lst;
// 	// Exit condition: until the next node is Null aka until member
//*next is NULL.
// 	while (curr->next != NULL)
// 	{
// 		// increment for lists: To go to the next node the pointer "next"
// points to the successive node.
// 		curr = curr->next;
// 	}
// 	// after exiting the loop at this point,
// 	// the last node of the list is curr->next.
// 	// Once we reach the last node of the list (curr->next != NULL)
// we assign it to the new node
// 	curr->next = new;
// }

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		a;
// 	int		b;
// 	int		c;
// 	t_list	*root;

// 	a = 15;
// 	b = -2;
// 	c = 11;
// 	root = ft_lstnew(&a);
// 	ft_lstadd_back(&root, ft_lstnew(&b));
// 	ft_lstadd_back(&root, ft_lstnew(&c));
// 	for (t_list *curr = root; curr != NULL; curr = curr->next)
// 	{
// 		printf("%d\n", *(int *)curr->content);
// 	}
// 	ft_lstclear(&root, del);
// 	return (0);
// }
