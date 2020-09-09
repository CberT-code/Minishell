/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:47:44 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 11:10:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./libft.h"

# define BUFFER_SIZE 200

typedef struct	s_gnl
{
	int				fd;
	char			*buff;
	char			*str;
	int				read;
	struct s_gnl	*next;
}				t_gnl;

int				get_next_line(int fd, char **line);
void			ft_del(t_gnl **lst_one);
int				ft_exist(t_gnl **lst_one, char **line);
int				search_fd(t_gnl **lst_one, int fd);
int				ft_find(char *str, char stop);
char			*ft_send(t_gnl **lst, char **line);
char			*ft_before_char(char *str, char stop);
void			ft_new_lst(int fd, t_gnl **lst_one);
char			*ft_strjoin_gnl(char *s1, char *s2);

#endif
