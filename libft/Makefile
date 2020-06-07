# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 12:20:26 by cbertola          #+#    #+#              #
#    Updated: 2020/02/19 00:54:30 by cbertola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MP -MMD -MF $(DEP_DIR)/$*.d -MT '$@'

# DIRECTORIES
DEP_DIR	= dep
OBJ_DIR	= obj
DIR		= $(DEP_DIR) $(OBJ_DIR)

# FILES
NAME	= libft.a
SRC		= ft_strlen.c ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcat.c \
		  ft_strnstr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_bzero.c ft_toupper.c ft_tolower.c ft_memset.c ft_memcpy.c ft_memccpy.c \
		  ft_memmove.c ft_memchr.c ft_memcmp.c ft_atoi.c ft_calloc.c ft_strdup.c \
		  ft_substr.c ft_strjoin.c ft_strjoin_free.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isfind.c \
		  ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_int.c \
		  ft_atoi_pos.c ft_printf.c ft_flags.c ft_fct.c ft_cs.c ft_p.c \
		  ft_diu.c ft_x.c get_next_line_utils.c get_next_line.c ft_start_str.c \
		  ft_count_char_int.c ft_how_many.c ft_strsubstr.c ft_strsubstr_free.c \
		  ft_splitnum.c ft_strlen_no_ws.c is_tab_full.c
SRCB	=
DEP		:= $(SRC:%.c=$(DEP_DIR)/%.d)
OBJ 	:= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPB	:= $(SRCB:%.c=$(DEP_DIR)/%.d)
OBJB 	:= $(SRCB:%.c=$(OBJ_DIR)/%.o)
$(NAME): $(OBJ)
	ar -rcs $@ $^
	ranlib $@

all: $(NAME)

clean:
	rm -rf $(DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME) $(OBJB)
	ar -rcs $(NAME) $^ 

$(DEP_DIR):
	mkdir $@

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: %.c | $(DIR)
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

-include $(DEP)

.PHONY: all clean fclean re bonus
