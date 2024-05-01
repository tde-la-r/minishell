/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:39:06 by amolbert          #+#    #+#             */
/*   Updated: 2024/05/01 19:48:40 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_lst
{
	int				content;
	struct s_lst	*next;
}	t_lst;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstpenultimate(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_lst	*ft_lstnew_int(int content);
t_lst	*ft_lstlast_int(t_lst *lst);
t_lst	*ft_lstpenultimate_int(t_lst *lst);
t_lst	*ft_lstmap_int(t_lst *lst);

char	*ft_strchr(const char *s, int c);
char	*ft_strchr_next(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*get_next_line(int fd);

int		ft_isalpha(int c);
int		ft_islower(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isbase(char c, int base_len);
int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, int base);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_lstsize(t_list *lst);
int		ft_lstsize_int(t_lst *lst);
int		ft_putnbr(int n);
int		ft_putnbrus(unsigned int n);
int		ft_lennum(int n);
int		ft_lennumus(unsigned int n);
int		ft_lennumhexa(unsigned int n);
int		ft_lennumhexaull(unsigned long long n);
int		ft_putchar(int n);
int		ft_putstr(char *s);
int		ft_dectohexa(unsigned int n, char *index);
int		ft_pointtohexa(unsigned long long n, char *index, int start);
int		ft_printf(const char *s, ...);
int		ft_fprintf(int fd, const char *s, ...);
int		ft_abs(int n);
int		ft_superior(int a, int b);
int		ft_lower(int a, int b);

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_count_words(char const *s, char c);

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_front_int(t_lst **lst, t_lst *new);
void	ft_lstadd_back_int(t_lst **lst, t_lst *new);
void	ft_lstdelone_int(t_lst *lst);
void	ft_lstclear_int(t_lst **lst);
void	ft_lstiter_int(t_lst *lst, void (*f)(int));

#endif
