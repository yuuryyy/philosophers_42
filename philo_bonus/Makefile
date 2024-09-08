# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 22:06:51 by ychagri           #+#    #+#              #
#    Updated: 2024/09/08 00:07:27 by ychagri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo_bonus

COMPILE	:= cc -Wall -Wextra -Werror

HEADER	:=	inc/philo_bonus.h \

SRCS	:=	philo_bonus.c \
			processes/init_data.c \
			parse/valid_args.c \

OBJS	:= $(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	: $(OBJS)
	$(COMPILE) $(OBJS) -o $(NAME)

%.o	: %.c $(HEADER)
	$(COMPILE) -c $< -o $@

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all

.PHONY : all clean fclean re

push	: fclean
	git add .
	git commit -m "bonus"
	git push