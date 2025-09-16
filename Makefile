# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eliagarc <eliagarc@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/30 16:44:47 by eliagarc          #+#    #+#              #
#    Updated: 2024/02/07 15:19:30 by eliagarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCE = Src/main.c Src/checker.c Src/init.c Src/functions.c Src/aux_functions.c
INCLUDE = Inc/philo.h

SILENCE = --no-print-directory
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJS = $(SOURCE:.c=.o)

%.o: %.c Makefile $(INCLUDE)
	@echo "Compiling $<..."
	@${CC} -c ${CFLAGS} -I $(INCLUDE) $< -o $@

all:  $(NAME)

$(NAME): ${OBJS} $(INCLUDE) Makefile
	@echo "Creating executable..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) created!"

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	@echo "Object files removed!"

fclean:	clean
	@echo "Cleaning trash..."
	@rm $(NAME)
	@echo "Trash removed!"

re: 	fclean all

.PHONY: all clean fclean re
