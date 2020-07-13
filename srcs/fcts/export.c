#include "../../minishell.h"

int          display_export(t_env *list, int fd, char *str)
{
    while (*str == ' ')
        str++;
    if (*str == '\0')
    {
        while(list->next)
        {
            write(fd, "declare -x ", 11);
            write(fd, list->var, ft_strlen(list->var));
            write(fd, "\"", 1);
            write(fd, list->valeur, ft_strlen(list->valeur));
            write(fd, "\"\n", 2);
            list = list->next;
        }
        return (1);
    }
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

int         replace_env(char *str, t_env *list)
{
    int i;
    int j;
    int in;

    while (list->next != NULL)
    {
        if (ft_strcmp(ft_strcpyuntil(str, "= "), list->var) == 0)
        {
            
            i = ft_strlen_str(str, "= ");
            j = -1;
            free(list->valeur);
            if (!(list->valeur = malloc(sizeof(char) * ft_strlen_str(str + i, " ") + 1)))
                return (0);
            while (str[i] != ' ' || in)
            {
                list->valeur[++j] = str[++i];
                in = in_quotes(str, i, in);
            }
            list->valeur[++j] = '\0';
            return (i);
        }
    list = list->next;
    }
    return (len_next_word(str));
}

char        *arg2(char *str)
{
    int     i;
  
  printf("ici on test str = %s\n",str);
    i = 0;
    if (*str == '\'' || *str == '\"')
    {
        while (ft_in_quotes(str, i) != 0)
            i++;
    }
    else 
        i = len_next_word(str);
    printf("ici on test valeur de i = %d\n",i);   
    return(ft_strncpy(str, i));
}

int        add_new_env(char *str, t_env *list)
{
    int i;
    int j;

    while (list->next != NULL)
    {
        if (ft_strcmp(ft_strcpyuntil(str, "="), list->var) == 0)
            return (len_next_word(str));
    list = list->next;
    }
    printf("ici on test la valeur de retour de arg2 = %s\n",arg2(str + ft_strlen_str(str, "=") + 1));
    ft_lstadd_back_env(&list, ft_strcpyuntil(str, "="), arg2(str + ft_strlen_str(str, "=")));
    return (len_next_word(str));
}

char         *check_var(char *str, list_env *list)
{
    int i;
    char *ret;

    i = 0;
    while (str[i] == ' ' || str[i] == '\"')
        i++;
    ret = ft_strcpyuntil(str, " =");


}

int         check_list(char *str, list_env *list)
{
    int i;
    int j;
    char *var;

    i = 0;
    while (str[i])
    {
        var = check_var(str + i);
        i += ft_strlen(ret);
        j = 0;
        if (str[i] == '=')
            while (str)


    }
}                                                     
int         ft_export(char *str, char **tri_selectif, int fd)
{
    char    **tab_env;
    t_env   *list_env;
    int     i;

    i = 0;
    tab_env = ft_tri_vartab(tri_selectif);
    list_env = ft_tab_to_list(tri_selectif);
    if (display_export(list_env, fd, str))
        return (exit(0));
    check_list(str, list_env);
    
    // while (str[i])
    // {
    //     while (str[i] == ' ')
    //         i++;
    //     i += replace_env(str + i, list_env);
    // }
    // i = 0;
    //  while (str[i])
    // {
    //     while (str[i] == ' ')
    //         i++;
    //     i += add_new_env(str + i, list_env);
    // }
    // i = 0;
    while (list_env->next != NULL)
    {
         printf("%s%s\n", list_env->var, list_env->valeur);
        list_env = list_env->next;
    }
    return (1);
}

int main(int argc, char **argv, char **envp)
{
	char *test = " USERSR=\"emo  te\" ";
    int ret;
    int i = -1;

    ret = ft_export(test, envp, 1);
	//while (tab[++i])
       // printf("%s\n", tab[i]);
	return (0);
}