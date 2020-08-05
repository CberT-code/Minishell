/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:07:55 by mifernan          #+#    #+#             */
/*   Updated: 2020/08/05 14:08:44 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFFER_SIZE 4096

char	*ft_reader(int fd, char *rest, char buf[]);
char	*ft_line(char **str);
int		get_next_line(const int fd, char **line);

#endif