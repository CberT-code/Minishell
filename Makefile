SRCS = 			srcs/split_minishell.c srcs/split_minishell_utils.c \
				srcs/lists/lists_args.c srcs/lists/lists_pipes.c \
				srcs/lists/lists_semicol.c srcs/lists/lists_redir.c \
				srcs/quotes.c srcs/clean_backs.c srcs/clean_spaces.c \
				srcs/replace_env.c  srcs/redirections.c srcs/clean_quotes.c 
				

BONUS = 		bonus/*

NAME = 			Minishell

FLAGS =			-Wall -Werror -Wextra

LOGFILE	=		$(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`

all: 			$(NAME)

$(NAME):	
				make -C libft
				clang $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)
				./$(NAME)

libft:
				make re -C libft
				make clean -C libft

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
				make clean -C libft
				rm -f $(NAME)
				rm -f a.out

fclean:		
				make fclean -C libft
				rm -f ${NAME}

re: 			clean
				clang $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)
				./$(NAME)

bonus:			clean
				clang $(FLAGS) $(BONUS) libft/libft.a -o $(NAME)
				./$(NAME)

norm:
				~/.norminette/norminette.rb *

.PHONY:			all clean fclean re bonus libft git merge_c_dev merge_m_dev merge_dev git_merge norm
