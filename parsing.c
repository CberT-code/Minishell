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
}