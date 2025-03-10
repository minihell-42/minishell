#include "../../../includes/execution.h"

/*
 * Allocates new memory of size 'new_size' and copies the content
 * from 'ptr' to the new memory. Then frees the old memory.
 *
 * If ptr is NULL, behaves like malloc.
 * If new_size is 0 and ptr is not NULL, behaves like free and returns NULL.
 *
 * Returns: Pointer to the newly allocated memory, or NULL if allocation fails.
 */
void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
