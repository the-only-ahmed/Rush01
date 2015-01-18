# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/06 21:25:08 by ael-kadh          #+#    #+#              #
#    Updated: 2015/01/18 08:28:28 by ael-kadh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= sample

VERSION=1.0

SRC=test3.cpp ModuleCPU.cpp AModule.cpp

CFLAGS=-Wall -Werror -Wextra -g3

TFLAGS=`pkg-config --cflags --libs gtk+-3.0`

all: $(NAME)

$(NAME):
	@g++ $(CFLAGS) -o $(NAME) $(SRC) $(TFLAGS)

fclean:
	@rm -rf $(NAME)

re: fclean all

v:
	@(echo "v$(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]\tis created!")

.PHONY: finish v re fclean all
