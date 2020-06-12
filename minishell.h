#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

typedef	struct	        s_redir
{
    char                **r_extern;
    char                **r_intern;
    int                 **type_extern;
    int                 **type_intern;
}			            t_redir;

typedef struct         s_cmds
{
    char               *entry;
    char               **pipes;
    struct s_cmds      *next; 
    t_redir            redir;
}                      t_cmds;

t_cmds      *split_pipes(char *str);
char	    **split_minishell(char const *s, char c);
int         ft_guillemets(char c, char c_b, char g);
#endif