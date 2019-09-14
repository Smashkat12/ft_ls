# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/14 09:51:46 by kmorulan          #+#    #+#              #
#    Updated: 2019/09/14 09:59:48 by kmorulan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FILES = src/main.c \
		src/flags.c \
		src/ft_ls.c \
		src/lex_sort.c \
		src/sort_list.c \
		src/path_entry_list.c \
		src/print_handler.c \
		src/printing.c \
		src/validate.c \

INC = -I includes \
	  -I libft/

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME):$(FILES)
	make -C libft/
	gcc -Wall -Werror -Wextra $(FILES) $(INC) -L libft/ -lft -o $(NAME)

clean:
	make -C libft/ clean
	rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re