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

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
		{
			if (p1[i] > p2[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}


void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_isalpha(int i)
{
	if ((i >= 65 && i <= 90) || (i >= 97 && i <= 122))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int i)
{
	if ((i >= 48 && i <= 57) || (i >= 65 && i <= 90) || (i >= 97 && i <= 122))
		return (1);
	else
		return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;
	size_t		i;

	cdest = (char *)dest;
	csrc = (const char *)src;
	if (cdest == NULL && csrc == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (cdest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc (1 * sizeof(t_list));
	if (!new)
		return (NULL);
	new -> content = content;
	new -> next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}