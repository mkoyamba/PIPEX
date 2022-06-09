# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 17:08:30 by mkoyamba          #+#    #+#              #
#    Updated: 2022/06/09 10:14:54 by mkoyamba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

NAME = pipex

INC_DIR =	.

SRC =	main.c \
		pipex.c \
		pipex_utils.c \
		ft_more_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[32;1m\n\nPipex created\n\n"

%.o: %.c
	@gcc $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@printf "\033[31;1m."

clean:
	@rm -rf $(OBJ) $(OBJB)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, bonus, re