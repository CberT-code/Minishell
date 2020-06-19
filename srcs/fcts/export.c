#include "../../minishell.h"

char         **ft_export(char *str, char **tri_selectif)
{
    int i;
    char **tableau_des_variables_d_environnement;

    i = 0;
    while (tri_selectif[i])
        i++;
    if (!(tableau_des_variables_d_environnement = malloc(sizeof(char *) * i + 2)))
        exit(0);
    i = -1;
    while (tri_selectif[++i])
        tableau_des_variables_d_environnement[i] = ft_strncpy(tri_selectif[i], ft_strlen(tri_selectif[i]));
    tableau_des_variables_d_environnement[i++] = ft_strncpy(str, ft_strlen(str));
    tableau_des_variables_d_environnement[i++] = NULL;
    return (tableau_des_variables_d_environnement);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char *test = "zozo=popo";
//     char **tab;
//     int i = -1;

//     tab = ft_export(test, envp);
// 	while (tab[++i])
//         printf("%s\n", tab[i]);
// 	return (0);
// }