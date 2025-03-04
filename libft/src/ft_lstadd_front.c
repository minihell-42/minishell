/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:45:25 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/24 18:37:59 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	// if the first node is NULL we need to assign it to the new node.
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		new->next = NULL;
// 		return ;
// 	}
// 	if (new == NULL)
// 		return ;
// 	// To add a node at the beginning, we get the first node
// 	// we replace the first node with the new one;// and then
// link the previous root to this newly created first node.
// 	new->next = *lst;
// 	*lst = new;
// }

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		a;
// 	int		b;
// 	int		c;
// 	t_list	*root;

// 	a = 1;
// 	b = 2;
// 	c = 3;
// 	root = ft_lstnew(&a);
// 	ft_lstadd_front(&root, ft_lstnew(&b));
// 	ft_lstadd_front(&root, ft_lstnew(&c));
// 	for (t_list *curr = root; curr != NULL; curr = curr->next)
// 	{
// 		printf("%d\n", *(int *)curr->content);
// 	}
// 	ft_lstclear(&root, del);
// 	return (0);
// }
