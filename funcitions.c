#include "minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	ib;
	size_t	il;

	ib = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[ib] != '\0' && ib < len)
	{
		il = 0;
		while (big[ib] == little[il] && big[ib] != '\0' && ib < len)
		{
			il++;
			ib++;
		}
		if (little[il] == '\0')
			return ((char *)&big[ib] - il);
		ib = ib - il;
		ib++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	r1;
	size_t	r2;
	size_t	t;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	r1 = ft_strlen (s1);
	r2 = ft_strlen (s2);
	t = r1 + r2;
	ptr = malloc((t + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memmove(ptr, s1, r1);
	ft_memmove(&ptr[r1], s2, r2);
	ptr[t] = '\0';
	return (ptr);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = dest;
	s = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		i = n;
		while (n > 0)
		{
			i--;
			n--;
			d[i] = s[i];
		}
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		++i;
	}
		if (c == '\0')
			return ((char *)&s[i]);
	return (NULL);
}
