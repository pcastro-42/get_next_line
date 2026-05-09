#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef	struct	s_list
{
	char	*content;
	struct s_list	*next;
	int	len;
}	t_list;

char	*get_next_line(int fd);
t_list	*ft_lstnew(char *buf, size_t len);
void	ft_lstdelone(t_lst *lst);
void	ft_lstclear(t_list **lst);
void	*ft_memcpy(void *des, void *src, size_t n);
#endif
