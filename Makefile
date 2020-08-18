<<<<<<< HEAD
SRCS = 			srcs/fcts/echo.c \
				srcs/fcts/env.c \
				srcs/fcts/env_list.c \
				srcs/fcts/export.c \
				srcs/fcts/export_utils.c \
				srcs/fcts/ft_cd.c \
				srcs/fcts/ft_cd_utils.c \
				srcs/fcts/ft_pwd.c \
				srcs/fcts/unset.c \
				srcs/lists/ft_tri_lst.c \
				srcs/lists/lists_args.c \
				srcs/lists/lists_pipes.c \
				srcs/lists/lists_redir.c \
				srcs/lists/lists_semicol.c \
				srcs/lists/lists_utils.c \
				srcs/check_bin.c \
				srcs/check_var.c \
				srcs/clean_backs.c \
				srcs/clean_quotes.c \
				srcs/clean_spaces.c \
				srcs/ft_free.c \
				srcs/ft_free_utils.c \
				srcs/pipes.c \
				srcs/pipes_util.c \
				srcs/quotes.c \
				srcs/redirections.c \
				srcs/replace_env.c \
				srcs/replace_env_utils.c \
				srcs/split_minishell.c \
				srcs/split_minishell_utils.c \
				main.c

BONUS = 		bonus/*

NAME = 			minishell
=======
NAME = 			Minishell
>>>>>>> mike

SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
INCS_PATH = ./includes/

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))
INCS = $(addprefix -I,$(INCS_PATH)) -I./libft/ -I/usr/local/include

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS_NAME= 		echo.c env.c env_list.c export.c \
				export_utils.c ft_cd.c ft_cd_utils.c \
				ft_pwd.c unset.c ft_tri_lst.c lists_args.c \
				lists_pipes.c lists_redir.c lists_semicol.c \
				lists_utils.c check_bin.c check_var.c clean_backs.c \
				clean_quotes.c clean_spaces.c ft_free.c \
				ft_free_utils.c pipes.c pipes_util.c quotes.c \
				redirections.c replace_env.c replace_env_utils.c \
				split_minishell.c split_minishell_utils.c main.c

CC = gcc

FLAGS =	-Wall -Werror -Wextra

LIB = libft/libft.a

LOGFILE	=		$(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`

all: 			$(NAME)

$(NAME):	$(OBJS) $(LIB)
		@$(CC) -o $(NAME) $(OBJS) $(LIB) $(INCS) 
		@echo "\033[0;34mExecutable Minishell \033[0m \033[0;32m [OK] \033[0m"
		@./Minishell
		
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
		@echo "deleted ./Minishell"

re: fclean all

norm:
				~/.norminette/norminette.rb *

.PHONY:			all clean fclean re libft git merge_c_dev merge_m_dev merge_dev git_merge norm
