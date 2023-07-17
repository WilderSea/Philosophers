# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 17:02:35 by msintas-          #+#    #+#              #
#    Updated: 2023/07/17 12:24:36 by msintas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

SRCS	=	main.c \
			init.c \
			philo.c \
			actions.c \
			time.c \
			kos.c \
			meals.c \
			utils.c

CC		=	gcc

#CFLAGS	=   -Wextra -Wall -Werror -pthread -fsanitize=thread
CFLAGS	=   -Wextra -Wall -Werror -pthread

RM		=	rm -rf

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		
			$(RM) $(OBJS) $(NAME)

re:			fclean all

run : all
	./$(NAME)

.PHONY:		all clean fclean re bonus
