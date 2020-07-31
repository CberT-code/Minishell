#include "../../minishell.h"

int          display_export(t_env *list, t_env *data, int fd)
{
        ft_tri_varlst(&list);
        while(list)
        {
            write(fd, "declare -x ", 11);
            write(fd, list->var, ft_strlen(list->var));
            write(fd, "\"", 1);
            write(fd, list->valeur, ft_strlen(list->valeur));
            write(fd, "\"\n", 2);
            list = list->next;
        }
        while(data)
        {
            write(fd, "declare -x ", 11);
            write(fd, data->var, ft_strlen(data->var));
            write(fd, "\"", 1);
            write(fd, data->valeur, ft_strlen(data->valeur));
            write(fd, "\"\n", 2);
            data = data->next;
        }
        return (1);
    return (0);
}

int    ft_tablen(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return (i);
    while (tab[i])
        i++;
    return (i);
}

char        *double_char(char *str, char c)
{
    int i;
    char *ret;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == c && str[i + 1] != c && (str[i - 1] != c || i == 0))
        {
            ret = add_char(str, c, i);
            free(str);
            str = ret; 
        }
        i++;
    }
    return (str);
}

char        **ft_tri_vartab(char **tab)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while (tab[i])
    {
        j = 0;
        while (j < ft_tablen(tab) - 1)
        {
            if (ft_strcmp(tab[j], tab[j + 1]) > 0)
            {
                temp = ft_strdup(tab[j]);
                tab[j] = ft_strdup(tab[j + 1]);
                tab[j + 1] = ft_strdup(temp);
            }
            j++;
        }
        i++;
    }
    return (tab);
}

void         data_list(char *str, t_env *data)
{
    int     i;
    char    *var;
    char    *value;

    i = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\"')
         i++;
        var = check_var(str + i);
        i += ft_strlen(var);
        if (str[--i] == '=' && var != NULL)
        {
            value = check_value(str, ++i);
            if (str[i] == '\"')
                i += 2;
            i += ft_strlen(value);
        }
        else
        {
            value = NULL;
            i++;
        }
        ft_lstadd_back_env(&data, var, value);
    }
}    
