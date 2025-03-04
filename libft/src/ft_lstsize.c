/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:47:05 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/26 13:44:03 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		count;

	curr = lst;
	count = 0;
	while (curr)
	{
		curr = curr->next;
		count++;
	}
	return (count);
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
// 	root = ft_lstnew(a);
// 	ft_lstadd_back(&root, ft_lstnew(b));
// 	ft_lstadd_back(&root, ft_lstnew(c));
// 	printf("Size of list: %d\n", ft_lstsize(root)); // Should print '3'
// 	ft_lstclear(&root, del);
// 	return (0);
// }
