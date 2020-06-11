#include "minishell.h"


t_cmds     *split_pipes(char *str)
{
    t_cmds  *list;
    t_cmds  *head;
    char    **tab;
    int     i;
    int     j; // aV

    i = 0;
    j = 0; // aV
    tab = ft_split(str, ';');
     if (!(list = malloc(sizeof(t_list))))
                return (NULL);
    list->entry = tab[i];
    list->pipes = parsing_pipes(list->entry);
    head = list;
    ft_printf("entry = %s\n pointeur = %p\n\n", list->entry, list); // aV
     while (list->pipes[j]) // aV
                ft_printf("pipes = || %s\n\n", list->pipes[j++]); // aV
    while (tab[++i])
        {
            j = 0; // aV
            if (!(list->next = malloc(sizeof(t_list))))
                return (NULL);
            list = list->next;
            list->entry = tab[i];
            list->pipes =ft_split(list->entry, '|');
            ft_printf("entry = %s\n pointeur = %p\n\n", list->entry, list); // aV
            while (list->pipes[j]) // aV
                ft_printf("pipes = || %s\n\n", list->pipes[j++]); // aV
        }
        
        list->next = 0;
        ft_printf("pointeur head = %p\n", head); // aV
    return (head);
}

