SRCS		= pipes.c \

BONUS		= bonus/*

NAME = 		Minishell

FLAGS =		-Wall -Werror -Wextra

LOGFILE		= $(LOGPATH) `date +'%y.%m.%d %H:%M:%S'`

all: 		$(NAME)

$(NAME):	
			make -C libft
			clang $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)
			./$(NAME)

libft:
			make re -C libft
			make clean -C libft

git:		fclean
			git add -A
			git add *
			git commit -u -m "$(LOGFILE) $(MSG)"
			git push

merge_cdev:	git
			git checkout dev
			git merge cyrille
			git checkout cyrille

merge_mdev:	git
			git checkout dev
			git merge mike
			git checkout mike

clean:
			make clean -C libft
			rm -f $(NAME)

fclean:		
			make fclean -C libft
			rm -f ${NAME}

re: 		clean
			clang $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)
			./$(NAME)

bonus:		clean
			clang $(FLAGS) $(BONUS) libft/libft.a -o $(NAME)
			./$(NAME)

norm:
			~/.norminette/norminette.rb *

.PHONY:		all clean fclean re bonus libft git merge_cdev merge_mdev norm
