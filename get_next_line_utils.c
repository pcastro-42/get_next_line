#include "get_next_line.h"

void	*ft_memmove(void	*dest, void *src, size_t n)
{
	//TODO turn this into a memmove (it's still memcpy but  already renamed)
	char	*ds;
	char	*sc;
	size_t	i;

	if (!dest || !src)
		return (NULL);
	ds = (char *)dest;
	sc = (char *)src;
	i = 0;
	while (i < n)
	{
		ds[i] = sc[i];
		i++;
	}
	return (dest);
}

t_list	*ft_lstnew(char *buf, size_t len)
{
	t_list	*new;
	char	*content;
	size_t	i;

	content = malloc(sizeof(char) * len);
	if (!content)
		return (NULL);
	i = 0;
	while (i < len)
	{
		content[i] = buf[i];
		i++;
	}
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->len = len;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	free(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*cur;

	if (!lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = cur->next;
		ft_lstdelone(cur);
	}
}
