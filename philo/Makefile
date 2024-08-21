# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 22:50:23 by ychagri           #+#    #+#              #
#    Updated: 2024/08/21 04:00:36 by ychagri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo

CFLAGS	:=	cc -Wall -Wextra -Werror -fsanitize=address

SRCS	:=	philo.c parse.c init.c \

OBJS	:=	$(SRCS:.c=.o)

HEADER	:=	philo.h

all	: $(NAME)

$(NAME)	: $(OBJS)
	$(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re	: fclean all

.PHONY : all clean fclean re

push	: fclean
	git add .
	git commit -m "parse"
	git push