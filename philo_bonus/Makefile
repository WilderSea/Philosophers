# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 17:02:35 by msintas-          #+#    #+#              #
#    Updated: 2023/07/12 12:37:19 by msintas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	main.c \
			init.c \
			philo.c \
			actions.c \
			time.c \
			kos.c \
			meals.c \
			utils.c

#BONUS	=	xxx_bonus.c

CC		=	gcc

#CFLAGS	=   -Wextra -Wall -Werror -pthread -fsanitize=thread
CFLAGS	=   -Wextra -Wall -Werror -pthread

RM		=	rm -rf

OBJS	=	$(SRCS:.c=.o)

#BOBJS	=	$(BONUS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS) $(BOBJS)

fclean:		
			$(RM) $(OBJS) $(BOBJS) $(NAME)

re:			fclean all

#bonus:		$(BOBJS)
#			$(CC) $(CFLAGS) $(BOBJS) -o $(NAME)

run : all
	./$(NAME)

.PHONY:		all clean fclean re bonus
