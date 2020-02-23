# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 22:09:29 by vabraham          #+#    #+#              #
#    Updated: 2020/02/23 15:53:43 by vabraham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FILES = src/main.c src/matrix.c src/key_press.c src/new.c src/rec_file.c src/brez.c
LIB = includes/libft/libft.a
NAME = fdf
OBJ = $(patsubst %.c,%.o,$(FILES))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C includes/libft re
	@gcc -Wall -Wextra -Werror -L includes/libft -lft $(FILES) -I includes/libft -I src/fdf.h -o $(NAME) -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
%.o: %.c
	@gcc -Wall -Werror -Wextra -I src/fdf.h $< -c -o $@

clean:
	@rm -rf $(OBJ)
	@make -C includes/libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C includes/libft fclean

re: fclean all

.PHONY: all clean fclean re
