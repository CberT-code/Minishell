NAME = 			minishell

SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
INCS_PATH = ./includes/

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))
INCS = $(addprefix -I,$(INCS_PATH)) -I./libft/ -I/usr/local/include

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS_NAME= 		echo.c env.c env_list.c export.c clean_brackets2.c\
				export_utils.c ft_cd.c ft_cd_utils.c replace_env_utils3.c\
				ft_pwd.c unset.c ft_tri_lst.c lists_args.c verif_parenthesis.c \
				lists_pipes.c lists_redir.c lists_semicol.c replace_env_utils4.c \
				lists_utils.c check_bin.c check_var.c clean_backs.c fcts_utils.c\
				clean_quotes.c clean_spaces.c ft_free.c  replace_env_utils2.c \
				ft_free_utils.c pipes.c pipes_util.c quotes.c clean_brackets.c \
				redirections.c replace_env.c replace_env_utils.c ft_exit.c \
				split_minishell.c split_minishell_utils.c main.c list_to_tab.c \
				replace_env_utils5.c ft_cd_utils2.c pipes_util_2.c

CC = gcc

FLAGS =	-Wall -Werror -Wextra

LIB = libft/libft.a

LOGFILE	=		$(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`

all: 			$(NAME)

$(NAME):	$(OBJS) $(LIB)
		@$(CC) -o $(NAME) $(OBJS) $(LIB) $(INCS) 
		@echo "\033[0;34mExecutable Minishell \033[0m \033[0;32m [OK] \033[0m"
		
$(LIB):
		@echo "\033[0;33mCompiling...\033[0m"
		@make -C libft/ fclean
		@make -C ./libft/
		@echo "\033[0;34mCompilation libft \033[0m \033[0;32m [OK] \033[0m"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c includes/minishell.h
		@mkdir -p $(OBJS_PATH)
		@gcc $(FLAGS) $(INCS) -o $@ -c $<

run : 
		make re
		./$(NAME)

git:			fclean
				git add -A
				git add *
				git commit -u -m "$(LOGFILE) $(MSG)"
				git push

git_merge:		fclean
				git add -A
				git add *
				git commit -u -m "$(LOGFILE) Mergind to dev $(MSG)"
				git push

merge_c_dev:	git_merge
				git checkout dev
				git merge cyrille
				$(git)
				git checkout cyrille

merge_m_dev:	git_merge
				git checkout dev
				git merge mike
				$(git)
				git checkout mike

merge_dev_c:	git
				git checkout dev
				git pull
				git checkout cyrille
				git merge dev

merge_dev_m:	git
				git checkout dev
				git pull
				git checkout mike
				git merge dev

clean:
		@make -C libft/ clean
		@rm -rf $(OBJS_PATH)
		@echo "deleted ./obj/"

fclean: clean
		@make -C libft/ fclean
		@rm -rf $(NAME)
		@echo "deleted ./minishell"

re: fclean all

norm:
				~/.norminette/norminette.rb *

.PHONY:			all clean fclean re libft git merge_c_dev merge_m_dev merge_dev git_merge norm
