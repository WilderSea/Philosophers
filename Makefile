# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 17:02:35 by msintas-          #+#    #+#              #
#    Updated: 2023/04/14 17:07:43 by msintas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	philo.c

#BONUS	=	xxx_bonus.c

CC		=	gcc

CFLAGS	=   -Wextra -Wall -Werror 

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
#			@make -C $(MLX42)
#			@make -C $(LIBFT) --silent
#			$(CC) $(CFLAGS) $(BOBJS) $(INCLUDES) $(LIBS) -o $(NAME)

run : all
	./$(NAME)

.PHONY:		all clean fclean re bonus
