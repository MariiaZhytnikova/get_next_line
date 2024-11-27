#include "get_next_line.h"
#include <stdint.h>

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	str = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (s1_len-- > 0)
		*str++ = *s1;
		while (s1_len-- > 0)
		*str++ = *s2++;
	str[s1_len + s2_len] = '\0';
	return (str);
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t	byte_size;
	size_t	i;
	unsigned char *object;

	if (size != 0 && num > (SIZE_MAX / size))
		return (NULL);
	byte_size = num * size;
	object = malloc(byte_size);
	if (!object)
		return (NULL);
	i = 0;
	while (i < byte_size)
	{
		object[i] = 0;
		i++;
	}
	return (object);
}
