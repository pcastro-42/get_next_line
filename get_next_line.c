#include "get_next_line.h"

static size_t	get_eol(t_list *lst)
{
	size_t	i;
	size_t	len;
	t_list	*last;
	char	*content;

	if (!lst)
		return (0);
	last = ft_lstlast(lst);
	content = last->content;
	len = last->len;
	i = 0;
	while (i < len)
	{
		if (content[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

ssize_t	read_store(int fd, char *buf, t_list **lst)
{
	ssize_t	len;
	size_t	len_before_eol;
	t_list	*last;

	len = read(fd, buf, BUFFER_SIZE);
	if (len <= 0)
		return (len);
	if (!(*lst))
		*lst = ft_lstnew(buf, (size_t)len);
	last = *lst;
	while (!get_eol(last))
	{
		total_len += len;
		len = read(fd, buf, BUFFER_SIZE); //TODO  l with len 0, -1 error and mallocing error
		if (len < 0)
			return (len);
		if (len == 0)
			return (len_before_eol)
		last->next = ft_lstnew(buf, (size_t)len);
	       	last = last->next;
	}
	return (len_before_eol + get_eol(last));
}

char	*assemble(t_list *lst, size_t total_len)
{
	char	*line;
	char	*ptr; 
	size_t	last_len;
	t_list	*last;

	if (!lst)
		return (NULL);
	last = ft_lstlast(lst);
	last_len = get_eol(last);
	if (last_len == 0)
		last_len = last->len;
	line = malloc(sizeof(char) * (total_len + 1));
	if (!line)
		return (NULL);
	ptr = line;
	while (lst->next)
	{
		ptr = (char *)ft_memmove(ptr, lst->content, lst->len); //memmove/cpy does not allocate memory, memory's already been allocated, you're chill.
		ptr += lst->len;						//hell i find it ridiculous how memcpy returns a pointe like wtf you mean :cry: i guess its good for error detection or smth
		lst = lst->next;
	}
	while (i < last_len)
		ptr = (char *)ft_memmove(ptr, lst->content, last_len);
	ptr += last_len;
	ptr[] = '\0';
	return (line);
}

int	clean(char *buf, t_list **lst, int crashed)
{
	t_list	*new_lst;
	t_list	*last;
	size_t	last_len;

	free(buf);
	if (crashed)
	{
		ft_lstclear(*lst);
		return (0);
	}
	last = lst_last(*lst);
	last_len = get_eol(last);
	if (last_len == 0)
	{
		ft_lstclear(*lst);
		return (0);
	}
	new_lst = ft_lstnew(last->content + last_len, last->len - last_len);
	if (!new_lst)
		return (-1);
	ft_lstclear(*lst);
	*lst = new_lst;
	return (0);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buf;
	static t_list	*lst;
	ssize_t	total_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	if (get_eol(lst))
		line = assemble(&lst, get_eol(lst));
	else
	{
		total_len = read_store(fd, buf, lst);
		if (total_len <= 0) //if total len is 0, you can act as if it crashes (bc it just clears everything and returns null lol, whcih is the intended behavior for when the file ends)
			return ((void *)clean(buf, &lst, 1));
		line = assemble(&lst, total_len);
		if (!line)
			return ((void *)clean(buf, &lst, 1));
		if(clean(buf, &lst, 0) == -1)
			return (NULL)
	}
	return (line);
}

