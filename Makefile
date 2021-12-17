# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 13:55:50 by bemoreau          #+#    #+#              #
#    Updated: 2021/12/16 19:03:19 by bemoreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
INCLUDE = pipex.h\

INC_PATH = ./includes/

vpath %.c sources/builtins
vpath %.c sources/

FILES =		./sources/main\
			./sources/redir\
			./sources/pipe\
			./sources/path\
			./sources/utils\
			./sources/utils2\
			./sources/utils/ft_split\
			./sources/utils/ft_substr\
			./sources/utils/ft_putendl_fd\
			./sources/utils/ft_putstr_fd\
			./sources/utils/ft_strncmp\
			./sources/utils/ft_strdup\
			./sources/utils/ft_strjoin_c\
			./sources/utils/ft_calloc\
			./sources/utils/ft_strlen\
			./sources/utils/ft_putchar_fd\
			./sources/utils/ft_bzero\
			./sources/utils/ft_memset
SRCS = $(addsuffix .c, $(FILES))
OBJ = $(SRCS:.c=.o)

CC = gcc
L_CC = clang
FLAGS = -Wall -Wextra -Werror

### COLORS ###

NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
VIOLET = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

all: 		$(NAME)

$(NAME): 	$(OBJ)
			@echo "$(CYAN)Constructing executable:$(NOC) $@"
			@$(L_CC) -g3 $(FLAGS) -o $(NAME) $(OBJ)

.c.o:		${SRCS}
			@echo " $(VIOLET)[$(L_CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
			@$(L_CC) -g3 $(FLAGS) -c -I$(INC_PATH) $< -o ${<:.c=.o}
clean:
	@echo "\n$(RED)Removing '.o' objects: $(NOC) $@"
	@rm -f $(OBJ)

fclean: clean
	@echo "\n$(RED)Removing executable: $(NOC) $@"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean
