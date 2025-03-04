/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:41:12 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/30 09:57:56 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_words(char const *s, char c);
void	free_buffer(char **buffer, int count);
char	**allocate_memory(char const *s, char c, int word_count);
int		write_buffer(char **buffer, char const *s, char c, int word_count);

char	**ft_split(char const *s, char c)
{
	char	**buffer;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	if (word_count == -1)
		return (NULL);
	buffer = allocate_memory(s, c, word_count);
	return (buffer);
}

int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**allocate_memory(char const *s, char c, int word_count)
{
	char	**buffer;

	buffer = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!buffer)
		return (NULL);
	if (!write_buffer(buffer, s, c, word_count))
	{
		free_buffer(buffer, word_count);
		return (NULL);
	}
	return (buffer);
}

int	write_buffer(char **buffer, char const *s, char c, int word_count)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	while (i < word_count)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		buffer[i] = ft_substr(s, start, end - start);
		if (!buffer[i])
			return (0);
		start = end;
		i++;
	}
	buffer[i] = NULL;
	return (1);
}

void	free_buffer(char **buffer, int count)
{
	while (count >= 0)
	{
		free(buffer[count]);
		count--;
	}
	free(buffer);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char const	*s;
// 	char		c;
// 	char		**res;
// 	int			i;

// 	s = "lorem ipsum dolor sit amet,consectetur";
// 	c = ' ';
// 	i = 0;
// 	res = ft_split(s, c);
// 	while (res[i])
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// 	return (0);
// }
