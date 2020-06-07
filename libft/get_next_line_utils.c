/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:07:28 by cbertola          #+#    #+#             */
/*   Updated: 2019/12/14 17:53:52 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_malloc(char *s1, char *s2)
{
	char		*ptr;
	long int	u;
	long int	v;

	u = 0;
	v = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!(ptr = malloc((ft_strlen(s1) + ft_strlen(s2)) * (sizeof(char) + 1))))
		return (NULL);
	while (s1[u])
	{
		ptr[u] = s1[u];
		u++;
	}
	while (s2[v])
		ptr[u++] = s2[v++];
	free(s1);
	free(s2);
	ptr[u] = '\0';
	return (ptr);
}

char		*ft_before_char(char *str, char stop)
{
	int i;

	i = 0;
	while (str[i] != stop)
		i++;
	str[i] = '\0';
	return (str);
}

char		*ft_send(t_list_gnl **lst, char **line)
{
	char	*str;
	char	*new;
	int		i;
	int		j;

	i = ft_find((*lst)->str, '\n');
	if (!(str = malloc(i * sizeof(char))))
		return (NULL);
	if (!(new = malloc((ft_strlen((*lst)->str) - i) * sizeof(char) + 1)))
		return (NULL);
	j = 0;
	while (j != i)
	{
		str[j] = (*lst)->str[j];
		j++;
	}
	str[--j] = '\0';
	j = 0;
	while ((*lst)->str[i] != '\0')
		new[j++] = (*lst)->str[i++];
	new[j] = '\0';
	*line = str;
	free((*lst)->str);
	return (new);
}

int			ft_find(char *str, char stop)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i++] == stop)
			return (i);
	}
	return (0);
}
