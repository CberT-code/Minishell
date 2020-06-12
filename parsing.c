<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 09:55:46 by user42            #+#    #+#             */
/*   Updated: 2020/06/12 10:01:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (new != NULL)
	{
		if (*alst != NULL)
			ft_lstlast(*alst)->next = new;
		else
			*alst = new;
	}
}

int main(int argc, char **argv)
{
    (void)argc;

    return (0);
=======
#include "minishell.h"

t_cmds     *split_pipes(char *str)
{
    t_cmds  *list;
    t_cmds  *head;
    char    **tab;
    int     i;

    i = 0;
    tab = split_minishell(str, ';');
    if (!(list = malloc(sizeof(t_list))))
        return (NULL);
    list->entry = tab[i];
    list->pipes = ft_split(list->entry, '|');
    head = list;
    while (tab[++i])
        {
            if (!(list->next = malloc(sizeof(t_list))))
                return (NULL);
            list = list->next;
            list->entry = tab[i];
            list->pipes = split_minishell(list->entry, '|');
        }
    list->next = 0;
    return (head);
>>>>>>> dev
}