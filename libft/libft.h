/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:01:26 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/28 13:24:55 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "./includes/ft_printf.h"
# include "./includes/stack.h"
# include "./includes/array_utils.h"
# include "./includes/get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

void	*ft_memset(void *b, int c, size_t len);
// fill the pointer up to size n with 0
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
// find first occurance of c and return the pointer or NULL
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// string to int +(-)0123456789
int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

//partie2
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//bonus
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//personal

// return a malloc pointer du duplicated string up to n char
char	*ft_strndup(const char *s1, size_t n);
// return 1 or 0 if a space char is found (\t \n \r \v) included
int		ft_isspace(int c);
// return the same pointer, reverse the string without touching '\0'
char	*ft_strrev(char *str);
// string to long
long	ft_atol(const char *str);
// memory utils

// free stack by poping and free content value inside
void	free_stack(t_stack *stack);
// free memory for two dimension arrays
void	free_array(void **array, size_t size);
void	free_char_array(char **array, size_t size);
void	ft_free_splitted(char **arr);
int		ft_atoi_base(const char *str, int base);
#endif
