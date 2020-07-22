#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>

#define SIMPQ 39
#define DOUBQ 34
#define BACKS 92

typedef	struct	           s_redir
{
    char                   *str;
    struct s_redir         *next;
}			               t_redir;


typedef	struct	           s_tab_redir
{
    t_redir                *simpl;
    t_redir                *doubl;
}			               t_tab_redir;

typedef struct             s_args
{
    char                   *str;
    struct s_args          *next;
}                          t_args;

typedef struct             s_cmds
{
    char                   *str;
    t_args                 *args;
}                          t_cmds;

typedef struct             s_pipes
{
    char                   *str;
    t_tab_redir            redir_in;
    t_tab_redir            redir_out;
    t_cmds                 cmds;
    struct s_pipes         *next;
}                          t_pipes;

typedef struct             s_semicol
{
    char                   *str;
    int                    nb_cmd;
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
int	                    ft_isbacks(char *str, int i);
int	                    ft_isquote(char *str, int i);


t_semicol		    	*ft_lstnewsemicol(char *str, char **env);
t_semicol		    	*ft_lstlastsemicol(t_semicol *cmds);
void			        lstadd_back_semicol(t_semicol **semicol, char *str, char **env);

t_pipes			        *ft_lstnewpipes(char *str, char **env);
t_pipes			        *ft_lstlastpipes(t_pipes *cmds);
void		         	lstadd_back_pipes(t_pipes **pipes, char *str, char **env);

t_args		        	*ft_lstnewargs(char *str, char **env);
t_args		        	*ft_lstlastargs(t_args *cmds);
void		        	lstadd_back_args(t_args **args, char *str, char **env);

int		            	split_semicol(char *str, t_semicol **semicol, char **env);
t_pipes		        	*split_pipes(char *str, char **env);
t_args                  *split_args(char *str, char **env);
t_cmds		        	cmds_args(char *str, char **env);

int		                ft_strlen_str_quotes(char *s, char *str);

t_tab_redir			    full_redir(char *str, char c, char **env);
void                    ft_splitting(char *str, char c, t_tab_redir *redir, char **env);


t_redir			        *ft_lstnewredir(char *str, char **env);
t_redir		        	*ft_lstlastredir(t_redir *redir);
void			        lstadd_back_redir(t_redir **redir, char *str, char **env);

int                     ft_isbacks(char *str, int i);
int                     ft_isquote(char *str, int i);
char	                *ft_clean_quotes(char *str);

char                	*ft_clean_backs(char *str);
void	                ft_cpy_in_squotes(char *str, char *cpy, int *i, int *j);
void	                ft_cpy_in_dbquotes(char *str, char *cpy, int *i, int *j);

int		            	count_pipe(t_semicol *semicol);
void	                new_str(t_pipes *pipes);

#endif