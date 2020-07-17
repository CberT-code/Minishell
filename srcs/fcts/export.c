#include "../../minishell.h"

char         *check_var(char *str)
{
    int     i;

    i = 0;
    while (str[i] == ' ' || str[i] == '\"')
        i++;
    if (str[i] != '\0')
        return (ft_strcpyuntil(str + i, " ="));
    else 
        return (NULL);
}

char         *check_value(char *str, int i)
{
    char    *ret;
    int     start;

    if (str[i] == '\"')
        i++;
    start = i;
    if (ft_in_quotes(str, i) != 0)
    {
        while (ft_in_quotes(str, i) != 0)
            i++;
        i -= start;
        i--;
        ret = ft_strncpy(str + start, i);
        return (double_char(ret, '\\'));
    }
    return (ft_strcpyuntil(str + i, " "));
}

void        replace_env(t_env *list_env, t_env *list_data)
{
    t_env   *data;

     while (list_env->next != NULL)
    {
        data = list_data;
         while (data != NULL)
        {
            if (ft_strcmp(data->var, list_env->var) == 0)
            {
                printf("We are here\n");
                list_env->valeur = data->valeur;
            }
            data = data->next;
        }
        list_env = list_env->next;
    }
}

void        add_env(t_env *list_env, t_env *list_data)
{
     t_env   *env;
     int    find;

     while (list_data != NULL)
    {
        env = list_env;
        find = 0;
         while (env->next != NULL && find == 0)
        {
            if (ft_strcmp(list_data->var, env->var) == 0)
             find = 1;
            env = env->next;
        }
        if (find == 0)
        {
            printf("here we test -> %s\n", list_data->var);
            printf("here we test -> %s\n", list_data->valeur);
            ft_lstadd_back_env(&list_env, list_data->var, list_data->valeur);
        }
        list_data = list_data->next;
    }
}
                                                 
int         ft_export(char *str, char **tri_selectif, int fd)
{
    char    **tab_env;
    t_env   *list_env;
    t_env   *list_data;

    tab_env = ft_tri_vartab(tri_selectif);
    list_env = ft_tab_to_list(tri_selectif);
    if (display_export(list_env, fd, str))
        return (0);
    list_data = data_list(str);
    replace_env(list_env, list_data);
    add_env(list_env, list_data);
    printf("%s%s\n", list_env->var, list_env->valeur);
    while (list_env->next != NULL)
    {
        list_env = list_env->next;
        printf("%s%s\n", list_env->var, list_env->valeur);
    }
    return (1);
}

int main(int argc, char **argv, char **envp)
{
	char *test = " USERSR=\"emo  te\" toto=pepo USER=\"pipa toto\"";
    int ret;
    int i = -1;

    ret = ft_export(test, envp, 1);
	//while (tab[++i])
       // printf("%s\n", tab[i]);
	return (0);
}