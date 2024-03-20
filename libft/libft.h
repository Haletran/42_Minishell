/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:40:33 by bapasqui          #+#    #+#             */
/*   Updated: 2024/03/20 11:40:16 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../includes/struct.h"
# include <stdlib.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *str, int to_find);
int		ft_atoi(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memset(void *pointer, int value, size_t count);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
void	*ft_memchr(const void *mem, int srh, size_t size);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_strncmp(const char *first, const char *second, size_t lenght);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_calloc(size_t elementCount, size_t elementSize);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strrchr(const char *s, int c);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
void	*ft_lstnew(int content);
char	*get_next_line(int fd);
char	*ft_strcpy(char *dest, char *src);
void	*ft_lstadd_back(t_com *lst, int value);
void	ft_lst_add_front(t_com **a, t_com *new);
int		ft_lst_size(t_com *a);
void	*ft_lst_new(int content, int index);
int		ft_strcmp(char *s1, char *s2);

#endif
