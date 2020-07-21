#include "../minishell.h"

void            ft_splitting(char *str, char c, t_redir **redir, char **env)
{
    while (*str)
    {
        if (*str == c)
        {
            if (*(++str) == c)
            {
                str++;
                str += *str == ' ' ? 1 : 0 ;
                lstadd_back_redir(redir, ft_substr(str, 0, ft_strlen_str_quotes(str, " ")), env);
            }
            else
            {
                str += *str == ' ' ? 1 : 0 ;
                lstadd_back_redir(redir, ft_substr(str, 0, ft_strlen_str_quotes(str, " ")), env);
            }
            str++;
            str += ft_strlen_str_quotes(str, " ");
        }
        else
            str++;
    }
}

t_tab_redir			full_redir(char *str, char **env)
{
     t_tab_redir    redir;

    ft_bzero(&redir, sizeof(t_tab_redir));
    if (!str)
        return (redir);
    ft_splitting(str, '<', &redir.simple_in, env);
    ft_splitting(str, '<', &redir.double_in, env);
    ft_splitting(str, '>', &redir.simple_out, env);
    ft_splitting(str, '>', &redir.double_out, env);
    return (redir);
 
}

//   int main(void)
//   {
// 	 char **tab;
// 	 int i = 0;
// 	 int j = 0;
// 	 char *str;
//      int *redir;

// 	 str = "gr \";f < > \" < text.c > test >> pa << p >> popo >li";
//         // printf("adress tableau redir = %p\n", &redir);
//     if (!(redir = malloc(sizeof(int) * (ft_redir(str, '>') + 1))))
// 	        return (-1);
// 	 tab = split_chevron(str, '>', redir);
//         // printf("adress tableau redir = %p\n", &redir);
// 	while (tab[i])
// 	{
//     	printf("i = %d && print = %s\n",i, tab[i]);
//         // printf("adress redir = %p\n", &redir[i]);
//         printf("j = %d && print = %d\n",i, redir[i]);
// 	    i++;
// 	}

//  }