#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>
#define SIMPQ 39
#define DOUBQ 34
#define BACKS 92

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
int		                ft_del_name(char *str);
int		                ft_in_quotes(char *str, int i);
char	                *ft_last_space(char *str);
char                    *ft_convert_envp(char *str, char **envp);
t_env                   *ft_tab_to_list(char **tri_selectif);
int                     display_export(t_env *list, int fd, char *str);
int                     ft_tablen(char **tab);
char                    **ft_tri_vartab(char **tab);
t_env                  *data_list(char *str);
char                   *check_var(char *str);
char                   *check_value(char *str, int i);
char	                *ft_clean_spaces(char *str);
char	                *ft_envcpy(char *str, char **env);
int                     ft_isbacks(char *str, int i);
int                     ft_isquote(char *str, int i);
#endif