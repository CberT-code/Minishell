#ifndef MINISHELL_H
# define MINISHELL_H

#include	"../libft/libft.h"
#include	<sys/wait.h>
#include	<signal.h>

# define		SIMPQ				39
# define		DOUBQ				34
# define		BACKS				92
# define		MAXLONG				9223372036854775807
# define		ERROR_SYNTAX 		"\033[1;31mErreur de syntaxe \033[0;0m\n"
# define		ERROR_FILE_FOLDER 	"\033[1;31mAucun fichier ou dossier de ce type\033[0;0m\n"
# define		ERROR_FIND_CMD		"\033[1;31mLa commande n'a pas été trouvée.\033[0;0m\n"
# define		IDERRONE 			"\033[1;31mexport: identifiant non valable\033[0;0m\n"
# define		ARGUMENTS 			"exit: trop d'arguments\n"
# define		ARGUMENTS_NUM 		"exit: argument numérique nécessaire\n"
#define			ERROR_GETCWD 		"cd : erreur de détermination du répertoire actuel : getcwd : ne \
peut accéder aux répertoires parents : Aucun fichier ou dossier de ce type"

typedef	struct			s_redir
{
	char				*str;
	int					ind;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_args
{
	char				*str;
	struct s_args		*next;
}						t_args;

typedef struct			s_cmds
{
	char				*str;
	int					nb_args;
	t_args				*args;
}						t_cmds;

typedef struct			s_pipes
{
	char				*str;
	t_redir				*redir_in;
	t_redir				*redir_out;
	t_cmds				cmds;
	struct s_pipes		*next;
}						t_pipes;

typedef struct			s_semi
{
	char				*str;
	char				*g_line;
	int					nb_pipes;
	void				*first_semi;
	char				***all;
	t_pipes				*pipes;
	struct s_semi	*next;
}						t_semi;
typedef struct			s_env
{
	char				*var;
	char				*valeur;
	struct s_env		*next;
}						t_env;

typedef struct			s_gbl
{
	char				*path;
	char			 	*pwd;
	int					pid;
	int					rep;
	int					sta;
	int					error;
	int					ret;
	char				*line;
	t_semi				*semi;
	t_env				*env;
}						t_gbl;

t_cmds					*ft_lstnewcmds(char *str);
t_cmds					*ft_lstlast(t_cmds *cmds);
void					ft_lstadd_back(t_cmds **alst, char *str);
void					ft_lstadd_back_env(t_env **alst, char *str, char *str2, t_gbl *gbl);
t_cmds					*parsing(char *str, t_env *envp);
int						in_quotes(char *s, int i, int in);
int						ft_redir(char *s, char c);
int						len_next_word(char *str);
int						ft_del_name(char *str);
int						ft_in_quotes(char *str, int i);
char					*ft_last_space(char *str);
t_env					*ft_tab_to_list(char **tri_selectif, t_gbl *gbl);
int						display_export(t_env *list);
int						ft_tablen(char **tab);
char					**ft_tri_vartab(char **tab);
char					*check_var(char *str);
char					*check_value(char *str, int i);
char					*ft_clean_spaces(char *str);
char					*ft_envcpy(char *str, t_gbl *gbl);
int						ft_find_size_arg(char *str);
char					*ft_replace_value(char *str, t_gbl *gbl);
char					*ft_replace_bashname(char *str, t_env *env);
int						ft_isbacks(char *str, int i);
int						ft_isquote(char *str, int i);
t_semi					*ft_lstnewsemi(t_gbl *gbl, char *str);
t_semi					*ft_lstlastsemi(t_semi *cmds);
void					lstadd_back_semi(t_gbl *gbl, char *str);
t_pipes					*ft_lstnewpipes(t_gbl *gbl, char *str);
t_pipes					*ft_lstlastpipes(t_pipes *cmds);
void					lstadd_back_pipes(t_gbl *gbl, t_pipes **pipes, char *str);
t_args					*ft_lstnewargs(char *str, t_env *env);
t_args					*ft_lstlastargs(t_args *cmds);
void					lstadd_back_args(t_args **args, char *str, t_env *env);
int						split_semi(t_gbl *gbl);
t_pipes					*split_pipes(t_gbl *gbl, t_semi *semi);
t_args					*split_args(char *str, t_env *env);
void					cmds_args(t_cmds *cmd, char *str, t_env *env);
int						ft_strlen_str_quotes(char *s, char *str);
t_redir				full_redir(char *str, char c, t_env *env);
t_redir					*ft_lstnewredir(char *str, int i);
t_redir					*ft_lstlastredir(t_redir *redir);
void					lstadd_back_redir(t_redir **redir, char *str, int i);
int						ft_isbacks(char *str, int i);
int						ft_isquote(char *str, int i);
int						ft_isbracket(char *str, int i);
char					*ft_clean_quotes(char *str);
char					*ft_clean_backs(char *str);
char 					*ft_clean_brackets(char *str);
int						ft_verif_commands(char *str);
void					ft_cpy_in_squotes(char *str, char *cpy, int *i,
		int *j);
void					ft_cpy_in_dbquotes(char *str, char *cpy, int *i,
		int *j);
int						count_pipe(t_semi *semi);
void					new_str(t_semi *semi);
void					count_args(t_cmds *cmd);
void					ft_fill_cmds(t_semi *semi);
char					**new_tab(t_pipes *pipes);
void					tab_all(t_semi *semi);
int						ft_envlen(char *str, t_env *env, int *cpt);
void					ft_simpq_len(char *str, int *i, int *len);
void					ft_doubleq_len(char *str, t_env *env, int *i,
		int *len);
int						ft_envcpylen(char *str, t_env *env);
int						ft_len_replace_value(char *str, t_gbl *gbl);
int						ft_fill_replace_value(char *cpy, int *j, char c, t_gbl *gbl);
char					*ft_check_brackets(char *str);
int						ft_end_brackets(char *str);
int						ft_end_brackets_doubq(char *str);
int						ft_isbacks(char *str, int i);
int						ft_isquote(char *str, int i);
int						exec_cmds(t_semi *semi, t_gbl *gbl);
int						ft_export(t_args *args, t_gbl *gbl);
char					*double_char(char *str, char c);
char					**ft_tri_vartab(char **tab);
void					data_list(char *str, t_gbl *gbl);
void					ft_tri_varlst(t_env **lst_env);
void					ft_lstadd_back_var(t_env **alst, char *var,
		char *valeur);
t_env					*ft_lstlast_var(t_env *lst);
t_env					*ft_lstnew_var(char *var, char *valeur);
int						replace_env(t_env *env, char *var, char *value);
void					suppr_maillon(t_env **list, t_env *ptr);
int						condition(char *str, char *str2);
int						ft_unset(t_args *args, t_gbl *gbl);
void					unset(char *str, t_gbl *gbl);
int						delete_var(char *var, t_env *env);
void					ft_free(t_semi *semi);
void					free_tab_all(char ***all);
void					free_pipes(t_pipes *pipes);
void					free_tab_redir(t_redir *redir);
void					free_redir(t_redir *redir);
void					free_cmds(t_cmds *cmds);
void					free_args(t_args *args);
void					free_exit(t_semi *semi, t_gbl *gbl, char *str);
void					ft_free_env(t_env *env);
char					*clean_redir(char *str, char c);
int						ft_env(t_args *args, t_gbl *gbl);
int						check_str_alpha(char *str, int len);
void					check_line(char *str);
int						find_fcts(t_cmds *cmd, t_gbl *gbl);
int						ft_echo(t_args *args, t_gbl *gbl);
int						ft_cd(t_args *args, t_gbl *gbl);
void					ft_change_path(t_gbl *gbl);
int						ft_check_cd_errors(t_env *env);
int						ft_check_size_args_cd(t_args *args);
char					*ft_getenv(char *str, t_env *env);
int						ft_size_args(t_args *args);
int						ft_pwd(void);
int						search_mybin(char *str);
char					*check_path(char *str, t_gbl *gbl);
void					exec_fork(t_semi *semi, int j, t_gbl *gbl);
int						cond_pipe(t_semi *semi, char *str);
void					do_dup(int j, int *pipes, t_semi *semi, t_gbl *gbl);
void					redir_out(t_redir *redir, int *pipes, int j);
void					wait_pipes(int nb_pipes, pid_t *pid, int *ret);
void					close_pipes(int nb_pipes, int *pipes);
void					init_pipes(int nb_pipes, int *pipes);
char     				**list_to_tab(t_env *env);

int						ft_strlen_str_quotes_backs(char *s, char *str);
void					free_tab(char **tab);
void   					ft_change_args(t_cmds *cmd, t_gbl *gbl);

void					ft_redir_in(char *str, t_redir **redir, t_gbl *gbl);
void					ft_redir_out(char *str, t_redir **redir, t_gbl *gbl);
void					free_exit2(t_gbl *gbl, char *str);
int   					ft_exit(t_cmds *cmd, t_gbl *gbl);

void					ft_simpq_cpy_all(char *str, char *cpy, int *i, int *j);
int						ft_verif_crochets(char *str, t_env *env);
int						ft_iscrochet(char *str, int i);
char					*ft_replace_crochets(char *str);

#endif
