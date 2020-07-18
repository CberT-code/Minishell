#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>

#define SIMPQ 39
#define DOUBQ 34
#define BACKS 92


typedef	struct	           s_redir
{
    char                   **r_out;
    char                   **r_in;
    int                    **type_in;
    int                    **type_out;
}			               t_redir;

typedef struct             s_args
{
    char                   *arg;
    struct s_args          *next;
}                          t_args;

typedef struct             s_cmds
{
    char                   *cmd;
    t_args                 *args;
}                          t_cmds;

typedef struct             s_pipes
{
    char                   *pipes;
    t_redir                redir;
    t_cmds                 cmds;
    struct s_pipes         *next;
}                          t_pipes;

typedef struct             s_semicol
{
    char                   *semicol;
    t_pipes                *pipes;
    struct s_semicol       *next;
}                          t_semicol;

typedef struct             s_env
{
    char                   *var;
    char                   *valeur;
    struct s_env           *next;
}                          t_env;


/* FUNCTIONS LISTS */

t_cmds              	*ft_lstnewcmds(char *str);
t_cmds	                *ft_lstlast(t_cmds *cmds);
void                	ft_lstadd_back(t_cmds **alst, char *str);
void			        ft_lstadd_back_env(t_env **alst, char *str, char *str2);
t_cmds                  *parsing(char *str, char **envp);
int		            	split_semicol(char *str, t_semicol *semicol);
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
t_env                   *data_list(char *str);
char                    *check_var(char *str);
char                    *check_value(char *str, int i);
char	                *ft_clean_spaces(char *str);
char	                *ft_envcpy(char *str, char **env);
char	                *ft_clean_quotes(char *str);
int	                    ft_isbacks(char *str, int i);
int	                    ft_isquote(char *str, int i);


t_semicol		    	*ft_lstnewsemicol(char *str);
t_semicol		    	*ft_lstlastsemicol(t_semicol *cmds);
void			        lstadd_back_semicol(t_semicol *semicol, char *str);

t_pipes			        *ft_lstnewpipes(char *str);
t_pipes			        *ft_lstlastpipes(t_pipes *cmds);
void		         	lstadd_back_pipes(t_pipes *pipes, char *str);

t_args		        	*ft_lstnewargs(char *str);
t_args		        	*ft_lstlastargs(t_args *cmds);
void		        	lstadd_back_args(t_args *args, char *str);

int		            	split_semicol(char *str, t_semicol *semicol);
t_pipes		        	*split_pipes(char *str);
t_args                  *split_args(char *str);
t_cmds		        	cmds_args(char *str);

int		                ft_strlen_str_quotes(char *s, char *str);

#endif