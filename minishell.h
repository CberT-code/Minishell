#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>

typedef	struct	        s_redir
{
    char                **r_out;
    char                **r_in;
    int                 **type_in;
    int                 **type_out;
}			            t_redir;

typedef struct         s_cmds
{
    char               *entry;
    char               **pipes;
    t_redir            redir;
    struct s_cmds      *next;
}
                      t_cmds;
                      
typedef struct         s_env
{
    char               *var;
    char               *valeur;
    struct s_env       *next;
}                      t_env;


/* FUNCTIONS LISTS */

t_cmds              	*ft_lstnewcmds(char *str);
t_cmds	                *ft_lstlast(t_cmds *cmds);
void                	ft_lstadd_back(t_cmds **alst, char *str);
void			        ft_lstadd_back_env(t_env **alst, char *str, char *str2);
t_cmds                  *parsing(char *str, char **envp);
char                    **split_minishell(char *s, char c);
char		            **split_chevron(char *s, char c, int *type_redir);
int                     in_quotes(char *s, int i, int in);
int                     ft_redir(char *s, char c);
int                     len_next_word(char *str);
int		                ft_in_quotes(char *str, int i);
char	                *ft_last_space(char *str);
char                    *ft_convert_envp(char *str, char **envp);
t_env                   *ft_tab_to_list(char **tri_selectif);

#endif