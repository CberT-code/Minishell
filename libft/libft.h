/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrillebertola <cyrillebertola@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:59:00 by cbertola          #+#    #+#             */
/*   Updated: 2020/03/24 15:21:19 by cyrillebert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "ft_printf.h"

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct			s_list_gnl
{
	int					fd;
	char				*buff;
	char				*str;
	int					read;
	struct s_list_gnl	*next;
}						t_list_gnl;

char					**ft_splitnum(char *s, int c);
char					*ft_strsubstr(char *s1, char *sub);
char					*ft_strsubstr_free(char *s1, char *sub);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strdup(const char *s1);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin_free(char *s1, char *s2, int k);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_substr(char const *s, unsigned int start,
						size_t len);
char					**ft_split(char const *s, char c);
char					*ft_itoa(int n);
char					*ft_send(t_list_gnl **lst, char **line);
char					*ft_before_char(char *str, char stop);
char					*ft_strjoin_malloc(char *s1, char *s2);
char					*ft_strmapi(char const *s,
						char (*f)(unsigned int, char));
char					*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_how_many(char *str, char *tab);
int						ft_strlen(const char *s);
int						ft_strlen_no_ws(char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_atoi_pos(const char *str);
int						ft_isfind(char *str, char stop);
int						get_next_line(int fd, char **line);
int						ft_exist(t_list_gnl **lst_one, char **line);
int						search_fd(t_list_gnl **lst_one, int fd);
int						ft_find(char *str, char stop);
int						ft_start_str(char *str1, char *str2);
int						ft_count_char_int(long int nb, int base);
int						is_tab_full(char *tab, char c);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
void					*ft_bzero(void *s, size_t n);
void					*ft_memset(void *b, int c, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
						size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_calloc(size_t count, size_t size);
void					ft_putchar_fd(char c, int fd);
int						ft_putchar_int(char c);
void					ft_putchar(char c);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char *s);
void					ft_putendl(char *s);
void					ft_putnbr(int n);
void					ft_del(t_list_gnl **lst_one);
void					ft_new_lst(int fd, t_list_gnl **lst_one);

#endif
