#include "../../minishell.h"



int         find_env_in_tab(char *str, char **tri_selectif)
{
    int i;
    int ind;


    i = 0;
    ind = -1;
    if (ft_isdigit(str[i]))
        return (0);
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '=')
        i++;
    while (tri_selectif[++ind])
    {
        if (ft_strncmp(str, tri_selectif[ind], i) == 0 && 
       (*(tri_selectif[ind] + i) == '=' ||
        *(tri_selectif[ind] + i) == ' ' ||
        *(tri_selectif[ind] + i) == '\0'))
        {
        return (2);
        }     
    }
    return (1);
}
int         ft_nbrvar(char *str, char **tri_selectif)
{
    int i;
    int nb;

    i = 0;
    nb = 0;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i])
        {
            if (find_env_in_tab(str + i, tri_selectif) == 1)
                nb++;
           i += len_next_word(str + i);
        }
    }
    return (nb);
}

char        *fill_new_env(char *str, int i)
{
    if (!(ret = malloc(sizeof(char) * i + 1)))
        exit(0);
    i = 0;
    while (str[i] != ' ' && str[i] != '=' && str[i] != '\0')
        ret[i] = str[i++];
    if (str[i] = '=')
    {
        ret[i + 1] = '\"';
        while (str[i] != ' ' && str[i])
        {
            ret[i + 1] = str[i++];
        }
        ret[i + 1] = '\0';
    }
}

char         *add_new_env(char *str)
{
    int i;
    char *ret;

    i = ft_strlen_str(str, " =");
    if (str[i] = '=')
    {
        while (str[i] != ' ' && str[i])
            i++;
        i += 2;
    }
    ret = fill_new_env(str, i);
}


char         *replace_env(char *str, char **tri_selectif)
{
    int i;

    while
}

void        fill_env(int ind, char *str, char **tri_selectif, char **new_tab)
{
    int i;
    int nb;

    i = 0;
    nb = 0;
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i])
        {
            if (find_env_in_tab(str + i, tri_selectif) == 1)
               new_tab[ind++] = add_new_env(str + i);
               // printf("il exist n'existe pas %d, %s\n", ind++, str + i);
            if (find_env_in_tab(str + i, tri_selectif) == 2)
               new_tab[ind++] = replace_env(str + i, tri_selectif);
                // printf("il existe %d, %s\n", ind++, str + i);
           i += len_next_word(str + i);
        }
    }
}

char         **ft_export(char *str, char **tri_selectif)
{
    int i;
    int nbr;
    char **tableau_des_variables_d_environnement;

    i = 0;
    while (tri_selectif[i])
        i++;
    nbr = ft_nbrvar(str, tri_selectif);
    printf ("nbr var = %d\n",nbr);
    if (!(tableau_des_variables_d_environnement = malloc(sizeof(char *) * (i + nbr) + 1)))
        exit(0);  
    i = -1;
    while (tri_selectif[++i])
        tableau_des_variables_d_environnement[i] = ft_strncpy(tri_selectif[i], ft_strlen(tri_selectif[i]));
    fill_env(i, str, tri_selectif, tableau_des_variables_d_environnement);
      //  tableau_des_variables_d_environnement[i++] = ft_strncpy(str, ft_strlen(str));
    tableau_des_variables_d_environnement[i + nbr] = NULL;
    return (tableau_des_variables_d_environnement);
}

int main(int argc, char **argv, char **envp)
{
	char *test = "SHLVL=10 vscodetoto ipocampe 8tarentule vagabond";
    char **tab;
    int i = -1;

    tab = ft_export(test, envp);
	//while (tab[++i])
       // printf("%s\n", tab[i]);
	return (0);
}